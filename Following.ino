/*
 * This code is used for following logic of the trolley. It uses PWM motors and ultrasonic transmitter+receiver
 */

/*******************************************************************************
 * CONNECTIONS:
 * 
 * Arduino D03  - Motor Driver1 PWM 1A Input
 * Arduino D06 - Motor Driver1 PWM 2A Input
 * Arduino D04  - Motor Driver1 1B Input
 * Arduino D07 - Motor Driver1 2B Input
 * 
 * Arduino D09 - Motor Driver2 PWM 1A Input
 * Arduino D10 - Motor Driver1 PWM 2A Input
 * Arduino D11 - Motor Driver1 1B Input
 * Arduino D12 - Motor Driver1 2B Input

*/
#include "CytronMotorDriver.h"
int receiver;

// Configure the motor driver.
CytronMD motor1(PWM_PWM, 3, 4);   // PWM 1A = Pin 3, PWM 1B = Pin 4.
CytronMD motor2(PWM_PWM, 6, 7); // PWM 2A = Pin 6, PWM 2B = Pin 7.

CytronMD motor3(PWM_PWM, 9, 11);   // PWM 1A = Pin 9, PWM 1B = Pin 11.
CytronMD motor4(PWM_PWM, 10, 12); // PWM 2A = Pin 10, PWM 2B = Pin 12.

// The setup routine runs once when you press reset.
void setup() {
  Serial.begin(9600);
  pinMode(2,INPUT);
}

// The loop routine runs over and over again forever.
void loop() {
  receiver = digitalRead(2);
  if (receiver == HIGH)
  {
    Serial.println("Follow");
    delay(2000);
    motor1.setSpeed(200);  // Motor 1 runs forward.
    motor2.setSpeed(200);  // Motor 2 runs forward.
    
    motor3.setSpeed(-200);  // Motor 3 runs forward.
    motor4.setSpeed(-200);  // Motor 4 runs forward.
    delay(2000);
  }
  else if(receiver == LOW)
  {
     Serial.println("Wait");
     delay(2000);
     motor1.setSpeed(0);     // Motor 1 stops.
     motor2.setSpeed(0);     // Motor 2 stops.
     
     motor3.setSpeed(0);     // Motor 3 stops.
     motor4.setSpeed(0);     // Motor 4 stops.
     delay(2000);
  }  
}
