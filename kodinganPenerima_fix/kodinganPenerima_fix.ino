#include <SPI.h>
#include <LoRa.h>
#include <WiFi.h>
//#include <ThingSpeak.h>

#define ss 5
#define rst 14
#define dio0 2 

String apiKey = "HVMD5HB13WJOI17H";

// Replace with your network credentials

const char* ssid = "****";
const char* password = "****";
const char* server = "api.thingspeak.com";

int channelTS = 1758760;
int i;

WiFiClient client;
//const char *writeAPI = "HVMD5HB13WJOI17H";

float temp;
float hum;
float pres;


void setup() {
  Serial.begin(115200);

  while (!Serial);
  Serial.println("LoRa Receiver");
  LoRa.setPins(ss, rst, dio0);
  /*
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  */

  
  while(!LoRa.begin(433E6)){
    Serial.println(".");
    delay(500);
  }
  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializing OK!!");

  
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.println(".");
    }
  Serial.println("");
  Serial.println("WiFi connected");
  
   //ThingSpeak.begin(client);
  
  
  
}

void loop() {
  /*
  ThingSpeak.writeField(channelTS,1,temp,writeAPI);
  ThingSpeak.writeField(channelTS,2,hum,writeAPI);
  ThingSpeak.writeField(channelTS,3,pres,writeAPI);
  */
  int packetSize = LoRa.parsePacket();
  if(packetSize) {
    
    //received paket
    Serial.print("Received packet: ");
    //read packet
    while(LoRa.available()) {
      //Serial.print((char)LoRa.read());
      String LoRaData = LoRa.readString();
      Serial.print(LoRaData);
    }
    //Serial.println("");

    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  }

  
  //delay(3000);
  
  if(client.connect(server, 80)){
    String postStr= apiKey;
    postStr += "&field1=";
    postStr += String(temp);
    postStr += "&field2=";
    postStr += String(hum);
    postStr += "&field3=";
    postStr += String(pres);
    postStr += "\r\n\r\n";
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
    Serial.print("Temperatur: ");
    Serial.print(temp);
    Serial.print(" derajat Celcius, Kelembaban: ");
    Serial.print(hum);
    Serial.print(" %, Tekanan udara: ");
    Serial.print(pres);
    Serial.print(" Pa");
    Serial.println();
    Serial.print("%. Send to Thingspeak.");
  }
  
  client.stop();
  Serial.println("Waiting...");
  delay(1000);
  

}
