#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

int i=0; //initiarize
int w=119;
int r=114;
int DeviceAddress = 0A; // 0b1100000 96
  
int Address[100]={
  0, // Device Status
  177, // software reset
  15, // PLLA_SRC
  183, // CL
  28, // MSNA_P1[17:16] 
  29, // MSNA_P1[15:8]  
  30, // MSNA_P1[7:0]
  31, // MSNA_P3[19:16] MSNA_P2[19:16]
  32, // MSNA_P2[15:8]
  33, // MSNA_P2[7:0]
  34, // MSNA_P3[15:8]
  35, // MSNA_P3[7:0]
  42, // MS0_P3[15:8]
  43, // MS0_P3[7:0]
  44, // MS0_P1[17:16]
  45, // MS0_P1[15:8]
  46, // MS0_P1[7:0]
  47, // MS0_P3[19:16] MS0_P2[19:16]   
  48, // MS0_P2[15:8]
  49, // MS0_P2[7:0]
  };

int Value[100]={
  0, // Device Status
  0, // software reset
  0, // PLLA_SRC
  146, // CL=8pF
  0, // MSNA_P1[15:8]  
  0, // MSNA_P1[7:0]
  0, // MSNA_P2[15:8]
  0, // MSNA_P2[7:0]
  0, // MSNA_P3[15:8]
  0, // MSNA_P3[7:0]
  0, // MS0_P3[15:8]
  0, // MS0_P3[7:0]
  0, // MS0_P1[17:16]
  0, // MS0_P1[15:8]
  0, // MS0_P1[7:0]
  0, // MS0_P3[19:16] MS0_P2[19:16]   
  0, // MS0_P2[15:8]
  0, // MS0_P2[7:0]
  };

void loop() {
  delay(100);
  Serial.println("Please send command either w or r");
  delay(1000);
  Serial.print("Serial.available()=");
  Serial.println(Serial.available());
  if(Serial.available()>0){
    Serial.println("Serial avalable!");
    int x=0;
    x = Serial.read();
    Serial.print("x=");
    Serial.println(x,DEC);
    if(x==w){
      Serial.println("Write");
      WriteReg();
      }
    if(x==r){ 
      Serial.println("Read");
      ReadReg();
      }
    }
  }

void WriteReg(){
  for (i=0; i<100; i++) {
    Wire.beginTransmission(DeviceAddress);
    Wire.write(Address[i]);
    Wire.write(Value[i]);    
    Wire.endTransmission(false);
    Insert0x0(Address[i]);
    Serial.print(Address[i],HEX);
    Serial.print("=");
    Insert0x0(Value[i]);
    Serial.println(Value[i], HEX);
    delay(0);
  } while(1){}//finalize
  }

void ReadReg(){
  for (i=0; i<10; i++) { 
  Wire.beginTransmission(DeviceAddress);
  Wire.write(Address[i]);
  Wire.endTransmission(false);
  Wire.requestFrom(DeviceAddress, 1,true);
  Value[i] = Wire.read();
  //Insert0x0(Address[i]);
  Serial.print(Address[i],DEC);
  Serial.print("=");
  //Insert0x0(Value[i]);
  Serial.println(Value[i],DEC);
  delay(0);
  } while(1){}//finalize
  }

void Insert0x0(int num){
  Serial.print("0x");
  if (num<10){ Serial.print("0"); }
  else Serial.print("");
  }
