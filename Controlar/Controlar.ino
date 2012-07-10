
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
  myStepper.setSpeed(100);

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
  

  // Read the position of the 2 limiter pots
  float limMin = analogRead(A4);
  float limMinNorm = limMin/1024;
  
  float limMax = analogRead(A5);
  float limMaxNorm = limMax/1024;
  
  float limDeltaNorm = limMaxNorm - limMinNorm;
  
  // read the input on analog pin 2 and linearize:
  float sensorValue = pow((analogRead(A2)/sensorMaxValue), logPotCorrectionConstant);
  
  
  // map the sensor value to the range set by the 2 limiter pots
  float val = limMinNorm + (limDeltaNorm * sensorValue);
  
  Serial.print("val: ");
  Serial.println(val);
  
  float diff = round((val - prev)*160); 
  
   Serial.print("sensorValue: ");
   Serial.println(sensorValue);
   
   Serial.print("limMinNorm: ");
   Serial.println(limMinNorm);
   
   Serial.print("limMaxNorm: ");
   Serial.println(limMaxNorm);
  
  
  Serial.print("diff: ");
  Serial.println(diff);

  myStepper.step(diff);
  prev = val;

  
  
  
  Serial.println("-------");
  delay(10);
}
