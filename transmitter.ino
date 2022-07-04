#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8);  // CE, CSN
const byte address[6] = "00001";
int temp;
int finger1;
int finger2;
int finger3;
int AngleX;
int AngleY;
int AngleZ;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.startListening();
}

void loop() {
  if (radio.available())
  {
    int text = 0;
     radio.read(&text, sizeof(text));
    if (text==29811)
    {
      temp=0;
    }
    else if(temp==0){ Serial.print("Finger 1:-");
                      Serial.print(text);
                      finger1=text;
                      temp+=1;}
    else if(temp==1){ Serial.print("Finger 2:-");
                      Serial.print(text);
                      finger2=text;
                      temp+=1;}    
    else if(temp==2){ Serial.print("Finger 3:-");
                      Serial.print(text);
                      finger3=text;
                      temp+=1;}    
    else if(temp==3){ Serial.print("AngleX:-");
                      Serial.print(text);
                      AngleX=text;
                      temp+=1;}
    else if(temp==4){ Serial.print("AngleY:-");
                      Serial.print(text);
                      AngleY=text;
                      temp+=1;}
    else if(temp==5){ Serial.print("AngleZ:-");
                      Serial.println(text);
                      AngleZ=text;
                      temp+=1;}                      
    }

  // put your main code here, to run repeatedly:

}
