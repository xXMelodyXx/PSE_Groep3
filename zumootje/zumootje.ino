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


double BASE_SPEED = 200.0;  // basissnelheid
double MAX_SPEED = 400.0;   // maximale motorsnelheid
double MIN_SPEED = -400.0;  // minimale motorsnelheid
//0.6
const float KP = 0.63; 
const float KI = 0;    
const float KD = 0;    

// PID variabelen
float prevError = 0;
float integral = 0;

void rijdenMetPID(bool groendetected, bool hellingdetected) {
  int positie = lijnsensor.leesPositie();


  float error = positie - 3000;

  //niet gebruikt
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
    int linksSnelheid = constrain((int)(BASE_SPEED / 1.3 + correctie), MIN_SPEED / 1.3, MAX_SPEED );
    int rechtsSnelheid = constrain((int)(BASE_SPEED / 1.3 - correctie), MIN_SPEED / 1.3, MAX_SPEED);
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

   if (lijnsensor.handleGrijsTape(motoren)) {
    return;
  }

  int keuze = lijnsensor.bepaalRichting();
 
 
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
      
      rijdenMetPID(false, false);
     
      xb.print("case 2: Grijs Links");
      break;

    case 3:
      //Grijs Rechts
      
      rijdenMetPID(false, false);
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