#include <Wire.h>
#include "Lijnsensor.h"
#include <Zumo32U4.h>
#include "Xbee.h"
#include "Motoren.h"
#include "ProximityBlok.h"



Zumo32U4ButtonC buttonC;
Zumo32U4ButtonA buttonA;

Xbee xb;
Motoren motoren;
ProximityBlok proxBlok(&motoren);

Lijnsensor lijnsensor(&xb, &proxBlok);

//── PID instellingen ──────────────────────────────
const int BASE_SPEED = 200;   // basissnelheid
const int MAX_SPEED  = 400;   // maximale motorsnelheid
const int MIN_SPEED  = 0;     // minimale motorsnelheid

// Pas deze drie waarden aan tijdens testen:
const float KP = 0.11;   // Proportioneel  – reageert op huidige fout
const float KI = 0.0;    // Integraal      – compenseert aanhoudende fout
const float KD = 1.5;    // Differentieel  – dempt overshoot/slingeren
// ─────────────────────────────────────────────────

// PID variabelen
float prevError   = 0;
float integral    = 0;

void rijdenMetPID() {
  int positie = lijnsensor.leesPositie();  

  float error = positie - 2000;
  integral += error;
  integral = constrain(integral, -5000, 5000);

  Afgeleide
  float derivative = error - prevError;
  prevError = error;
  
  float correctie = (KP * error) + (KI * integral) + (KD * derivative);

  // Motorsnelheden berekenen
  int linksSnelheid  = constrain((int)(BASE_SPEED + correctie), MIN_SPEED, MAX_SPEED);
  int rechtsSnelheid = constrain((int)(BASE_SPEED - correctie), MIN_SPEED, MAX_SPEED);

  motoren.setSpeed(linksSnelheid, rechtsSnelheid);
}

void setup() {
  //calibreren van de benodigde kleuren
  //Serial1.begin(9600);
  Serial1.begin(9600);
  xb.print("test");
  delay(2000);
  while (buttonC.isPressed() == false) {}
  motoren.initialiseer(&lijnsensor);

  lijnsensor.init();
  lijnsensor.getCalibratie();

  /*
  xb.print("Leg de ZUMO op WIT");
  xb.print("Druk op knop C om te starten");
  while (buttonC.isPressed() == false) {}
  delay(1000);
  lijnsensor.calibrateWit();
  xb.print("--------------------------------");
  xb.print("Leg de ZUMO op ZWART");
  xb.print("Druk op knop C om te scannen");
  while (buttonC.isPressed() == false) {}
  delay(1000);
  lijnsensor.calibrateZwart();

  xb.print("zwart gescand");
  xb.print("Leg de ZUMO op Groen");
  xb.print("Druk op knop C om te scannen");
  while (buttonC.isPressed() == false) {}
  delay(1000);
  lijnsensor.calibrateGrijs();

  xb.print("groen gescand");

  xb.print("Leg de ZUMO op Bruin");
  xb.print("Druk op knop C om te scannen");
  while (buttonC.isPressed() == false) {}
  delay(1000);
  lijnsensor.calibrateBruin();

  xb.print("bruin gescand");
  xb.print("Leg de ZUMO op Grijs");
  xb.print("Druk op knop C om te scannen");
  while (buttonC.isPressed() == false) {}
  delay(1000);
  lijnsensor.calibrateGrijs();

  xb.print("grijs gescand");


  xb.print("wait for button A");
  buttonA.waitForButton();
  xb.print("start!");
  */

  //xbee.begin();
}


void loop() {



  //xbee.update();


  int keuze = lijnsensor.bepaalRichting();



  switch (keuze) {

    case 0:
      //rechtdoor
     // motoren.setSpeed(200, 200);
     integral = 0;
      rijdenMetPID();
      xb.print("case 0 : RECHTDOOR");
      break;

    case 1:
      //SCHERPE LINKS
      //motoren.setSpeed(0, 200);
      integral = 0;
      rijdenMetPID();
      xb.print("case 1 : SCHERP LINKS");
      break;

    case 2:
      //SCHERPE RECHTS
      //motoren.setSpeed(200, 0);
      integral = 0;
      rijdenMetPID();
      xb.print("case 2 : SCHERP RECHTS");
      break;

    case 3:
      //SCHUINE LINKS
      //motoren.setSpeed(50, 200);
      integral = 0;
      rijdenMetPID();
      xb.print("case 3 : SCHUIN LINKS");
      break;


    case 4:
      //SCHUINE RECHTS
      //motoren.setSpeed(200, 50);
      integral = 0;
      rijdenMetPID();
      xb.print("case 4 : SCHUIN RECHTS");
      break;

    case 5:
      //groene lijn
      integral = 0;
      motoren.setSpeed(100, 100);
      xb.print("case  5: GROEN");
      break;

    case 6:
      //bruine lijn
      break;


    case 10:
      //stoppen voor 2 sec
      motoren.stop();
      delay(2000);
      xb.print("case 10: STOP 2 SEC");
      break;

    case 11:
      //stoppen als op knop B gedrukt.
      // motoren.stop();
      // xb.print("case 11: STOP");

      motoren.stop();
      xb.print("case 11: STOP");
      while (buttonA.isPressed() == false) {
        motoren.stop();
        delay(50);
      }
      Serial1.println("Hervat!");
      
      break;
  }  
}