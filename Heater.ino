int heater = 13; // digital pin 13, built-in LED to indicate state of heater
int ThermistorPin = 0; // analog pin 0

int Vo;
float R1 = 1000; // R1 value (10,000k ohms)
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07; // constants
boolean heaterState = false;

int maxTemp = 35, minTemp = 30; // temp range

void setup() {
   pinMode(heater, OUTPUT); // heater pin 13 init
   Serial.begin(9600); // baud rate: 9600
}

void resistorCalculations(){ // thermistor calculations
  
  Vo = analogRead(ThermistorPin); // analogRead function to read voltage value
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15;
  
}

void loop() {
  
  resistorCalculations(); // method call
  //Serial.println("");
  Serial.print("\nTemperature: "); // serial messages
  Serial.print(T); // temp value in celsius
  Serial.println(" C"); // label

  if (heaterState) { // prints heater state based on boolean state 
    Serial.println("Heater on and warming up");
  }
  if (!heaterState) { // same thing
    Serial.println("Heater off and cooling down");  
  }
  
  delay(2000);
  
  // if temp too hot, turn heater off
  if ( T >= maxTemp){ // max temp  
    digitalWrite(heater, LOW);  
    heaterState = false; // heater off  
  } 
  
  // if temp too cold, turn heater on
  else if (T <= minTemp) {// min temp
    digitalWrite(heater, HIGH);
    heaterState = true; // heater on
  }
}
