#include <ESP32Servo.h>

const int trigPin = 12;     // Trigger pin of the ultrasonic sensor
const int echoPin = 13;     // Echo pin of the ultrasonic sensor

const int motor1Forward = 32; // Motor driver IN1
const int motor1Backward = 33; // Motor driver IN2
const int motor2Forward = 25;  // Motor driver IN3
const int motor2Backward = 26; // Motor driver IN4

void setup() {
  Serial.begin(115200);

  // Initialize motor pins
  pinMode(motor1Forward, OUTPUT);
  pinMode(motor1Backward, OUTPUT);
  pinMode(motor2Forward, OUTPUT);
  pinMode(motor2Backward, OUTPUT);

  // Initialize ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  long duration, distance;

  // Clear the trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Set the trigger pin HIGH for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echo pin
  duration = pulseIn(echoPin, HIGH);

  // Calculate distance in cm
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  // Check distance to avoid obstacles
  if (distance < 10) { // Adjust the threshold to 10 cm for testing
    stopMotors();      // Stop motors
    delay(500);        // Wait for half a second
    turn();            // Turn to avoid obstacle
  } else {
    moveForward();     // Move forward
  }

  delay(100); // Small delay for stability
}

void moveForward() {
  digitalWrite(motor1Forward, HIGH);
  digitalWrite(motor1Backward, LOW);
  digitalWrite(motor2Forward, HIGH);
  digitalWrite(motor2Backward, LOW);
}

void stopMotors() {
  digitalWrite(motor1Forward, LOW);
  digitalWrite(motor1Backward, LOW);
  digitalWrite(motor2Forward, LOW);
  digitalWrite(motor2Backward, LOW);
}

void turn() {
  // Turn the car to the left
  digitalWrite(motor1Forward, LOW);
  digitalWrite(motor1Backward, HIGH);
  digitalWrite(motor2Forward, HIGH);
  digitalWrite(motor2Backward, LOW);
  delay(1000); // Turn for 1 second
  stopMotors(); // Stop after turning
}
