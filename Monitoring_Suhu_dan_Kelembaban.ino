#include <DHT.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ThingSpeak.h>
#define DHTPIN D3
DHT dht(DHTPIN, DHT11);
WiFiClient client;

String apiKey = ""; // apiKeyRead
const char *ssid = ""; // ssid WiFi
const char *pass = ""; // pass ssid
const char *server = "api.thingspeak.com"; // server yang di gunakan
unsigned long myChannelNumber = 0; // channel thingspeak
const char *myWriteAPIKey = "";


void setup() {
  Serial.begin(9600);
  delay(10);
  dht.begin();
  
  Serial.println("Connecting... ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  ThingSpeak.begin(client);
}

void loop() {  
  float suhu = dht.readTemperature();
  float kelembaban = dht.readHumidity();
  if (isnan(suhu) || isnan(kelembaban)) {
    Serial.println("Sensor Tidak Terdeteksi");
    return;
  }  

  ThingSpeak.writeField(myChannelNumber,1,suhu,myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber,2,kelembaban,myWriteAPIKey);
  delay(10);

  Serial.print("Kelembaban: ");  
  Serial.println(kelembaban);
  Serial.println(" ");  
  Serial.print("Suhu: ");
  Serial.println(suhu);

}
