void setup() {
  // initialize digital pin 13 as an output.
  pinMode(PC13, OUTPUT);
}

void loop() {
  digitalWrite(PC13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                // wait for a second
  digitalWrite(PC13, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);             
}
