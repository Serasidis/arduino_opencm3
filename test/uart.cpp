#include<Arduino.h>

uint32_t    n=0;

void setup()
{

    pinMode(LED1, OUTPUT);
    Serial.begin(115200);
    Serial.println(F("-PROGRAM START-"));
    Serial.print(" SYSTEM CLOCK:");
    Serial.println( sysclk() );
    Serial.print(" APB1 CLOCK:");
    Serial.println( pb1clk() );
    Serial.print(" APB2 CLOCK:");
    Serial.println( pb2clk() );
}

void loop()
{
    Serial.print(n++);
    Serial.print(" RSV:");
    Serial.println( Serial.available());
    togglePin(LED1);
    delay(100);
}
