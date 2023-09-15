#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <SoftwareSerial.h>
#include <TinyGPSPlus.h>


TinyGPSPlus gps;
// CE, CSN
RF24 radio(9, 8); 
// RX, TX - TX, RX of gps
SoftwareSerial ss(2, 3);


struct dataStruct{
  // latitude, longitude and altitude are defined as double in case of an negative value
  double latitude;
  double longitude;
  double altitude;
  unsigned long date;
  unsigned long time;
  int satalites;
}gps_data;


void setup() {
  Serial.begin(115200);
  ss.begin(9600);
  
  // Setup and configure RF radio
  radio.begin();
  // Open pipe
  radio.openWritingPipe(0xF0F0F0F0E1LL);
  // Lowest frequency 2.4GHz
  radio.setChannel(0x00);
  // LOW power level
  // Default is MAX
  radio.setPALevel(RF24_PA_LOW);
  // Lowest bitrate
  radio.setDataRate(RF24_250KBPS);
  radio.stopListening();
  radio.powerUp();
}


void loop() {
  while (ss.available() > 0){
    if (gps.encode(ss.read())){
      get_data();
      radio.write(&gps_data, sizeof(gps_data));
    }
  }
} 


void get_data(){
  if (gps.location.isValid()){
    gps_data.latitude = gps.location.lat();
    gps_data.longitude = gps.location.lng();
    gps_data.altitude = gps.altitude.meters();
  }
  else{
    gps_data.latitude = 0;
    gps_data.longitude = 0;
  }

  if (gps.date.isValid()){
    gps_data.date = gps.date.value();
  }
  else{
    gps_data.date = 0;
  }

  if (gps.time.isValid()){
    gps_data.time = (gps.time.value());
  }
  else{
    gps_data.time = 0;
  }
  if (gps.satellites.isValid()){
    gps_data.satalites = gps.satellites.value();
  }
  else{
    gps_data.satalites = 0;
  }
}