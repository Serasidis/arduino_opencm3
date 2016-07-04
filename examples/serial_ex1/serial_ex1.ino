uint32_t    n=0;

void setup()
{
    pinMode(PC13, OUTPUT);
    Serial1.begin(115200);
    Serial1.println(F("-PROGRAM START-"));
}

void loop()
{
    Serial1.println(n++);
    togglePin(PC13);
    delay(100);            
}
