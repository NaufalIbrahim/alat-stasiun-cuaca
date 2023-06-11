#include "RTClib.h"
#include <SPI.h>
#include <LoRa.h>
#include "DHT.h"
#include <Adafruit_BMP280.h>


RTC_DS1307 rtc;

#define DHTPIN 5
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP280 bmp;

#define ss 10
#define rst 9
#define dio0 2

char daysOfTheWeek[7][12] = {"Ahad", "Senin", "Selasa", "Rabu", "Kamis", "Jum'at", "Sabtu"};

//unsigned long previousMillis = 0; //--> will store last time was updated
//const long interval = 1000; //--> interval (1000 = 1 second)


int counter = 0;

//dht11
float hum;
float temp;
//bmp280
float pres;

  
void setup() {
  Serial.begin(9600); //baud komunikasi serial

  
  Serial.println("Inisialisasi RTC DS1307...");
  delay(100);
  //rtc.begin();

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay (10);
  }

  Serial.println("Successfully Initializing the RTC DS1307");
  Serial.println();

  Serial.println("Starting to run RTC DS1307...");
  delay(100);

  //----------------------------------------------Checks whether the DS1307 RTC can be run or not
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    //delay(100);
    // following line sets the RTC to the date & time this sketch was compiled (Set the time and date based on your computer time and date)
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //-> If that doesn't work, use this line of code outside of "if (! rtc.isrunning())"
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  Serial.println("Successfully running RTC DS1307");
  delay(100);
  

  //starting sensors
  Serial.println("Start DHT11");
  dht.begin();
  
  Serial.println("Start BMP280");
  bmp.begin();
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
                  
  /*
  Serial.println("Inisialisasi Micro SD...");
  delay(100);
  
  if (!SD.begin()){
    Serial.println("failed open sd\n");
    while(1);
  }
  Serial.println("Inisialisasi Micro SD sukses :)");
  Serial.println();
  delay(100);
  */
  
  Serial.println("Inisialisasi LoRa...");
  Serial.println();
    
  while (!Serial);
  Serial.println("LoRa Sender");
  LoRa.setPins(ss, rst, dio0);
  /*
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  */
  while (!LoRa.begin(433E6)) {
    Serial.println(".");
    delay(500);
  }
  
  LoRa.setSyncWord(0xF3);
  Serial.println("Inisialisasi LoRa OK!!");
}

void loop() {
  DateTime now = rtc.now();

  //var sensors
  //dht
  temp = dht.readTemperature();
  hum = dht.readHumidity();
  //bmp
  pres = bmp.readPressure();

  Serial.println("----");
  //Printing Tanggal dan Waktu di serial monitor
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(now.hour()+1, DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.println(now.second(), DEC);
    
  Serial.print("Temperature : ");
  Serial.print(temp);
  Serial.print(" °C");
  Serial.print(" | Kelembaban : ");
  Serial.print(hum);
  Serial.print(" %");
  Serial.print(" | Tekanan udara: ");
  Serial.print(pres);
  Serial.print(" Pa");
  Serial.println();

    /*
    myFile = SD.open("dataSensor.txt", FILE_WRITE);
    if (myFile) {
      Serial.print("mencetak dataSensor.txt");
      myFile.print(now.year(), DEC);
      myFile.print('/');
      myFile.print(now.month(), DEC);
      myFile.print('/');
      myFile.print(now.day(), DEC);
      myFile.print(" (");
      myFile.print(daysOfTheWeek[now.dayOfTheWeek()]);
      myFile.print(") ");
      
      myFile.print(",");
      
      myFile.print(now.hour(), DEC);
      myFile.print(':');
      myFile.print(now.minute(), DEC);
      myFile.print(':');
      myFile.print(now.second(), DEC);
      
      myFile.print(",");

      myFile.print(temp);

      myFile.print(",");

      myFile.print(hum);

      myFile.print(",");

      myFile.print(pres);

      myFile.close();

      Serial.println("Sukses menulis data ke Micro SD");
      Serial.println("----");
      Serial.println();
    } else {
      Serial.print("Kesalahan membuka dataSensor.txt");
    }
    */

    /*
    temp = dht.readTemperature();
    hum = dht.readHumidity();
    //bmp
    pres = bmp.readPressure();

    Serial.print("Temperature : ");
    Serial.print(temp);
    Serial.print(" °C");
    Serial.print(" | Kelembaban : ");
    Serial.print(hum);
    Serial.print(" %");
    Serial.print(" | Tekanan udara: ");
    Serial.print(pres);
    Serial.print(" Pa");
    */

    
  //Millis untuk mengupdate Tanggal, Waktu, Temperatur, Kelembaban, dan Tekanan udara

  /*
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 1000) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    DateTime now = rtc.now();

    //var sensors
    //dht
    temp = dht.readTemperature();
    hum = dht.readHumidity();
    //bmp
    //pres = bmp.readPressure();

    if(now.second() %5 == 0){
      Serial.println("----");
      //Printing Tanggal dan Waktu di serial monitor
      Serial.print(now.year(), DEC);
      Serial.print('/');
      Serial.print(now.month(), DEC);
      Serial.print('/');
      Serial.print(now.day(), DEC);
      Serial.print(" (");
      Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
      Serial.print(") ");
      Serial.print(now.hour(), DEC);
      Serial.print(':');
      Serial.print(now.minute(), DEC);
      Serial.print(':');
      Serial.print(now.second(), DEC);

      Serial.print("Temperature : ");
      Serial.print(temp);
      Serial.print(" °C");
      Serial.print(" | Kelembaban : ");
      Serial.print(hum);
      Serial.print(" %");
      //Serial.print(" | Tekanan udara: ");
      //Serial.print(pres);
      //Serial.print(" Pa");
      Serial.println();

      myFile = SD.open("dataSensor.txt", FILE_WRITE);
      if (myFile) {
        Serial.print("mencetak dataSensor.txt");
        myFile.print(now.year(), DEC);
        myFile.print('/');
        myFile.print(now.month(), DEC);
        myFile.print('/');
        myFile.print(now.day(), DEC);
        myFile.print(" (");
        myFile.print(daysOfTheWeek[now.dayOfTheWeek()]);
        myFile.print(") ");

        myFile.print(",");

        myFile.print(now.hour(), DEC);
        myFile.print(':');
        myFile.print(now.minute(), DEC);
        myFile.print(':');
        myFile.print(now.second(), DEC);

        myFile.print(",");

        myFile.print(temp);

        myFile.print(",");

        myFile.print(hum);

        //myFile.print(",");

        //myFile.print(pres);

        myFile.close();

        Serial.println("Sukses menulis data ke Micro SD");
        Serial.println("----");
        Serial.println();
      } else {
        Serial.print("Kesalahan membuka dataSensor.txt");
      }
    }
  }
  */
  
  
  
  
  Serial.print("Sending packet: ");
  Serial.println(counter);
 
  // send packet
  LoRa.beginPacket();
  //LoRa.print("Temperature : ");
  LoRa.print(temp);
  LoRa.print(" °C | ");
  //LoRa.print(" | Kelembaban : ");
  LoRa.print(hum);
  LoRa.print(" % | ");
  //LoRa.print(" | Tekanan udara: ");
  LoRa.print(pres);
  LoRa.print(" Pa ");
  Serial.print("' with RSSI ");
  Serial.println(LoRa.packetRssi());
  LoRa.print(counter);
  LoRa.endPacket();
 
  counter++;
  
  delay(2000);
}
