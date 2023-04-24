int heater = 3; // digital pin 3 on attiny
float reading, voltage;
float T;

int maxTemp = 35, minTemp = 25; // temp range

void setup() {
   pinMode(heater, OUTPUT); // heater init
   Serial.begin(9600); // baud rate: 9600
}
  
void tempCalc(){ // thermistor calculations
  voltage = analogRead(A1); // analogRead function to read voltage value, pin A1
  float mv = voltage / 1024 * 5 * 1000; //find percentage of input reading
  T = (mv - 0.5) / 10; //Convert to degrees
}

void loop() {
  
  tempCalc(); // method call
  
  delay(2000);
  // if temp too hot, turn heater off
  if ( T >= maxTemp){ // max temp  
    digitalWrite(heater, LOW);  
  } 
  
  // if temp too cold, turn heater on
  else if (T <= minTemp) {// min temp
    digitalWrite(heater, HIGH);
  }
}
