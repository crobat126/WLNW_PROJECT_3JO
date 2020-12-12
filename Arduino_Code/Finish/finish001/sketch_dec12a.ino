/* Auto Water Pot - 자동 물공급 화분 */
#define A0Pin 0
int sensorVal = 0;
int A_1A = 11;
int A_2A = 12;

void setup()
{
  Serial.begin(9600);   
  pinMode(4, INPUT);
  pinMode(A_1A, OUTPUT);
  pinMode(A_2A, OUTPUT);
}

void loop() 
{
  sensorVal = analogRead(A0Pin);  // 토양센서값 읽어 저장
  delay(1000);
  Serial.print("Asensor = ");
  Serial.println(sensorVal);  // 0(습함) ~ 1023(건조)값 출력 
  if ( sensorVal <= 500) 
  {    
    Serial.println(" Very Wet ! ");        
    stop();   
  }
  else if ( sensorVal > 500)
  {
    Serial.println(" Very Dry ! ");    
    pump(1);
    Serial.println(" Pump On for 1 Second!");    
    delay(1000);
  }    
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
