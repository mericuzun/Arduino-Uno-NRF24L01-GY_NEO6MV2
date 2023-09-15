# Arduino-Uno-NRF24L01-GY_NEO6MV2
Transmiting GPS data via NRF24 2.4GHz
Required libraries and examples:
https://github.com/mikalhart/TinyGPSPlus/tree/master
https://github.com/mikalhart/TinyGPSPlus/blob/master/examples/DeviceExample/DeviceExample.ino
https://github.com/nRF24/RF24.git
https://github.com/nRF24/RF24/blob/master/examples/GettingStarted/GettingStarted.ino
In this project I used NRF24 breakout adapter. Project can be done without adapter, supply NRF24 module directly from 3V3.
Reciever connections:
  NRF24L01 connections:
  CE   ->  8
  CSN  ->  9
  SCK  ->  13
  MO   ->  11
  MI   ->  12
  VCC  ->  5V
  GND  ->  GND
Transmitter connections:
  NRF24L01 connections:
  CE   ->  8
  CSN  ->  9
  SCK  ->  13
  MO   ->  11
  MI   ->  12
  VCC  ->  5V
  GND  ->  GND
  NEO6MV2 connections:
  VCC  ->  5V
  RX   ->  3
  TX   ->  2
  GND  ->  GND
