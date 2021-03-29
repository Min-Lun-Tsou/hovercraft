
#include <Manchester.h>

#define buttonpin 0
#define TX_PIN  1
#define FBpot A3
#define LRpot A2  
uint8_t data[4] = {4,1,2,3};
uint8_t datalength=4;
uint8_t LR,FB;
uint8_t Button=0;
bool flag;

void setup() 
{
  pinMode(buttonpin,INPUT_PULLUP);
  man.setupTransmit(TX_PIN, MAN_1200);
}



void loop() 
{
  data[0] = datalength;
  if(ButtonDetect()) Button=!Button;
  data[1]=Button;
  LR=analogRead(LRpot)/4;
  data[3]=LR;
  FB=analogRead(FBpot)/4;
  data[2]=FB;
  man.transmitArray(datalength, data);
  delay(1);
}

bool ButtonDetect() {
  if (!digitalRead(buttonpin)) flag=1;
  if (digitalRead(buttonpin)&&flag){
    flag=0;
    return 1;
  }
  else return 0;
}
