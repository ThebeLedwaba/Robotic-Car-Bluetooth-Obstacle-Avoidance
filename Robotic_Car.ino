// Robotic Car - Bluetooth Controlled with Obstacle Avoidance
// Author: Thebe Ledwaba
// Year: 2025
// Description: Arduino-based robotic car controlled via Bluetooth and avoids obstacles using ultrasonic sensor

// Motor Driver Pins (L298N)
const int ENA = 10;
const int ENB = 11;
const int IN1 = 2;
const int IN2 = 3;
const int IN3 = 4;
const int IN4 = 5;

// Ultrasonic Sensor Pins
const int trigPin = 6;
const int echoPin = 7;

// Bluetooth Input
char command;

void setup() {
  Serial.begin(9600);  // Bluetooth module (e.g., HC-05) is connected to Serial
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  if (Serial.available()) {
    command = Serial.read();
    handleCommand(command);
  }
}

// Movement Functions
void forward() {
  if (!obstacleDetected()) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, 150);  // Speed control
    analogWrite(ENB, 150);
  } else {
    stopMotors();
  }
}

void backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
}

void left() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
}

void right() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// Obstacle Detection using Ultrasonic Sensor
bool obstacleDetected() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;  // in cm
  return (distance < 15); // Obstacle within 15cm
}

// Bluetooth Command Handler
void handleCommand(char cmd) {
  switch (cmd) {
    case 'F':
      forward();
      break;
    case 'B':
      backward();
      break;
    case 'L':
      left();
      break;
    case 'R':
      right();
      break;
    case 'S':
      stopMotors();
      break;
    default:
      stopMotors();
  }
}
