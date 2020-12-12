/* Auto Water Pot - 자동 물공급 화분 */
#define A0Pin 0
int sensorVal = 0;
int pump = 13;
void setup() {
  Serial.begin(9600);
  pinMode(pump, OUTPUT);
}
void loop() {
  sensorVal = analogRead(A0Pin);  // 토양센서값 읽어 저장
  delay(1000);
  Serial.print("Asensor = ");
  Serial.println(sensorVal);  // 0(습함) ~ 1023(건조)값 출력 
  // 습도 값에 따라 출력 처리 다르게 해줌
  if ( sensorVal <= 500) {    
    Serial.println(" Very Wet ! ");        
    digitalWrite(pump, LOW);    
  }
/*  if (sensorVal > 500 && sensorVal <= 1000) {
    Serial.println(" It's OK ! ");    
    digitalWrite(pump, LOW);
    delay(500);
  }
*/
  else if ( sensorVal > 500){
    Serial.println(" Very Dry ! ");    
    digitalWrite(pump, HIGH);
    Serial.println(" Pump On for 1 Second!");    
    delay(1000);
  }    
  delay(3000); //정보수집 시간(간격) 설정
}
