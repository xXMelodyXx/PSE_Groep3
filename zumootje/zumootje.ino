#include <Wire.h>
#include "Lijnsensor.h"
#include <Zumo32U4.h>
#include "Xbee.h"
#include "Motoren.h"
#include "ProximityBlok.h"

enum GrijsKeuze {
  GEEN_GRIJS,
  GRIJS_LINKS,
  GRIJS_RECHTS
};

GrijsKeuze grijsKeuze = GEEN_GRIJS;


Zumo32U4ButtonC buttonC;
Zumo32U4ButtonA buttonA;

Xbee xb;
Motoren motoren;
ProximityBlok proxBlok(&motoren);

Lijnsensor lijnsensor(&xb, &proxBlok);


int BASE_SPEED = 200;  // basissnelheid
int MAX_SPEED = 400;   // maximale motorsnelheid
int MIN_SPEED = -400;  // minimale motorsnelheid

const float KP = 0.6; 
const float KI = 0;    
const float KD = 0;    

// PID variabelen
float prevError = 0;
float integral = 0;

void rijdenMetPID(bool groendetected, bool hellingdetected) {
  int positie = lijnsensor.leesPositie();


  float error = positie - 3000;

  integral += error;
  integral = constrain(integral, -5000, 5000);

  float derivative = error - prevError;
  prevError = error;

  float correctie = (KP * error) + (KI * integral) + (KD * derivative);

  if (!groendetected) {
    int linksSnelheid = constrain((int)(BASE_SPEED + correctie), MIN_SPEED, MAX_SPEED);
    int rechtsSnelheid = constrain((int)(BASE_SPEED - correctie), MIN_SPEED, MAX_SPEED);
    motoren.setSpeed(linksSnelheid, rechtsSnelheid);
  }
  if (groendetected) {
    int linksSnelheid = constrain((int)(BASE_SPEED / 2 + correctie), MIN_SPEED / 2, MAX_SPEED / 2);
    int rechtsSnelheid = constrain((int)(BASE_SPEED / 2 - correctie), MIN_SPEED / 2, MAX_SPEED / 2);
    motoren.setSpeed(linksSnelheid, rechtsSnelheid);
  }
  if(hellingdetected){
    int linksSnelheid = constrain((int)(BASE_SPEED * 2 + correctie), MIN_SPEED, MAX_SPEED);
    int rechtsSnelheid = constrain((int)(BASE_SPEED * 2 - correctie), MIN_SPEED, MAX_SPEED);
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

  if (grijsKeuze != GEEN_GRIJS && lijnsensor.zwartKruispunt()) {

    if (grijsKeuze == GRIJS_LINKS) {
      xb.print("Grijs links onthouden -> links op kruising");
      motoren.setSpeed(-150, 200);
      delay(400);
    }

    if (grijsKeuze == GRIJS_RECHTS) {
      xb.print("Grijs rechts onthouden -> rechts op kruising");
      motoren.setSpeed(200, -150);
      delay(400);
    }

    grijsKeuze = GEEN_GRIJS;
    return;
  }

  switch (keuze) {
   

    case 0:
      //Zwarte lijn volgen
      rijdenMetPID(false, false);
      xb.print("case 0 : Zwart gedetecteerd");
      break;


    case 1:
      //Groene lijn volgen
      //groendetected = true;
      rijdenMetPID(true, false);
      xb.print("case 1: Groen gedetecteerd");
      break;

    case 2:
      //Grijs Links
      grijsKeuze = GRIJS_LINKS;
      rijdenMetPID(false, false);
      //motoren.setSpeed(50, 200);
      xb.print("case 2: Grijs Links");
      break;

    case 3:
      //Grijs Rechts
      grijsKeuze = GRIJS_RECHTS;
      //motoren.setSpeed(200, 50);
      xb.print("case 2: Grijs rechts");
      break;

    case 4:
      //Bruin gedetecteerd, start zoeken en duwen van blokje.
      proxBlok.start();
      break;

    case 5:
      //Helling gedetecteerd, sneller rijden.
      rijdenMetPID(false, true);
      xb.print("case 4 : Helling gedetecteerd");
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