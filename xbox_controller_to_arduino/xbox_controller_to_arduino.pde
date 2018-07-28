import processing.serial.*;
import net.java.games.input.*;
import org.gamecontrolplus.*;
import org.gamecontrolplus.gui.*;
import cc.arduino.*;
import org.firmata.*;

ControlDevice controlDevice;
ControlIO controlIO;
Arduino arduino;
float roll, pitch, throttle;
int leftAileron = 3;
int rightAileron = 4;
int elevator = 5;
int motor = 6;

void setup() {
  size(127, 127);
  controlIO = ControlIO.getInstance(this);
  controlDevice = controlIO.getMatchedDevice("xbox_controller_readings");

  if (controlDevice == null) {
    println("not happening");
    System.exit(-1);
  }
  
  arduino = new Arduino(this, Arduino.list()[0], 57600);
}

public void getUserInput() {
  roll = map(controlDevice.getSlider("roll").getValue(), -1, 1, 0, 180);
  pitch = map(controlDevice.getSlider("pitch").getValue(), -1, 1, 0, 180);
  throttle = map(controlDevice.getSlider("throttle").getValue(), -1, 1, 700, 2000);
}

void draw() {
  getUserInput();
  arduino.analogWrite(leftAileron, (int)roll);
  arduino.analogWrite(rightAileron, (180-(int)roll));
  arduino.analogWrite(elevator, (180-(int)pitch));
  arduino.analogWrite(motor, (int)throttle);
}
