#include <Manchester.h>
#include <Servo.h>
#define servo_pin 9
#define thrust_pin 5
#define holder_pin 6
#define receiver_pin 13 
uint8_t buffer[4];
Servo spoiler;
int degree,thrust;
int checking1=0;
int checking2=0;
int counter=0;

void setup() {
  spoiler.attach(servo_pin,500,2400);
  pinMode(thrust_pin,OUTPUT);
  pinMode(holder_pin,OUTPUT);
  man.setupReceive(receiver_pin,MAN_1200);
  man.beginReceiveArray(4,buffer);
  spoiler.write(90);
}

void loop() {
  if(man.receiveComplete()){
    degree=easyconvert(buffer[3]);
    //degree=JoystickToServo(buffer[2],buffer[3]);
    // *wait 3 signals before changing relay state
    if(buffer[1]!=checking1){
      if(checking2<3) checking2++;
      else{
        checking2=0;
        checking1=buffer[1];
        digitalWrite(holder_pin,buffer[1]); 
      }
    }
    else checking2=0;
    if(buffer[2]>140) digitalWrite(thrust_pin,HIGH);
    else digitalWrite(thrust_pin,LOW);
    if (counter>10){
      counter=0;
      spoiler.write(degree);
    }
    man.beginReceiveArray(4,buffer);
    counter++;
  }
}
/*
int JoystickToServo(int y,int x){
  int result;
  if(y==135&&x>=115&&x<=130)
    return 90;
   else if(y>60&&x==255)
    return 45;
   else if(y>60&&x==0)
    return 135;
   else if(y==255)
    return 90;
   else if(y<135&&x!=0&&x!=255){
    if(x-128>0){
      result=atan((y-128)/(x-128));
      return(result/2);
    }
    else{
      result=atan((y-128)/(128-x));
      return ((180-result)/2);
    }
   }
}*/
int easyconvert(int v){
  if(v<=130&&v>=115)
    return 90;
  else
    return map(v,0,255,165,15);
}
