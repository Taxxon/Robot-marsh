void setup() {
Serial.begin(9600);
pinMode(5, INPUT);
pinMode(6, INPUT);
 


}

void loop() {
 byte wLeft = digitalRead(5);
 byte wRight = digitalRead(6);
 Serial.print(wLeft);
 Serial.print(wRight);
}
