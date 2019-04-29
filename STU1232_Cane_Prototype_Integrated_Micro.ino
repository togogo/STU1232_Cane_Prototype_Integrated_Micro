#include<SoftwareSerial.h>//for HC-05
#include <Wire.h>//for BNO055
#include <Adafruit_Sensor.h>//for BNO055
#include <Adafruit_BNO055.h>//for BNO055
#include <utility/imumaths.h>//for BNO055
Adafruit_BNO055 bno = Adafruit_BNO055(55);//for BNO055

//#define LED_PIN
#define LED1 9
#define LED2 7
#define LED3 4
#define vibrationMotor1 8
#define vibrationMotor2 5
#define vibrationMotor3 6
#define TxD 11
#define RxD 10

int brightness = 0;
int fadeAmount = 5;//not used at the moment...but will be implemented later...

int gaitSpeed = 0;
int gaitSpeed1 = 500;//time delay for gaitSpeed1
int gaitSpeed2 = 300;//time delay for gaitSpeed2
int gaitSpeed3 = 100;//time delay for gaitSpeed3

bool lamp = false;

SoftwareSerial Bluetooth(RxD, TxD);
char c;//for incoming signal

void setup() {

  //start comm. for both serial and bluetooth
  Bluetooth.begin(9600);
  Serial.begin(9600);
  //while (!Serial);//workaround required for Arduino Micro

  // put your setup code here, to run once:

  pinMode(LED1, OUTPUT);//for led
  pinMode(LED2, OUTPUT);//for led 2
  pinMode(LED3, OUTPUT);//for led 3
  pinMode(vibrationMotor1, OUTPUT);//vibrationmotor
  pinMode(vibrationMotor2, OUTPUT);//vibrationmotor
  pinMode(vibrationMotor3, OUTPUT);//vibrationmotor

  //Serial.println("Orientation Sensor Test");
  //Serial.println("");

  /* Initialise the sensor */


  if (!bno.begin())
  {
    // There was a problem detecting the BNO055 ... check your connections
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while (1);
  }




  delay(1000);

  bno.setExtCrystalUse(true);

}

void loop() {

  //Serial.println(lamp);//for debugging purposes

  /*BNO055 code: Get a new sensor event */
  sensors_event_t event;
  bno.getEvent(&event);


  //for the vibration motor part...could be refined

  //if the gait speed is set to 0, do not vibrate at aall
  if(gaitSpeed == 0){
    analogWrite(vibrationMotor1, 0);
    analogWrite(vibrationMotor2, 0);
    analogWrite(vibrationMotor3, 0);  
  }
  else if(gaitSpeed == 1){
    analogWrite(vibrationMotor1, 255);
    delay(gaitSpeed1);
    analogWrite(vibrationMotor1, 0);
    
    analogWrite(vibrationMotor2, 255);
    delay(gaitSpeed1);
    analogWrite(vibrationMotor2, 0);
    
    analogWrite(vibrationMotor3, 255);
    delay(gaitSpeed1);
    analogWrite(vibrationMotor3, 0);
  }
  else if(gaitSpeed == 2){
    analogWrite(vibrationMotor1, 255);
    delay(gaitSpeed2);
    analogWrite(vibrationMotor1, 0);
    
    analogWrite(vibrationMotor2, 255);
    delay(gaitSpeed2);
    analogWrite(vibrationMotor2, 0);
    
    analogWrite(vibrationMotor3, 255);
    delay(gaitSpeed2);
    analogWrite(vibrationMotor3, 0);
  }
  else if(gaitSpeed == 3){
    analogWrite(vibrationMotor1, 255);
    delay(gaitSpeed3);
    analogWrite(vibrationMotor1, 0);
    
    analogWrite(vibrationMotor2, 255);
    delay(gaitSpeed3);
    analogWrite(vibrationMotor2, 0);
    
    analogWrite(vibrationMotor3, 255);
    delay(gaitSpeed3);
    analogWrite(vibrationMotor3, 0);
  }
  
  //LED Module: turn the light on based on Bluetooth serial input
  //maybe refined by gradually turning on/off the lights
  if (lamp == true) {
    brightness = 255;
  } else if (lamp == false) {
    brightness = 0;
  }


  analogWrite(LED1, brightness);
  analogWrite(LED2, brightness);
  analogWrite(LED3, brightness);


  /*
    brightness = brightness + fadeAmount;
    if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
    }
  */

  //Serial.println(brightness);//for debugging LED

  //this sends serial signal from PC -> Arduino
  //Going to use this to turn on the LED Lamp
  if (Bluetooth.available()) {
    c = Bluetooth.read();
    //Serial.println(c);
    //Bluetooth.println(c);

    if (c == 't') {
      lamp = true;
      Bluetooth.println("lamp is on");
    }
    if (c == 'f') {
      lamp = false;
      Bluetooth.println("lamp is off");
    }
    if (c == '0') {
      gaitSpeed = 0;
      Bluetooth.println("gait speed is now set to 0");
    }
    if (c == '1') {
      gaitSpeed = 1;
      Bluetooth.println("gait speed is now set to 1");
    }
    if (c == '2') {
      gaitSpeed = 2;
      Bluetooth.println("gait speed is now set to 2");
    }
    if (c == '3') {
      gaitSpeed = 3;
      Bluetooth.println("gait speed is now set to 3");
    }
  }

  /*Display the floating point data for BLUETOOTH comm. */
  
    Bluetooth.print("X: ");
    Bluetooth.print(event.orientation.x, 4);
    Bluetooth.print("\tY: ");
    Bluetooth.print(event.orientation.y, 4);
    Bluetooth.print("\tZ: ");
    Bluetooth.print(event.orientation.z, 4);
    Bluetooth.println("");

  /* Display the floating point data for SERIAL comm. */
  /*
      Serial.print("X: ");
      Serial.print(event.orientation.x, 4);
      Serial.print("\tY: ");
      Serial.print(event.orientation.y, 4);
      Serial.print("\tZ: ");
      Serial.print(event.orientation.z, 4);
      Serial.println("");
  */

  delay(100);//need to play around with this variable

}
