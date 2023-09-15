#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>


// CE, CSN
RF24 radio(9, 8); 


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
  
  // Setup and configure RF radio
  radio.begin();
  // Open pipe
  radio.openReadingPipe(0, 0xF0F0F0F0E1LL);
  // Lowest frequency, 2.4GHz
  radio.setChannel(0x00);
  // MAX power level 
  // Default is MAX
  radio.setPALevel(RF24_PA_MAX);
  // Lowest bitrate
  radio.setDataRate(RF24_250KBPS);
  radio.startListening();
  radio.powerUp();
}


void loop() {
  if (radio.available()) {
    radio.read(&gps_data, sizeof(gps_data));

    unsigned long date_value = gps_data.date;
    unsigned int date_firstTwoDigits = (date_value / 10000) % 100;
    unsigned int date_secondTwoDigits = (date_value / 100) % 100;
    unsigned int date_thirdTwoDigits = date_value % 100;

    unsigned long time_value = gps_data.time;
    unsigned int time_firstTwoDigits = (time_value / 1000000) % 100;
    unsigned int time_secondTwoDigits = (time_value / 10000) % 100;
    unsigned int time_thirdTwoDigits = (time_value / 100) % 100;

    Serial.print("Location: ");
    Serial.print(gps_data.latitude, 6);
    Serial.print(", ");
    Serial.print(gps_data.longitude, 6);
    Serial.print(", ");
    Serial.print(gps_data.altitude);
    Serial.print("M");

    Serial.print("  Date: ");
    Serial.print(date_firstTwoDigits);
    Serial.print(":");
    Serial.print(date_secondTwoDigits);
    Serial.print(":");
    Serial.print(date_thirdTwoDigits);
    
    Serial.print("  Time: ");
    Serial.print(time_firstTwoDigits);
    Serial.print(":");
    Serial.print(time_secondTwoDigits);
    Serial.print(":");
    Serial.print(time_thirdTwoDigits);

    Serial.print("  Satalites:  ");
    Serial.print(gps_data.satalites);
    Serial.println();
    }
}