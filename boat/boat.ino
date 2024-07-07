#include <Arduino.h>
#include <Servo.h>

// Define pin connections
#define THROTTLE_PIN D1
#define STEERING_PIN D2
#define ESC_PIN D3
#define SERVO_PIN D4

// Create servo object
Servo steeringServo;

void setup() {
  Serial.begin(9600);

  // Initialize pins
  pinMode(THROTTLE_PIN, INPUT);
  pinMode(STEERING_PIN, INPUT);
  
  // Attach the servo on SERVO_PIN to the servo object
  steeringServo.attach(SERVO_PIN);
  
  // Initialize ESC
  pinMode(ESC_PIN, OUTPUT);
  analogWriteFreq(50); // Set frequency for ESC
}

void loop() {
  // Read values from FlySky receiver
  int throttleValue = pulseIn(THROTTLE_PIN, HIGH);
  int steeringValue = pulseIn(STEERING_PIN, HIGH);

  // Map the receiver values to appropriate ranges
  int escValue = map(throttleValue, 1000, 2000, 0, 1023); // Map to ESC range (0-1023)
  int servoValue = map(steeringValue, 1000, 2000, 0, 180); // Map to Servo range (0-180)

  // Control the ESC (BLDC motor speed)
  analogWrite(ESC_PIN, escValue);
  
  // Control the Servo (steering)
  steeringServo.write(servoValue);

  // Debugging output
  Serial.print("Throttle: ");
  Serial.print(throttleValue);
  Serial.print(" -> ESC: ");
  Serial.print(escValue);
  Serial.print("\tSteering: ");
  Serial.print(steeringValue);
  Serial.print(" -> Servo: ");
  Serial.println(servoValue);

  // Small delay for stability
  delay(20);
}

