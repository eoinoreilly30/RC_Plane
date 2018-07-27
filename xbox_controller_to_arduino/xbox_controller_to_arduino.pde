import processing.serial.*;
import net.java.games.input.*;
import org.gamecontrolplus.*;
import org.gamecontrolplus.gui.*;
import cc.arduino.*;
import org.firmata.*;

ControlDevice cont;
ControlIO control;
Arduino arduino;
float thumb;
int servo1 = 3;

void setup() {
  size(127, 127);
  control = ControlIO.getInstance(this);
  cont = control.getMatchedDevice("Test");

  if (cont == null) {
    println("not today chump"); // write better exit statements than me
    System.exit(-1);
  }
  //println(Arduino.list());
  arduino = new Arduino(this, Arduino.list()[0], 57600);
}

public void getUserInput() {
  thumb = map(cont.getSlider("servoPos").getValue(), -1, 1, 0, 180);
}

void draw() {
  getUserInput();
  arduino.analogWrite(servo1, (int)thumb);
}
