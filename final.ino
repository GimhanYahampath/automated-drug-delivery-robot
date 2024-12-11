// Define motor driver pins
#define enA 10 // Enable pin for motor 1
#define in1 9  // Control pin for motor 1
#define in2 8  // Control pin for motor 1
#define in3 7  // Control pin for motor 2
#define in4 6  // Control pin for motor 2
#define enB 5  // Enable pin for motor 2

// Define infrared sensor pins
#define R_S A0 // Right IR sensor
#define L_S A1 // Left IR sensor

// Define buzzer pin
#define buzzerPin 11

// Define movement duration (in milliseconds)
const unsigned long forwardDuration = 10000; // Adjust the time to follow the line forward (e.g., 10 seconds)
const unsigned long waitDuration = 120000;   // 2 minutes waiting

void setup() {
    // Set up pins for sensors, motors, and buzzer
    pinMode(R_S, INPUT);      // Right sensor input
    pinMode(L_S, INPUT);      // Left sensor input
    pinMode(enA, OUTPUT);     // Motor 1 enable
    pinMode(in1, OUTPUT);     // Motor 1 control
    pinMode(in2, OUTPUT);     // Motor 1 control
    pinMode(in3, OUTPUT);     // Motor 2 control
    pinMode(in4, OUTPUT);     // Motor 2 control
    pinMode(enB, OUTPUT);     // Motor 2 enable
    pinMode(buzzerPin, OUTPUT); // Buzzer output

    // Increase motor speed by raising PWM values
    analogWrite(enA, 200);    // Set higher speed for motor 1 (left motor)
    analogWrite(enB, 200);    // Set higher speed for motor 2 (right motor)
    delay(1000);              // Short delay to stabilize
}

void loop() {
    // Follow the line forward for a set duration
    unsigned long startTime = millis();
    while (millis() - startTime < forwardDuration) {
        followLine(); // Follow the line for the specified time
    }
    Stop();           // Stop the robot at the stopping point

    // Sound buzzer to indicate stopping point
    soundBuzzer();

    // Wait for 2 minutes (120000 milliseconds)
    delay(waitDuration);  // 2 minutes delay

    // Follow the line back to the start
    startTime = millis();
    while (millis() - startTime < forwardDuration) {
        followLine(); // Follow the line back for the same duration
    }
    Stop();           // Stop the robot

    // End of the task, stop the loop
    while(true);  // Keep the robot stopped indefinitely
}

// Line-following function using two IR sensors
void followLine() {
    int rightSensor = digitalRead(R_S);
    int leftSensor = digitalRead(L_S);

    if (rightSensor == 0 && leftSensor == 0) {
        moveForward(); // Move forward if both sensors detect white (on the line)
    } 
    else if (rightSensor == 1 && leftSensor == 0) {
        turnRight(); // Turn right if right sensor sees black
    } 
    else if (rightSensor == 0 && leftSensor == 1) {
        turnLeft(); // Turn left if left sensor sees black
    } 
    else {
        Stop(); // Stop if both sensors see black
    }
}

// Functions to control robot movement
void moveForward() {  // Move forward
    digitalWrite(in1, HIGH); // Motor 1 forward
    digitalWrite(in2, LOW);  // Motor 1 backward
    digitalWrite(in3, LOW);  // Motor 2 backward
    digitalWrite(in4, HIGH); // Motor 2 forward
}

void turnRight() { // Turn right
    digitalWrite(in1, LOW);  // Motor 1 backward
    digitalWrite(in2, HIGH); // Motor 1 forward
    digitalWrite(in3, LOW);  // Motor 2 backward
    digitalWrite(in4, HIGH); // Motor 2 forward
}

void turnLeft() { // Turn left
    digitalWrite(in1, HIGH); // Motor 1 forward
    digitalWrite(in2, LOW);  // Motor 1 backward
    digitalWrite(in3, HIGH); // Motor 2 backward
    digitalWrite(in4, LOW);  // Motor 2 forward
}

void Stop() { // Stop movement
    digitalWrite(in1, LOW); // Motor 1 forward
    digitalWrite(in2, LOW); // Motor 1 backward
    digitalWrite(in3, LOW); // Motor 2 backward
    digitalWrite(in4, LOW); // Motor 2 forward
}

void soundBuzzer() {
    // Make a sound with the buzzer
    tone(buzzerPin, 1000);  // Start the buzzer at 1000 Hz frequency
    delay(1000);            // Sound duration
    noTone(buzzerPin);      // Stop the buzzer
}
