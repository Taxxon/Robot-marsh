#include <Servo.h> //Inkludera servobiblioteket

  Servo servoLeft; //Gör ett nytt objekt av klassen Servo och döp den till servoLeft.
  Servo servoRight; //Gör ett nytt objekt av klassen Servo och döp den till servoRight.

  double light; //Initialisera en variabel av typen double och döp den till light. Den ska ha värdet för ljuset.

void manouver(int leftServo, int rightServo,int tid) { //Detta är metoden som sköter all manövrering.
  
  servoLeft.attach(13); //Starta vänstra servon på pinsen 13.
  servoRight.attach(12); //Starta högra servon på pinsen 12.

  servoLeft.writeMicroseconds(leftServo); //Skriv till vänsta servon med pulsen man har som argument när man kallar metoden.
  servoRight.writeMicroseconds(rightServo); //Skriv till högra servon med pulsen man har som argument när man kallar metoden.
  delay(tid); //Delay för att servona ska pulsera så länge som man har som argument när man kallar metoden.
}

void stopServos() { //Stoppa servon när man kallar metoden. Denna används inte.
  servoLeft.detach();
  servoRight.detach();
}

void setup() {
  Serial.begin(9600); //Starta serialmonitorn så man kan ha utskrifter till den.
  //Deklarera pinmode till alla pins som används.
  pinMode(5, INPUT); 
  pinMode(6, INPUT); 
  pinMode(10, INPUT); 
  pinMode(9, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, INPUT);
}
void findLight() { //Metoden som kallas när ljusnivån är låg.
  manouver(1300, 1700, 2000); //Gå bakåt i 2 sekunder.
  manouver(1300, 1300, 1000); // Sväng ungefär 180 grader.
  
}
int irDetect(int irLedPin, int irReceivePin, long frequency) { //Metoden som hanterar irsensorerna.
  tone(irLedPin, frequency, 8); //Sätt på och stäng av irlampan så ofta man specificierar i argumenten.
  delay(1); //Ge tid för ljuset att reflektera.
  int ir = digitalRead(irReceivePin); //Sätt variabeln ir till 0 om irsensorn känner av ljuset från irlampan. Annars är den 1.
  delay(1);
  return ir; //Returnera variabeln ir.
}
void loop() { //Main loop
  byte morrLeft = digitalRead(5); //Sätt variabeln morrLeft till 1 om vänstra morrhåret inte nuddar något.
  byte morrRight = digitalRead(6);
  light = analogRead(0); //Ge variabeln light samma värde som ljusnivån.
  if(irDetect(9, 10, 44000) == 0 && irDetect(3, 4, 44000) == 0) { //Om båda irsensorerna returnerar 0 backar den och svänger åt sidan.
      manouver(1300, 1700, 1000);
      manouver(1700, 1700, 700);
      Serial.println("Moving backwards");
  } else if(irDetect(9, 10, 44000) == 0) { //Om irsensorn på vänstra sidan returnerar 0 väntar den i 5ms och kollar sedan igen om det är samma
                                           //returnerar den fortfarande 0 så svänger den åt höger.
    delay(5);
    if(irDetect(9, 10, 44000) == 0) {
      Serial.println("Turning Right");
    manouver(1700, 1700, 50);
    }
  } else if(irDetect(3, 4, 44000) == 0) { //Om irsensorn på högra sidan returnerar 0 väntar den i 5ms och kollar sedan igen om det är samma
                                           //returnerar den fortfarande 0 så svänger den åt vänster.
    delay(5);
    if(irDetect(3, 4, 44000) == 0) {
      Serial.println("Turning Left");
      manouver(1300, 1300, 50);
    }
  }
  if(morrLeft == 0 && morrRight == 0) {                 // Båda nuddar.
    manouver(1300, 1700, 1000);
    manouver(1700, 1700, 1700);                             // Vänd 180 grader.
    stopServos();
  } else if(morrLeft == 0) {                            // Vänster nuddar.
    manouver(1300, 1700, 300);                              // Gå bakåt i 500ms
    manouver(1700, 1700, 300);                              // Vänd åt höger
  } else if(morrRight == 0) {                           // Höger nuddar
    manouver(1300, 1700, 300);                              // Gå bakåt i 500ms
    manouver(1300, 1300, 300);                              // Vänd åt vänster.
  }
  Serial.println(light);
  if(light > 4) { //Om ljusnivån är över 4.
      manouver(1700, 1300, 10);
  }
  if(light < 4) { //Om ljusnivån är under 4 kör den metoden findLight.
     findLight();
 }
  
}
