using System;
using System.Diagnostics;
using System.Linq;
using System.Net.Security;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Text.Json;
using uPLibrary.Networking.M2Mqtt;
using uPLibrary.Networking.M2Mqtt.Messages;
using static uPLibrary.Networking.M2Mqtt.MqttClient;

namespace gamelogic
{

    class HitEvent : EventArgs
    {
        private int _value;
        private int _playerNum;

        public int Value { get => _value; }
        public int PlayerNum { get => _playerNum; }

        public HitEvent(int value, int playerNum)
        {
            _value = value;
            _playerNum = playerNum;
        }
    }

    class MqttConnecter
    {
        public event EventHandler UpdateReceived;
        private MqttClient mqttClient;

        /*
            We didn't implement a configuration file for this, so you'll have to uncomment this code and fill it with your own credentials

            // The MQTT host (which is integrated in OpenRemote)
            private const string OPENREMOTE_HOST = "localhost";

            // The client ID, only has to match the realm (smartcity)
            private const string CLIENT_ID = "smartcity_test";

            // The client ID of the service account used to connect via MQTT
            private const string USERNAME = "";

            // The client secret of the service account used to connect via MQTT
            private const string PASSWORD = "";

            // The asset ID for the first player
            private const string TopicPlayer1 = "assets/4uthmTF71SbczfTsJ5dRb5";

            // The asset ID for the second player
            private const string TopicPlayer2 = "assets/7Z82EaiJnAW7k5lF2oQtxp";
        */
        
        private string CurrentTopic = TopicPlayer1;
        private int TurnPlayer = 0;

        public MqttConnecter()
        {
            mqttClient = new MqttClient(OPENREMOTE_HOST, 1883, false, MqttSslProtocols.TLSv1_2, (object sender, X509Certificate certificate, X509Chain chain, SslPolicyErrors sslPolicyErrors) => { return true; }, null);
            mqttClient.MqttMsgPublishReceived += GetMsgHandler(mqttClient);
            mqttClient.Connect(CLIENT_ID, USERNAME, PASSWORD);
            mqttClient.Subscribe(new string[] { TopicPlayer1 }, new byte[] { MqttMsgBase.QOS_LEVEL_AT_LEAST_ONCE });
            mqttClient.Subscribe(new string[] { TopicPlayer2 }, new byte[] { MqttMsgBase.QOS_LEVEL_AT_LEAST_ONCE });
            SetupValues();
        }

        MqttMsgPublishEventHandler GetMsgHandler(MqttClient mqttClient)
        {
            return (object sender, MqttMsgPublishEventArgs e) =>
            {
                var data = JsonSerializer.Deserialize<AttributeExportEvent>(e.Message);
                Debug.WriteLine($"[{data.Timestamp}] - {data.Realm} > {data.AttributeState.Attribute.EntityID} > {data.AttributeState.Attribute.Name} = {data.AttributeState.Value}");

                if (data.AttributeState.Attribute.Name == "hits")
                {
                    int[] values = data.AttributeState.Value.EnumerateArray().Select(json=>json.GetInt32()).ToArray();

                    string hitsDisplay = string.Join(", ", values.Select(num => num.ToString()));
                    mqttClient.Publish($"{TopicPlayer1}/{"secondaryLine"}", Encoding.UTF8.GetBytes(JsonSerializer.Serialize(hitsDisplay)));
                    mqttClient.Publish($"{TopicPlayer2}/{"secondaryLine"}", Encoding.UTF8.GetBytes(JsonSerializer.Serialize(hitsDisplay)));

                    // If there are 3 values thrown
                    if (values.Length == 3)
                    {
                        int dartValue = 0;

                        foreach (var item in values)
                        {
                            dartValue += item;
                        }

                        if (e.Topic == TopicPlayer1)
                        {
                            CurrentTopic = TopicPlayer1;
                            TurnPlayer = 0;
                        }
                        else if (e.Topic == TopicPlayer2)
                        {
                            CurrentTopic = TopicPlayer2;
                            TurnPlayer = 1;
                        }

                        StartEvent(new HitEvent(dartValue, TurnPlayer));
                    }
                }
            };
        }

        // Starting the event in the main form.
        void StartEvent(EventArgs e)
        {
            UpdateReceived?.Invoke(this, e);
        }

        // Sending value to the current topic.
        public void SetValue(string value)
        {
            mqttClient.Publish($"{TopicPlayer1}/{"primaryLine"}", Encoding.UTF8.GetBytes(JsonSerializer.Serialize(value)));
            mqttClient.Publish($"{TopicPlayer2}/{"primaryLine"}", Encoding.UTF8.GetBytes(JsonSerializer.Serialize(value)));

            // Update status on secondary line and enable/disable dartboard.
            if (CurrentTopic == TopicPlayer1)
            {
                SetSecondary(TopicPlayer1, TopicPlayer2);
            }
            else if (CurrentTopic == TopicPlayer2)
            {
                SetSecondary(TopicPlayer2, TopicPlayer1);
            }
        }

        // Topic 1's turn has ended, Topic 2's turn starts.
        private void SetSecondary(string topic1, string topic2)
        {
            // Player who's turn it is.
            mqttClient.Publish($"{topic1}/{"secondaryLine"}", Encoding.UTF8.GetBytes(JsonSerializer.Serialize("Waiting for other player..")));
            mqttClient.Publish($"{topic1}/{"enable"}", Encoding.UTF8.GetBytes(JsonSerializer.Serialize(false)));

            // Player who's turn has ended.
            mqttClient.Publish($"{topic2}/{"secondaryLine"}", Encoding.UTF8.GetBytes(JsonSerializer.Serialize("Your turn")));
            mqttClient.Publish($"{topic2}/{"enable"}", Encoding.UTF8.GetBytes(JsonSerializer.Serialize(true)));
        }

        // Set values for the games start.
        private void SetupValues()
        {
            //Enable the right dartboard.
            SetSecondary(TopicPlayer2, TopicPlayer1);

            // Display the right score.
            mqttClient.Publish($"{TopicPlayer1}/{"primaryLine"}", Encoding.UTF8.GetBytes(JsonSerializer.Serialize("P1: 501 - P2: 501")));
            mqttClient.Publish($"{TopicPlayer2}/{"primaryLine"}", Encoding.UTF8.GetBytes(JsonSerializer.Serialize("P1: 501 - P2: 501")));
        }

        public void DisableAll()
        {
            byte[] disabled = Encoding.UTF8.GetBytes(JsonSerializer.Serialize(false));
            byte[] gameEnded = Encoding.UTF8.GetBytes(JsonSerializer.Serialize("Game ended."));
            mqttClient.Publish($"{TopicPlayer1}/{"enable"}", disabled);
            mqttClient.Publish($"{TopicPlayer1}/{"secondaryLine"}", gameEnded);
            mqttClient.Publish($"{TopicPlayer2}/{"enable"}", disabled);
            mqttClient.Publish($"{TopicPlayer2}/{"secondaryLine"}", gameEnded);
        }
    }
}
