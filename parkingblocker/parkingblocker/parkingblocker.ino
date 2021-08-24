#include <SoftwareSerial.h>
#include <Servo.h>

Servo servo3;
Servo servo5;
Servo servo7;
int angle = 0;

SoftwareSerial bt(8, 9);

void setup() {
  Serial.begin(9600);
  bt.begin(9600);
  servo3.attach(3);
  servo5.attach(5);
  servo7.attach(7);
}

void loop() {
  
  if(bt.available() > 0);
  char inputkey = bt.read();

  if(inputkey == '1') {
    angle += 90;
    servo3.write(angle);
    if(angle == 180) {
      angle = 0;
      servo3.write(angle);
    }
  }else if(inputkey == '2') {
    angle += 90;
    servo5.write(angle);
    if(angle == 180) {
      angle = 0;
      servo5.write(angle);
    }
  }else if(inputkey == '3') {
    angle += 90;
    servo7.write(angle);
    if(angle == 180) {
      angle = 0;
      servo7.write(angle);
    }
  }

}
