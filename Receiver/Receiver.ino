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
  int servo1, servo2, servo3, motor;
}dataRx;

Servo motor;
Servo servo1;
Servo servo2;
Servo servo3;

void setup() {
  motor.attach(MOTOR_PIN);

  motor.writeMicroseconds(MAX_SIGNAL);
  delay(1000);
  motor.writeMicroseconds(MIN_SIGNAL);
  
  servo1.attach(3);
  servo2.attach(5);
  servo3.attach(6);
  
  
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
    
    servo1.write(dataRx.servo1);
    servo2.write(dataRx.servo2);
    servo3.write(dataRx.servo3);
    motor.writeMicroseconds(dataRx.motor);
  }
}
