
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <dht.h>
dht DHT;
#define DHT11_PIN 6
RF24 radio(7, 8);  // CE, CSN
const byte address[6] = "00001";
int temp;
int finger1;
int finger2;
int finger3;
int AngleX;
int AngleY;
int AngleZ;
int nextcount = 0;
int nextcount1 = 0;
int nextcount2 = 0;
int nextcount3 = 0;
int relay = 1;
int gpscheck=0;
int tlat=3796;
int tlng=4899;
int gpsreceive=0;
int gpsbugfix;
float dhttimer=0;
String gpsfinal;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.startListening();
//Serial.println('start');
}

void loop() {
  if (radio.available())
  {
    int text = 0;
     radio.read(&text, sizeof(text));

  if(String(text).length()==4)
  {
    if (gpscheck==0){
      tlat=text;
      //Serial.println(tlat);
      gpscheck=1;
      }
    else if(gpscheck==1){
      tlng=text;
      //Serial.println(tlng);
      gpscheck=0;
      gpsreceive=1;
      gpsfinal="g"+String(3140)+String(5138);
      //Serial.println(gpsfinal);
      //Serial1.println(gpsfinal);
      //delay(100);

      
      
      }
  }
  else{ 
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
                      temp+=1;
                      }
    else if(temp==5){ Serial.print("AngleZ:-");
                      Serial.println(text);
                      AngleZ=text;
                      temp+=1;
                      
                      if (millis()>3000)
                      {
                        if (AngleY>70)
                          { 
                           if (nextcount<10)
                            {
                              nextcount=nextcount+1;
                            }
                            else
                            { Serial.println("n");
                              Serial1.println("n");
                              nextcount=0;
                            }

                          }
                         else
                         {
                          nextcount=0;
                         }
                        if (finger1>930)
                          { 
                           if (nextcount1<10)
                            {
                              nextcount1=nextcount1+1;
                            }
                            else
                            { Serial.println("s");
                              Serial1.println("s");
                              nextcount1=0;
                            }

                          }
                         else
                         {
                          nextcount1=0;
                         }

                         
                         //if (finger2>935 and AngleY<-50)
                         if (AngleY<-50)
                          { 
                           if (nextcount2<10)
                            {
                              nextcount2=nextcount2+1;
                            }
                            else
                            { 
                                Serial.println("yay");
                                if (relay==0)
                                {
                                  relay=1;
                                  digitalWrite(5, HIGH);
                                  Serial1.println('w');
                                }
                                else if(relay==1)
                                {
                                  relay=0;
                                  digitalWrite(5, LOW);
                                  Serial1.println('q');
                                }                              
                              
                              nextcount2=0;
                            }

                          }
                         else
                         {
                          nextcount2=0;
                         } 
                      if (AngleX>30)
                          { 
                           if (nextcount3<20)
                            {
                              nextcount3=nextcount3+1;
                            }
                            else
                            
                            {gpsfinal="g"+String(3140)+String(5138);
                              Serial.println(gpsfinal);
                              Serial1.println(gpsfinal);
                              nextcount3=0;
                            }                         
                      }
                     //Temprature, HUmitidty
                     if(dhttimer==0)
                     {
                     int chk = DHT.read11(DHT11_PIN);
                     String dhtstr="v"+String(int(DHT.temperature))+String(int(DHT.humidity));
                     Serial.println(dhtstr);
                     Serial1.println(dhtstr);
                     dhttimer=1;
                     }
                      }                      
    }
  }
}
}
