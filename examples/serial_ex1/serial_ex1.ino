uint32_t    n=0;

void setup()
{
    pinMode(LED1, OUTPUT);
    Serial2.begin(115200);
    Serial2.println(F("-PROGRAM START-"));
}

void loop()
{
    Serial2.println(n++);
    togglePin(LED1);
    delay(100);            
}
