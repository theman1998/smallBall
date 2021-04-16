#include <SoftwareSerial.h>
#include <Wire.h>
#include "MAX30105.h"

#define TxD 6//3
#define RxD 7//4
SoftwareSerial BTserial(RxD, TxD); // RX, TX for Bluetooth

//variables
const long baudRate = 9600; 
char com;

//prototypes
void checkSerials(), btSendData(char* data1), btSendData(int data1);


void setup() {
    Serial.begin(baudRate);
    Serial.println(" ");
 
    BTserial.begin(baudRate);  
    Serial.print("BTserial started at "); Serial.println(baudRate);

}

void loop() {
  checkSerials();
  // put your main code here, to run repeatedly:

}
int tmpCounter = 0;
void checkSerials(){
  
  String phrase;
    // Read from the Bluetooth module and send to the Arduino Serial Monitor
    if (BTserial.available())
    {
    delay(10);
      tmpCounter++;
      phrase = "";
      int tmmp = 0;
      while(BTserial.available() > 0){
        tmmp++;
        if(tmmp >= 19)break;
    char tmp = BTserial.read();
    phrase += tmp;
      }
    if(phrase.length() > 0){
      Serial.print(phrase);
      Serial.print("  ");
      Serial.println(tmpCounter);
     }
      //Serial.read();
      if(!BTserial.available()){
      const char * at = phrase.c_str();
      BTserial.write("roger that 10-4,");
      BTserial.write(at);
      BTserial.read();
      }
      }
    
     //if (BTserial.available())BTserial.read();
     //BTserial.write(com); //use this and
     //BTserial.read();     // this to write back to it self need to read to clear buffer
  
    // Read from the Serial Monitor and send to the Bluetooth module
   if (Serial.available()){ 
      com = Serial.read();
      BTserial.write(com);


      Serial.println("in the serial");
      if(!Serial.available()) BTserial.write("\n");
      
      delay(10);
    }  
     
  }

void btSendData(char* data1){
      BTserial.write(data1);
      BTserial.read();
  }
void btSendData(int data1){
  
      Serial.println("=================================================================");
      int counterA = 0; //make int into asc2
      for (int i = data1; i > 0;){
        counterA++;
        i = i/10;
        }
      for(; counterA > 0;  counterA--){
      int tmp;
      tmp = (data1/(int)pow(10,(counterA-1)))%10;
     
      char tmpChar = tmp + '0';  //asc conversion
      BTserial.write(tmpChar);
      
      
      }
      BTserial.write("\n");
      BTserial.read();
  }
