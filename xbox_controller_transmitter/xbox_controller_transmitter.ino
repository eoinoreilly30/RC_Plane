#include <Firmata.h>
#include "Arduino.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

int aileron = 4;
int elevator = 5;
int motor = 6;

RF24 radio(7, 8); // CNS, CE

const byte addresses[][6] = {"00001", "00002"};

struct dataStruct{
  int aileron, elevator, motor;
}data;

void setup()
{
  Serial.begin(9600);
  
  Firmata.setFirmwareVersion(0, 1);
  Firmata.attach(ANALOG_MESSAGE, analogWriteCallback); // Call this function when analog writes are received
  Firmata.begin(57600);
  
  radio.begin();
  radio.setDataRate(RF24_2MBPS);
  radio.setPALevel(RF24_PA_MIN);
  radio.setChannel(124);
  radio.openWritingPipe(addresses[1]); // 00001
  radio.openReadingPipe(1, addresses[0]); // 00002
  radio.stopListening();
}

void loop()
{
   while(Firmata.available()) // Handles Firmata serial input
       Firmata.processInput();
}

// Called whenever Arduino receives an analog message through Firmata
void analogWriteCallback(byte pin, int value)
{
  if(pin == aileron) {
    data.aileron = value;
  }

  else if(pin == elevator) {
    data.elevator = value;
  }

  else if(pin == motor) {
    data.motor = value;
  }
  
   // Otherwise, just send the pin value to the appropriate pin on the Arduino
  else {
     pinMode(pin,OUTPUT);
     analogWrite(pin, value);
  }

  Serial.println(value);

  radio.write(&data, sizeof(data));
}
