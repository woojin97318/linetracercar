#include<SoftwareSerial.h>
SoftwareSerial bluetooth(8, 9);

const int AIA = 5;  //우 뒤
const int AIB = 6;  //우 앞
const int BIA = 10; //좌 뒤
const int BIB = 11; //좌 앞

const int SensorLeft = 2;
const int SensorRight = 3;

int trig = 13;
int echo = 12;

#define FAST 180
#define MIDDLE 155
#define SLOW 130
#define SLOWER 105

void setup() {
  bluetooth.begin(9600);  // 블루투스 통신 속도 설정
  
  pinMode(AIA,OUTPUT);
  pinMode(AIB,OUTPUT);
  pinMode(BIA,OUTPUT);
  pinMode(BIB,OUTPUT);

  pinMode(SensorLeft,INPUT);
  pinMode(SensorRight,INPUT);

  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  
}

void loop() {
  if(bluetooth.available()) {
   char data = (char)bluetooth.read();   // 블루투스 들어오는값 저장 data
    if(data == '1') {
      CarGo();
    }else if(data == '2') {
      CarBack();
    }else if(data == '3') {
      CarRight();
    }else if(data == '4') {
      CarLeft();
    }else if(data == '5') {
      CarStop();
    }else if(data == '6') {
      CarAuto();
    }
  }
}

void CarAuto(){
  while(!bluetooth.available()) {
   digitalWrite(trig, LOW); 
   delayMicroseconds(2);     
   digitalWrite(trig, HIGH); 
   delayMicroseconds(10);    
   digitalWrite(trig, LOW);
   unsigned long duration = pulseIn(echo,HIGH);
   float distance = ((float)(340*duration)/10000)/2; 
    
   int SL, SR;
   SL = digitalRead(SensorLeft);
   SR = digitalRead(SensorRight);

   if(distance <= 5) {
    CarStop();
   }else {
    if(SL == HIGH && SR == HIGH) {
      CarGo();
    }else if(SL == LOW && SR == HIGH) {
      CarRight();
    }else if(SL == HIGH && SR == LOW) {
      CarLeft();
    }else {
      CarStop();
    }
   }
  }
}

void CarGo(){
  //모터의 물리적 힘차이로 인해 모터마다 주는 힘이 다름
  while(!bluetooth.available()) {
    analogWrite(AIA,0);       // 우 뒤
    analogWrite(AIB,FAST);    // 우 앞
    analogWrite(BIA,0);       // 좌 뒤
    analogWrite(BIB,MIDDLE);  // 좌 앞
    break;
  }
}

void CarBack(){
  while(!bluetooth.available()) {
    analogWrite(AIA,FAST);
    analogWrite(AIB,0);
    analogWrite(BIA,MIDDLE);
    analogWrite(BIB,0);
    break;
  }
}

void CarRight(){
  while(!bluetooth.available()) {
    analogWrite(AIA,0);
    analogWrite(AIB,0);
    analogWrite(BIA,0);
    analogWrite(BIB,MIDDLE);
    break;
  }
}

void CarLeft(){
  while(!bluetooth.available()) {
    analogWrite(AIA,0);
    analogWrite(AIB,FAST);
    analogWrite(BIA,0);
    analogWrite(BIB,0);
    break;
  }
}

void CarStop(){
  while(!bluetooth.available()) {
    analogWrite(AIA,0);
    analogWrite(AIB,0);
    analogWrite(BIA,0);
    analogWrite(BIB,0);
    break;
  }
}
