#include <Arduino.h>

// written by simonf @ stm32duino.com
#ifdef STM32F1
#define SerialOUT Serial2
#elif defined STM32F4
#define SerialOUT Serial1
#endif // STM32F1

byte nodeID = 10;
byte packetNum = 11;
float C = 42.611;
float F = 42.611;
float H = 42.6;
float vBatt = 3.14;
int packetLoss = 10;
int packetTotal = 10000;


void printData() {
  SerialOUT.print(nodeID);
  SerialOUT.print(",");
  SerialOUT.print(packetNum);
  SerialOUT.print(",");
  SerialOUT.print(C);
  SerialOUT.print(",");
  SerialOUT.print(F);
  SerialOUT.print(",");
  SerialOUT.print(H);
  SerialOUT.print(",");
  SerialOUT.print(vBatt,3);
  SerialOUT.print(",");
  SerialOUT.print(packetLoss);
  SerialOUT.print(",");
  SerialOUT.println(packetTotal);
}

void setup() {
  Serial.begin(115200);

  //SerialOUT.begin(300);


}

void loop() {

 unsigned int Baudrates[]= {300,1200,2400,4800,9600,19200,38400,57600,115200};

  unsigned long start;

for ( int ind =0 ; ind < 9; ind++ ){

  Serial.print("AT Baudrate it Takes: -");
  Serial.print(Baudrates[ind]);
  Serial.print(" , ");
  SerialOUT.begin(Baudrates[ind]);
  start = micros();
  printData();
  unsigned long end = micros();
  Serial.print(end - start);
  Serial.print("uS. To send 1 char it should take uS :");
  Serial.println((10000000/Baudrates[ind]));


  delay(3000);
  SerialOUT.end();

  }

}
