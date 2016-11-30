void setup() {
Serial.begin(9600);

}
double volts(int adPin) {           // Vad den får för inputt
  return double(analogRead(adPin)); // Returnar inputt
}
void loop() {
 Serial.print("A3 = ");             // Printar ut A3 = 
 Serial.println(volts(0));          //Printar ut hur ljust det är
 delay(1000);                       // Delay innan den printar ut
}

//Test för ljus detektorn. Om det är ljust så blir värdet högre.
