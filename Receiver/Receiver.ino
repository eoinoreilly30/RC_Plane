#include "Arduino.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

#define MAX_SIGNAL 2000
#define MIN_SIGNAL 700
#define MOTOR_PIN 9

RF24 radio(7, 8); // CNS, CE

const byte addresses[][6] = {"00001", "00002"};

struct dataStruct{
  int leftAileron, rightAileron, elevator, motor;
}dataRx;

Servo motor;
Servo leftAileron;
Servo rightAileron;
Servo elevator;

void setup() {
  motor.attach(MOTOR_PIN);

  motor.writeMicroseconds(MAX_SIGNAL);
  delay(1000);
  motor.writeMicroseconds(MIN_SIGNAL);
  
  leftAileron.attach(3);
  rightAileron.attach(5);
  elevator.attach(6);
  
  
  radio.begin();
  radio.setDataRate(RF24_2MBPS);
  radio.setPALevel(RF24_PA_MIN);
  radio.setChannel(124);
  radio.openWritingPipe(addresses[0]); // 00002
  radio.openReadingPipe(1, addresses[1]); // 00001

  radio.startListening();
}

void loop() {
  
  if (radio.available()) 
  {
    while (radio.available()) 
    {
      radio.read(&dataRx, sizeof(dataRx));
    }
    
    leftAileron.write(dataRx.leftAileron);
    rightAileron.write(dataRx.rightAileron);
    elevator.write(dataRx.elevator);
    motor.writeMicroseconds(dataRx.motor);
  }
}
