#include <Firmata.h>

int servo1 = 3; //  Incoming Firmata data on this pin is handled specially.

void setup()
{
   Firmata.setFirmwareVersion(0, 1);
   Firmata.attach(ANALOG_MESSAGE, analogWriteCallback); // Call this function when analog writes are received
   Firmata.begin(57600);
   pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
   while(Firmata.available()) { // Handles Firmata serial input
       Firmata.processInput();
   }
}

// Called whenever Arduino receives an analog msg thru Firmata
void analogWriteCallback(byte pin, int value)
{
   // If data is sent to reserved pin, execute code
   if(pin == servo1) {
    if(value == 180){
    digitalWrite(LED_BUILTIN, HIGH);
    }
    else{
    digitalWrite(LED_BUILTIN, LOW);
    }
   } 
   
   // Otherwise, just send the pin value to the appropriate pin on the Arduino
   else {
     pinMode(pin,OUTPUT);
     analogWrite(pin, value);
   }  
}



