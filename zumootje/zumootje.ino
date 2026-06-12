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


int BASE_SPEED = 200;  // basissnelheid
int MAX_SPEED = 400;   // maximale motorsnelheid
int MIN_SPEED = -400;  // minimale motorsnelheid

const float KP = 0.6;  // Proportioneel  – reageert op huidige fout
const float KI = 0;    // Integraal      – compenseert aanhoudende fout
const float KD = 0;    // Differentieel  – dempt overshoot/slingeren
// ─────────────────────────────────────────────────

// PID variabelen
float prevError = 0;
float integral = 0;

void rijdenMetPID(bool groendetected) {
  int positie = lijnsensor.leesPositie();


  float error = positie - 3000;
  integral += error;
  integral = constrain(integral, -5000, 5000);

  //Afgeleide
  float derivative = error - prevError;
  prevError = error;

  float correctie = (KP * error) + (KI * integral) + (KD * derivative);

  if (!groendetected) {
    int linksSnelheid = constrain((int)(BASE_SPEED + correctie), MIN_SPEED, MAX_SPEED);
    int rechtsSnelheid = constrain((int)(BASE_SPEED - correctie), MIN_SPEED, MAX_SPEED);
    motoren.setSpeed(linksSnelheid, rechtsSnelheid);
  }

  else if (groendetected) {
    int linksSnelheid = constrain((int)(BASE_SPEED / 2 + correctie), MIN_SPEED / 2, MAX_SPEED / 2);
    int rechtsSnelheid = constrain((int)(BASE_SPEED / 2 - correctie), MIN_SPEED / 2, MAX_SPEED / 2);
    motoren.setSpeed(linksSnelheid, rechtsSnelheid);
  }
}

void setup() {

  Serial1.begin(9600);
  xb.print("test");
  delay(2000);
  buttonC.waitForButton();
  lijnsensor.init();
  motoren.initialiseer(&lijnsensor);
  lijnsensor.getCalibratie();
  xb.print("wait for button A");
  buttonA.waitForButton();
  xb.print("start!");

  xb.begin();
}

void loop() {

  int keuze = lijnsensor.bepaalRichting();


  switch (keuze) {
    bool groendetected = false;

    case 0:
      //Zwarte lijn volgen
      rijdenMetPID(groendetected);
      xb.print("case 0 : Zwart gedetecteer");
      break;


    case 1:
      //Groene lijn volgen
      groendetected = true;
      rijdenMetPID(groendetected);
      xb.print("case 1: Groen gedetecteerd");
      break;

    case 2:
      //Grijs Links
      motoren.setSpeed(50, 200);
      xb.print("case 2: Grijs Links");
      break;

    case 3:
      //Grijs Rechts
      motoren.setSpeed(200, 50);
      xb.print("case 2: Grijs rechts");
      break;

    case 4:
      //Bruin gedetecteerd, start zoeken en duwen van blokje.
      proxBlok.start();
      break;

    case 5:
      //Helling gedetecteerd, sneller rijden.
      rijdenMetPID();
      xb.print("case 4 : SCHUIN RECHTS");
      break;

    case 6:
      //Grijs stoppen voor 2 seconden.
      motoren.stop();
      delay(2000);
      xb.print("case 6: Stoppen en balanceren ");
      break;

    case 11:
      //stoppen als op knop B gedrukt.
      motoren.stop();
      xb.print("case 11: STOP");

      motoren.stop();
      xb.print("case 11: STOP");
      while (buttonA.isPressed() == false) {
        motoren.stop();
        delay(50);
      }
      Serial1.println("Hervat!");

      break;

    default:
      break;
  }
}