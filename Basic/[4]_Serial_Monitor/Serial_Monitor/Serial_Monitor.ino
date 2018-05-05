int i = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while(!Serial)
  {
    //
  }
  Serial.println("Serial monitor starting...");
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(i);
  delay(1000);
  i++;
}
