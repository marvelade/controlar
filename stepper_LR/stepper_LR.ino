
// Include the Stepper Library
#include <Stepper.h>


// Map our pins to constants to make things easier to keep track of
const int pwmA = 3;
const int pwmB = 11;
const int brakeA = 9;
const int brakeB = 8;
const int dirA = 12;
const int dirB = 13;

// The amount of steps for a full revolution of your motor.
// 360 / stepAngle
const int STEPS = 200;

// Initialize the Stepper class
Stepper myStepper(STEPS, dirA, dirB);

// the setup routine runs once when you press reset:
void setup() {
  // Set the RPM of the motor
  myStepper.setSpeed(40);

  // Turn on pulse width modulation
  pinMode(pwmA, OUTPUT);
  digitalWrite(pwmA, HIGH);
  pinMode(pwmB, OUTPUT);
  digitalWrite(pwmB, HIGH);

  // Turn off the brakes
  pinMode(brakeA, OUTPUT);
  digitalWrite(brakeA, LOW);
  pinMode(brakeB, OUTPUT);
  digitalWrite(brakeB, LOW);

  // Log some shit
  Serial.begin(9600);
}

float prev = 0.0;
// potmeter doesn't make the full sweep to 1024, so we'll have 
// to specify the max value manually
float sensorMaxValue = 781.0;
float logPotCorrectionConstant = 0.3;

// the loop routine runs over and over again forever:
void loop()
{
  

  
  myStepper.step(10);
  
  delay(500);
  
  myStepper.step(-1);
  
  delay(500);



}
