/**
 * Test example for toggling the SPI speed.
 * 
 * It toggles the SPI speed from 4.5 MHz to 9 MHz and vice versa.
 * 
 * Created on 07 Jul 2016 - Modified by Vassilis Serasidis <avrsite@yahoo.gr>
 * Home: http://www.serasidis.gr
 * 
 */


#include <SPI.h>

long i;


void setup() {
  SPI.begin(); //
  SPI2.begin();

}

void loop() {
  i = millis(); //Get the number of milliseconds since the Arduino board began running the current program. 
  //Set the SPI bus to 4.5 MHz, Most Significant Byte and SPI mode 0.
  SPI.beginTransaction(SPISettings(4500000, MSBFIRST, SPI_MODE0));
  
  //Set the SPI2 bus to 4.5 MHz, Most Significant Byte and SPI mode 0.
  SPI2.beginTransaction(SPISettings(4500000, MSBFIRST, SPI_MODE0));
  while((millis() <  i + 1000)){ // Do that loop for 1 second (1000 ms).
    SPI.transfer(0x55);          // Write on SPI the hex data 0x55
    SPI2.transfer(0xAC);         // Write on SPI2 the hex data 0xAC
  }

  i = millis();
  SPI.beginTransaction(SPISettings(9000000, MSBFIRST, SPI_MODE0));
  SPI2.beginTransaction(SPISettings(9000000, MSBFIRST, SPI_MODE0));
  while((millis() <  i + 1000)){
    SPI.transfer(0x55);
    SPI2.transfer(0xAC);
  }
}