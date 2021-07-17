#include<RH_ASK.h>
#include<SPI.h>
RH_ASK driver;
void setup() {
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  pinMode(8,OUTPUT);
  if(driver.init())
  {
    for(int x=1;x<3;x++)
    {
      digitalWrite(13,HIGH);
      delay(2000);
      digitalWrite(13,LOW);
      delay(2000);
    }
  }
  else
  {
    for(int x=1;x<6;x++)
    {
      digitalWrite(13,HIGH);
      delay(300);
      digitalWrite(13,LOW);
      delay(300);
    }
  }
}
bool isOn=false;
void loop() {
  uint8_t arr[25];
  uint8_t arrLen=sizeof(arr);
  int input;
  int x;
  if(driver.recv(arr,&arrLen))
  {
    input=arr[0];
    if(input>=1 && input<=2)
    {
      if(input==2)
      {
        if(isOn)
        {
          digitalWrite(8,LOW);
          delay(500);
        }
        else
        {
          digitalWrite(8,HIGH);
          delay(500);
        }
        isOn=!isOn;
      }
    }
  }
}