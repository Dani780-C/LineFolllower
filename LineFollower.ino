#include <QTRSensors.h>

const int m11Pin = 7;
const int m12Pin = 6;
const int m21Pin = 5;
const int m22Pin = 4;
const int m1Enable = 11;
const int m2Enable = 10;

const int led1Pin = 12;
const int led2Pin = 13; 

int m1Speed = 0;
int m2Speed = 0;

const float kp = 0.3;
const float ki = 0.001;
const float kd = 8.0;

int p = 1;
int i = 0;
int d = 0;

int error = 0;
int lastError = 0;

const int maxSpeed = 255;
const int minSpeed = -255;
const int baseSpeed = 255;

QTRSensors qtr;

const int sensorCount = 6;
int sensorValues[sensorCount];
int sensors[sensorCount] = { 0, 0, 0, 0, 0, 0 };

void setup() {
  // pinMode setup
  pinMode(m11Pin, OUTPUT);
  pinMode(m12Pin, OUTPUT);

  pinMode(m21Pin, OUTPUT);
  pinMode(m22Pin, OUTPUT);
  pinMode(m1Enable, OUTPUT);
  pinMode(m2Enable, OUTPUT);
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3, A4, A5 }, sensorCount);
  delay(500);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); 

  Serial.begin(9600);

  bool direction = false;
  int calibrationSpeed = -220;

  int val;

  for (uint16_t i = 0; i < 200; i++) {
    qtr.calibrate();
    val = qtr.readLineBlack(sensorValues);
  }

  for (uint16_t i = 0; i < 200; i++) {
    qtr.calibrate();

    val = qtr.readLineBlack(sensorValues);    

    if ( val < 500 && direction == true) {
    calibrationSpeed = -calibrationSpeed;
    direction = false;
    }
    else if ( val > 4500 && direction == false ) {
      calibrationSpeed = -calibrationSpeed;
      direction = true;
    }
      
    setMotorSpeed( calibrationSpeed, -calibrationSpeed );
  }

  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(led1Pin, HIGH);
  digitalWrite(led2Pin, HIGH);  

}

void loop() 
{ 
  
  pidControl(kp, ki, kd);
  
  int motorSpeed = kp * p + ki * i + kd * d; 

  m1Speed = baseSpeed;
  m2Speed = baseSpeed;

  if (error < 0) {
    m1Speed += motorSpeed;
  } 
  else if (error > 0) {
    m2Speed -= motorSpeed;
  }

  m1Speed = constrain(m1Speed, m1Speed, maxSpeed);
  m2Speed = constrain(m2Speed, m2Speed, maxSpeed);
  setMotorSpeed(m1Speed, m2Speed);

}

void pidControl(float kp, float ki, float kd) 
{
  error = qtr.readLineBlack(sensorValues) - 2500;

  p = error;
  i = i + error; 
  d = error - lastError;
  lastError = error;
  
}

void setMotorSpeed(int motor1Speed, int motor2Speed) {

  if (motor1Speed == 0) {
    digitalWrite(m11Pin, LOW);
    digitalWrite(m12Pin, LOW);
    analogWrite(m1Enable, motor1Speed);
  } else {
    if (motor1Speed > 0) {
      digitalWrite(m11Pin, HIGH);
      digitalWrite(m12Pin, LOW);
      analogWrite(m1Enable, motor1Speed);
    }
    if (motor1Speed < 0) {
      digitalWrite(m11Pin, LOW);
      digitalWrite(m12Pin, HIGH);
      analogWrite(m1Enable, -motor1Speed);
    }
  }
  if (motor2Speed == 0) {
    digitalWrite(m21Pin, LOW);
    digitalWrite(m22Pin, LOW);
    analogWrite(m2Enable, motor2Speed);
  } else {
    if (motor2Speed > 0) {
      digitalWrite(m21Pin, HIGH);
      digitalWrite(m22Pin, LOW);
      analogWrite(m2Enable, motor2Speed);
    }
    if (motor2Speed < 0) {
      digitalWrite(m21Pin, LOW);
      digitalWrite(m22Pin, HIGH);
      analogWrite(m2Enable, -motor2Speed);
    }
  }
}