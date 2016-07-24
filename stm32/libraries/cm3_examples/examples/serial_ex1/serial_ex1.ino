uint32_t    n=0;

void setup()
{
    pinMode(LED1, OUTPUT);
    Serial.begin(115200);
    Serial.println(F("-PROGRAM START-"));
}

void loop()
{
    Serial.println(n++);
    togglePin(LED1);
    delay(100);            
}
