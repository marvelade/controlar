
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  
  // potmeter doesn't make the full sweep to 1024, so we'll have 
  // to specify the max value manually
  int sensorMaxValue = 770;

  // Read the position of the other 2 pots
  int limmin = analogRead(A1);
  int limmax = analogRead(A2);
  

  float voltage1 = sensorValue + 2; // this needs some work :s
  // print out the value you read:
  Serial.println(voltage1);
  Serial.println(sensorValue);
  Serial.println("");
  delay(250);
}
