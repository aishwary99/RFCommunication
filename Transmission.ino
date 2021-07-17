#include<RH_ASK.h>
#include<SPI.h>
RH_ASK driver;
int buttonOld[2]={0,0};
int buttonNew[2]={0,0};
int i,j;
void setup()
{
  Serial.begin(9600);
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(13,OUTPUT);
  if(driver.init())
  {
    for(int x=1;x<=2;x++)
    {
      digitalWrite(13,HIGH);
      delay(2000);
      digitalWrite(13,LOW);
      delay(2000);
    }
  }
  else
  {
    for(int x=1;x<=5;x++)
    {
      digitalWrite(13,HIGH);
      delay(300);
      digitalWrite(13,LOW);
      delay(300);
    }
  }
}
void loop() {
    int arr[2];
    for(i=2;i<=3;i++)
    {
      buttonNew[i-2]=digitalRead(i);
      if(buttonNew[i-2]==1 && buttonOld[i-2]==0)
      {
        Serial.print("Key pressed : ");
        Serial.println(i-1);
        tone(8,400);
        delay(100);
        noTone(8);
        int key=i-1;
        if(key>=1 && key<=2)
        {
          arr[0]=key;
          arr[1]='\0';
          driver.send((uint8_t *)arr,1);
          driver.waitPacketSent();
        }
      }
      buttonOld[i-2]=buttonNew[i-2];
    }  
}