
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
  myStepper.setSpeed(300);

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

int prev = 0;
// potmeter doesn't make the full sweep to 1024, so we'll have 
// to specify the max value manually
int sensorMaxValue = 800;
float logPotCorrectionConstant = 0.3;

// the loop routine runs over and over again forever:
void loop()
{
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);

  // Read the position of the other 2 pots
  int limMin = analogRead(A3);
  float limMinNorm = limMin / 1023.0;
  int limMax = analogRead(A5);
  float limMaxNorm = limMax / 1023.0;
  
  float limDeltaNorm = limMaxNorm - limMinNorm;
  
  
  // To obtain a (sort of) linear signal from a log pot, 
  // we need to raise the value to a certain power 0 ... 1
  float linLevelNorm = (pow(sensorValue, logPotCorrectionConstant))/pow(sensorMaxValue, logPotCorrectionConstant) ;
  
 
  
  float scaledLevelNorm = limMinNorm + (limDeltaNorm * linLevelNorm);
  int val = (200*scaledLevelNorm);
  int diff = val - prev; 
  
  Serial.println("diff");
  Serial.println(diff);
  
  Serial.println("----------------");
  myStepper.step(diff);
  prev = val;

  
  
  // print out the value you read:
  Serial.println(linLevelNorm);
  Serial.println(sensorValue);
  Serial.println("");
  Serial.println(limMinNorm);
  Serial.println(limMaxNorm);
  Serial.println("");
  Serial.println(scaledLevelNorm);
  Serial.println("-------");
  delay(10);
}
