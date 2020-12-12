int A_1A = 11;
int A_2A = 12;

void setup()
{
  pinMode(4, INPUT);
  pinMode(A_1A, OUTPUT);
  pinMode(A_2A, OUTPUT);
}

void loop() {
  pump(1);
  delay(1000);
  stop();
  delay(1000);
}
  

void pump(int flag)
{
  boolean inPin1 = HIGH;
  boolean inPin2 = LOW;
  
  if(flag == 1) {
    inPin1 = HIGH;
    inPin2 = LOW;
  }
  digitalWrite(A_1A, inPin1);
  digitalWrite(A_2A, inPin2);
}

void stop() {
  digitalWrite(A_1A, LOW);
  digitalWrite(A_2A, LOW);
}
