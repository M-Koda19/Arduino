#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

int i=0; //initiarize
int w=119;
int r=114;
int DeviceAddress = 0x2A; // 0b0101010 42

int Address[100]={
  0x00, // Control
  0x00, // Control
  //0x01, // 
  //0x02, // 
  0x03, // Red MSB
  0x04, // Red LSB
  0x05, // Green MSB
  0x06, // Green LSB
  0x07, // Blue MSB
  0x08,  // Blue LSB
  0x09,
  0x0A
  };

int Value[100]={
  0x8F, // ADC reset, awake
  0x0B, // Control initialize 0B:correct
  //0x0C, 
  //0x30, 
  0x00, // Red MSB initialize
  0x00, // Red LSB initialize
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00
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
    Serial.println(x,HEX);
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
  for (i=0; i<10; i++) {
    Wire.beginTransmission(DeviceAddress);
    Wire.write(Address[i]);
    Wire.write(Value[i]);    
    Wire.endTransmission(false);
    Insert0x0(Address[i]);
    Serial.print(Address[i],HEX);
    Serial.print("=");
    Insert0x0(Value[i]);
    Serial.println(Value[i],HEX);
    delay(0);
  } // while(1){}//finalize
  }

void ReadReg(){
  for (i=0; i<10; i++) { 
  Wire.beginTransmission(DeviceAddress);
  Wire.write(Address[i]);
  Wire.endTransmission(false);
  Wire.requestFrom(DeviceAddress, 1,true);
  Value[i] = Wire.read();
  Insert0x0(Address[i]);
  Serial.print(Address[i],HEX);
  Serial.print("=");
  Insert0x0(Value[i]);
  Serial.println(Value[i],HEX);
  delay(0);
  } // while(1){}//finalize
  }

void Insert0x0(int num){
  Serial.print("0x");
  if (num<16){ Serial.print("0"); }
  else Serial.print("");
  }
