
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
  int sensorMaxValue = 800;
  float logPotCorrectionConstant = 0.3;
  

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
  
  
  // print out the value you read:
  Serial.println(linLevelNorm);
  Serial.println(sensorValue);
  Serial.println("");
  Serial.println(limMinNorm);
  Serial.println(limMaxNorm);
  Serial.println("");
  Serial.println(scaledLevelNorm);
  Serial.println("-------");
  delay(250);
}
