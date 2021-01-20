using System;
using DartboardGameServer;

namespace gamelogic
{
	public class GameLogic
	{
		private MqttConnecter mqtt;
		private Game game;
		
		static void Main(string[] args)
		{
			var logic = new GameLogic();
			logic.Start();
		}

		private void Start()
		{
			mqtt = new MqttConnecter();
			game = new Game_501(2, 1);
			mqtt.UpdateReceived += HandleUpdateReceived;
		}

		private void HandleUpdateReceived(object sender, EventArgs e)
		{
			var hitEvent = (HitEvent) e;
			int playerScore = game.ProcessDart(hitEvent.PlayerNum, hitEvent.Value);
			
			if (playerScore == 0)
			{
				mqtt.SetValue($"Player {hitEvent.PlayerNum+1}\n wins!");
				mqtt.DisableAll();
				return;
			}

			mqtt.SetValue($"P1: {game.GetPlayerScore(0)} - P2: {game.GetPlayerScore(1)}");
		}
	}
}
