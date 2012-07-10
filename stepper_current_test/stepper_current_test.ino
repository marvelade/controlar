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

void loop()
{
  
   float currentA = analogRead(A0);
   float currentB = analogRead(A1);
   float totalCurrent = currentA+currentB;
   
   Serial.print("current: ");
   Serial.println(totalCurrent);
   if(totalCurrent > 600.0)
   {
     Serial.println("Current too high. Stalling.");
   }
   else
   {
       
     Serial.println("Current OK. Stepping.");
     myStepper.step(11);
   }
  
  delay(100);
}
