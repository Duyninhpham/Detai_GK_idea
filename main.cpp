#include <Arduino.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <Ticker.h>
#include "wifi_connect.h"
#include "ca_cert.h"

// Chân kết nối phần cứng
#define SOIL_SENSOR_PIN 34 // Chân cảm biến độ ẩm đất
#define RELAY_PIN 25       // Chân điều khiển relay

// WiFi và MQTT thông tin
const char *ssid = "Wokwi-GUEST";
const char *password = "";
const char *mqttServer = "47a5763167324520891dd080bd6321d7.s1.eu.hivemq.cloud";
const int mqttPort = 8883;
const char *mqttUser = "DuyPham";
const char *mqttPassword = "Kd12345678";
const char *Hum_topic = "soil_humidity";
const char *Relay_status_topic = "relay_status";

// Khởi tạo MQTT và WiFi
WiFiClientSecure tlsClient;
PubSubClient mqttClient(tlsClient);
Ticker mqttPublishTicker;

// Hàm đọc độ ẩm đất và chuyển đổi sang %
float readSoilHumidity()
{
    int rawValue = analogRead(SOIL_SENSOR_PIN); // Đọc giá trị ADC
    return map(rawValue, 0, 4095, 0, 100);      // Chuyển đổi sang %
}

// Hàm đăng tải độ ẩm đất lên MQTT
void publishSoilHumidity()
{
    float soilHumidity = readSoilHumidity();
    Serial.print("Soil Humidity (%): ");
    Serial.println(soilHumidity);

    // Chuyển đổi thành chuỗi và gửi lên broker
    String humidityStr = String(soilHumidity) + "%";
    mqttClient.publish(Hum_topic, humidityStr.c_str(), false);

    // Điều khiển relay tự động
    if (soilHumidity < 70)
    {
        digitalWrite(RELAY_PIN, HIGH); // Bật relay
        mqttClient.publish(Relay_status_topic, "ON", false);
    }
    else
    {
        digitalWrite(RELAY_PIN, LOW); // Tắt relay
        mqttClient.publish(Relay_status_topic, "OFF", false);
    }
}

// Hàm xử lý tin nhắn MQTT nhận được
void mqttCallback(char *topic, byte *payload, unsigned int length)
{
    payload[length] = '\0'; // Thêm ký tự null kết thúc chuỗi
    String command = String((char *)payload);

    if (strcmp(topic, Relay_status_topic) == 0)
    {
        if (command == "ON")
        {
            digitalWrite(RELAY_PIN, HIGH);
        }
        else if (command == "OFF")
        {
            digitalWrite(RELAY_PIN, LOW);
        }
    }
}

// Hàm kết nối lại MQTT
void reconnectMQTT()
{
    while (!mqttClient.connected())
    {
        Serial.print("Attempting MQTT connection...");
        String clientId = "esp32-client-" + String(WiFi.macAddress());
        if (mqttClient.connect(clientId.c_str(), mqttUser, mqttPassword))
        {
            Serial.println("connected");
            mqttClient.subscribe(Relay_status_topic);
        }
        else
        {
            Serial.print("Failed, rc=");
            Serial.print(mqttClient.state());
            Serial.println(" try again in 2 seconds");
            delay(2000);
        }
    }
}

void setup()
{
    Serial.begin(115200);
    pinMode(SOIL_SENSOR_PIN, INPUT);
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, LOW); // Tắt relay ban đầu

    // Kết nối WiFi
    setup_wifi(ssid, password);

    // Cài đặt chứng chỉ SSL và MQTT
    tlsClient.setCACert(ca_cert);
    mqttClient.setServer(mqttServer, mqttPort);
    mqttClient.setCallback(mqttCallback);

    // Đặt lịch đăng tải độ ẩm đất mỗi giây
    mqttPublishTicker.attach(1, publishSoilHumidity);
}

void loop()
{
    if (!mqttClient.connected())
    {
        reconnectMQTT();
    }
    mqttClient.loop(); // Duy trì kết nối MQTT
}
