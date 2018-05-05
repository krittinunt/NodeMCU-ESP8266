#define LED1    D0
#define LED2    D1
#define LED3    D2
#define SW1     D3
#define SW2     D4
#define SW3     D5

void setup() {
  // put your setup code here, to run once:
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);
  pinMode(SW3, INPUT);

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(SW1) == LOW)
  {
    delay(100);
    while(digitalRead(SW1) != HIGH);
    delay(100);
    digitalWrite(LED1, !digitalRead(LED1));
  }

  if (digitalRead(SW2) == LOW)
  {
    delay(100);
    while(digitalRead(SW2) != HIGH);
    delay(100);
    digitalWrite(LED2, !digitalRead(LED2));
  }

  if (digitalRead(SW3) == LOW)
  {
    delay(100);
    while(digitalRead(SW3) != HIGH);
    delay(100);
    digitalWrite(LED3, !digitalRead(LED3));
  }
}
