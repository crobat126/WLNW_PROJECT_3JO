/* Auto Water Pot - 자동 물공급 화분 */
#define A0Pin 0 // 토양 습도 센서 
int sensorVal = 0; /* 토양 센서 값 */ 
int A_1A = 11; /* 워터 펌프 센서 */
int A_2A = 12; /* 워터 펌프 센서 */

void setup()
{
  Serial.begin(9600);   //시리얼 포트 9600 
  pinMode(4, INPUT); //4번핀을 INPUT으로 설정
  pinMode(A_1A, OUTPUT); //모터드라이브 A_1A의 pinMode 선언
  pinMode(A_2A, OUTPUT); //모터드라이브 A_2A의 pinmode 선언
}

void loop()
{
  sensorVal = analogRead(A0Pin);  // 토양 센서 값 읽어 저장
  delay(1000);
  //Serial.print("Asensor = ");
  //Serial.println(sensorVal);  // 0(습함) ~ 1023(건조)값 출력 

  // 토양이 습할 경우 (기준 600)
  if ( sensorVal <= 600) 
  {    
    //Serial.println(" Very Wet ! ");  
    Serial.println(sensorVal); // 토양의 습도 값(수치) 콘솔에 출력    
    stop();   
  }
  // 토양이 건조할 경우 (기준 600)
  else if ( sensorVal > 600)
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
  boolean inPin1 = HIGH;  //boolean inPin1 = 1
  boolean inPin2 = LOW;   //boolean inPin2 = 0
  
  if(flag == 1) {
    inPin1 = HIGH; //서로 값이 달라야 정방향, 역방향 회전
    inPin2 = LOW; //모터가 약할시에 역방향 회전으로 pin1, pin2의 값을 바꿔준다.
  }
  digitalWrite(A_1A, inPin1); // digital방식으로 output을 해준다.
  digitalWrite(A_2A, inPin2); // digital방식으로 output을 해준다.
}

void stop() {
  digitalWrite(A_1A, LOW); // digital방식으로 output을 해준다.
  digitalWrite(A_2A, LOW); // digital방식으로 output을 해준다.
}
