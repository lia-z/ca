int trigPin_A1 = 6;
int echoPin_A1 = 7;
int trigPin_A2 = 4;
int echoPin_A2 = 5;
long distance_A1; // 거리값을 저장할 변수
long distance_A2;
long duration_A1;
long duration_A2;

void setup(){
  Serial.begin(9600);       // 시리얼 속도 설정      
  pinMode(echoPin_A1, INPUT);   // echoPin 입력    
  pinMode(trigPin_A1, OUTPUT);  // trigPin 출력
  pinMode(echoPin_A2, INPUT);   // echoPin 입력    
  pinMode(trigPin_A2, OUTPUT);  // trigPin 출력
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
}
 
void loop(){
  digitalWrite(trigPin_A1, HIGH);  // trigPin에서 초음파 발생(echoPin도 HIGH) 
  delayMicroseconds(10);
  digitalWrite(trigPin_A1, LOW);
  duration_A1 = pulseIn(echoPin_A1, HIGH);    // echoPin 이 HIGH를 유지한 시간을 저장 한다.
  distance_A1 = ((float)(340 * duration_A1) / 1000) / 2; 
  
  
  //Serial.print("Duration:");   //시리얼모니터에 Echo가 HIGH인 시간을 표시
 // Serial.print(duration);
 
  Serial.print("\nDIstance1:"); // 물체와 초음파 센서간 거리를 표시        
  Serial.print(distance_A1);
  Serial.println("mm\n");

  delay(500);
  
  digitalWrite(trigPin_A2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_A2, LOW);
  duration_A2 = pulseIn(echoPin_A2, HIGH);
  distance_A2 = ((float)(340 * duration_A2) / 1000) / 2;

  Serial.print("\nDIstance2:"); // 물체와 초음파 센서간 거리를 표시  
  Serial.print(distance_A2);
  Serial.println("mm\n");

  delay(500);

  if(distance_A1 > 30 && distance_A1 < 150){
    digitalWrite(10,LOW);
  }
  else{
    digitalWrite(10,HIGH);
  }


  if(distance_A2 > 30 && distance_A2 < 150){
    digitalWrite(11,LOW);
  }
  else{
    digitalWrite(11,HIGH);
  }
 
  delay(1000);
}  
