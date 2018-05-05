void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while(!Serial)
  {
    //
  }
  Serial.println("Analog input (ADC 10 bits)");
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue = analogRead(A0);
  float volts = 3.3 * (float) sensorValue/1023;
  Serial.print("ADC Read = ");
  Serial.print(sensorValue);
  Serial.print("        ");
  Serial.print("Voltage = ");
  Serial.print(volts, 2);
  Serial.print(" V");
  delay(1000);
}
