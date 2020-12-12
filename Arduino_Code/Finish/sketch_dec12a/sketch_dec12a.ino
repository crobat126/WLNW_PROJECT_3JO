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
  sensorVal = analogRead(A0Pin);  // 토양 센서 값 읽어 저장
  delay(1000);
  //Serial.print("Asensor = ");
  //Serial.println(sensorVal);  // 0(습함) ~ 1023(건조)값 출력 

  // 토양이 습할 경우
  if ( sensorVal <= 500) 
  {    
    //Serial.println(" Very Wet ! ");  
    Serial.println(sensorVal); // 토양의 습도 값(수치) 콘솔에 출력    
    stop();   
  }
  // 토양이 건조할 경우
  else if ( sensorVal > 500)
  {
    //Serial.println(" Very Dry ! ");  
    Serial.println(sensorVal); // 토양의 습도 값(수치) 콘솔에 출력   
    pump(1); // 워터 펌프 작동
    //Serial.println(" Pump On for 5 Second!");    
    delay(5000); // 5초 주기로 딜레이
  }    
}
  
// 워터 펌프 작동 함수
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