using System;
using System.Text.Json;
using System.Text.Json.Serialization;

namespace gamelogic
{
    /// <summary>
    /// Class <c>AttributeReference</c> is a reference to the Attribute of an Entity
    /// </summary>
    ///
    class AttributeReference
    {
        [JsonPropertyName("entityId")]
        public string EntityID { get; set; }

        [JsonPropertyName("attributeName")]
        public string Name { get; set; }
    }

    /// <summary>
    /// Class <c>AttributeState</c> represents the state of an Attribute
    /// </summary>
    ///
    class AttributeState
    {
        [JsonPropertyName("attributeRef")]
        public AttributeReference Attribute { get; set; }

        [JsonPropertyName("value")]
        public JsonElement Value { get; set; }

        [JsonPropertyName("deleted")]
        public bool Deleted { get; set; }
    }

    /// <summary>
    /// Class <c>AttributeExportEvent</c> represents the export event of an Attribute
    /// </summary>
    ///
    class AttributeExportEvent
    {
        [JsonPropertyName("timestamp")]
        [JsonConverter(typeof(TimestampConverter))]
        public DateTimeOffset Timestamp { get; set; }

        [JsonPropertyName("eventType")]
        public string EventType { get; set; }

        [JsonPropertyName("realm")]
        public string Realm { get; set; }

        [JsonPropertyName("parentId")]
        public string ParentId { get; set; }

        [JsonPropertyName("attributeState")]
        public AttributeState AttributeState { get; set; }
    }
}