#include <Wire.h>
#include "Lijnsensor.h"
#include "Helling.h"
#include <Zumo32U4.h>
#include "Motoren.h"

Zumo32U4ButtonC buttonC;
Zumo32U4ButtonA buttonA;

Lijnsensor lijnsensor;
Motoren motoren(&lijnsensor);


//── PID instellingen ──────────────────────────────
const int BASE_SPEED = 200;   // basissnelheid
const int MAX_SPEED  = 400;   // maximale motorsnelheid
const int MIN_SPEED  = 0;     // minimale motorsnelheid

// Pas deze drie waarden aan tijdens testen:
const float KP = 0.25;   // Proportioneel  – reageert op huidige fout
const float KI = 0.0;    // Integraal      – compenseert aanhoudende fout
//const float KD = 1.5;    // Differentieel  – dempt overshoot/slingeren
// ─────────────────────────────────────────────────

// PID variabelen
float prevError   = 0;
float integral    = 0;

void setup() {
  Serial1.begin(9600);
  delay(2000);
  lijnsensor.init();

  Serial1.println("STARTEN MET SIMPEL CALIBRATIE");
  Serial1.println("Duk op knop C");
  while(buttonC.isPressed() == false){}
  motoren.initialiseer();

  Serial1.println("Leg de ZUMO op WIT");
  Serial1.println("Druk op knop C om te starten");
  while (buttonC.isPressed() == false) {}
  delay(1000);
  lijnsensor.calibrateWhite(false);

  Serial1.println("Leg de ZUMO op ZWART");
  Serial1.println("Druk op knop C om te scannen");
  while (buttonC.isPressed() == false) {}
  delay(1000);
  lijnsensor.calibrateBlack(false);

  Serial1.println("Leg de ZUMO op Groen");
  Serial1.println("Druk op knop C om te scannen");
  while (buttonC.isPressed() == false) {}
  delay(1000);
  lijnsensor.calibrateGreen(false);

  Serial1.println("Leg de ZUMO op Bruin");
  Serial1.println("Druk op knop C om te scannen");
  while (buttonC.isPressed() == false) {}
  delay(1000);
  lijnsensor.calibrateBrown(false);

  Serial1.println("Leg de ZUMO op Grijs");
  Serial1.println("Druk op knop C om te scannen");
  while (buttonC.isPressed() == false) {}
  delay(1000);
  lijnsensor.calibrateGray(false);

  Serial1.println("Druk op knop A om te starten!");
  buttonA.waitForButton();
  Serial1.println("Start!");
}


void rijdenMetPID() {
  int positie = lijnsensor.getPositie();  

  float error = positie - 2000;
  integral += error;
  integral = constrain(integral, -5000, 5000);

  // Afgeleide
  // float derivative = error - prevError;
  // prevError = error;

  // PID correctie
  float correctie = (KP * error) + (KI * integral);

  // Motorsnelheden berekenen
  int linksSnelheid  = constrain((int)(BASE_SPEED + correctie), MIN_SPEED, MAX_SPEED);
  int rechtsSnelheid = constrain((int)(BASE_SPEED - correctie), MIN_SPEED, MAX_SPEED);

  motoren.setSpeed(linksSnelheid, rechtsSnelheid);
}


void loop() {
  int keuze = lijnsensor.bepaalRichting();

  // static int vorigeKeuze = -1;
  // if (keuze != vorigeKeuze) {
  //   vorigeKeuze = keuze;
  // }

  switch (keuze) {

    case 0:
      // Rechtdoor met PID
      rijdenMetPID();
      Serial1.println("CASE 0: RECHTDOOR ");
      

      break;

    case 1:
      // Scherp links
      integral = 0;  // reset integraal bij bocht
      motoren.setSpeed(0, 200);
      Serial1.println("CASE 1: SCHERP LINKS");
      break;

    case 2:
      
      integral = 0;
      motoren.setSpeed(200, 0);
       Serial1.println("CASE 2: SCHERP RECHTS");
      break;

    case 3:
    
      rijdenMetPID();
       Serial1.println("CASE 3: SCHUIN LINKS");
      break;

    case 4:
     
      rijdenMetPID();
       Serial1.println("CASE 4: SCHUIN RECHTS");
      break;

    case 5:
      // Groene lijn
      integral = 0;
      motoren.setSpeed(100, 100);
      Serial1.println("CASE 5: GROEN");
      break;

    // case 6:
    //   // Bruine lijn
    //   integral = 0;
    //   motoren.stop();
    //   break;

    case 7:
      // Helling – rechtdoor zonder PID (lijn is minder betrouwbaar)
      integral = 0;
      motoren.setSpeed(250, 250);
       Serial1.println("CASE 7: HELLING GEDETECTEERD ");
      break;

    case 10:
      // Stop 2 seconden
      integral = 0;
      //motoren.stop();
      delay(2000);
      break;

    case 11:
      // Stop totdat knop A ingedrukt wordt
      integral = 0;
      motoren.stop();
      while (buttonA.isPressed() == false) {
        motoren.stop();
        delay(50);
      }
      Serial1.println("Hervat!");
      break;
  }
}
