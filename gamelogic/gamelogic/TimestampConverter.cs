using System;
using System.Text.Json;
using System.Text.Json.Serialization;

/// <summary>
/// JSON Converter for Unix time in milliseconds
/// </summary>
public class TimestampConverter : JsonConverter<DateTimeOffset>
{
    public override DateTimeOffset Read(
        ref Utf8JsonReader reader,
        Type typeToConvert,
        JsonSerializerOptions options) => DateTimeOffset.FromUnixTimeMilliseconds(reader.GetInt64());

    public override void Write(
        Utf8JsonWriter writer,
        DateTimeOffset dateTimeValue,
        JsonSerializerOptions options)
            => writer.WriteNumberValue(dateTimeValue.ToUnixTimeMilliseconds());
}
