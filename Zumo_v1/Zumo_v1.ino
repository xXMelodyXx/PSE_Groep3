#include <Wire.h>

#include "Lijnsensor.h"
#include "Helling.h"

#include <Zumo32U4.h>
//#include "XbeeControlv2.h"
#include "Motoren.h"


Zumo32U4ButtonC buttonC;
Zumo32U4ButtonA buttonA;
//Zumo32U4ButtonB buttonB;
//Zumo32U4Motors motors;
Motoren motoren;
Helling helling;

Lijnsensor lijnsensor;
//Xbee xbee;


void setup() {
  //calibreren van de benodigde kleuren
  //Serial1.begin(9600);
  Serial1.begin(9600);
  Serial1.println("test");
  delay(2000);
  lijnsensor.init();
  Serial1.println("Leg de ZUMO op WIT");
  Serial1.println("Druk op knop C om te starten");
  while (buttonC.isPressed() == false) {}
  delay(1000);
  lijnsensor.calibrateWhite(false);
  Serial1.println("--------------------------------");
  Serial1.println("Leg de ZUMO op ZWART");
  Serial1.println("Druk op knop C om te scannen");
  while (buttonC.isPressed() == false) {}
  delay(1000);
  lijnsensor.calibrateBlack(false);

  Serial1.println("zwart gescand");
  Serial1.println("Leg de ZUMO op Groen");
  Serial1.println("Druk op knop C om te scannen");
  while (buttonC.isPressed() == false) {}
  delay(1000);
  lijnsensor.calibrateGreen(false);

  Serial1.println("groen gescand");

  Serial1.println("Leg de ZUMO op Bruin");
  Serial1.println("Druk op knop C om te scannen");
  while (buttonC.isPressed() == false) {}
  delay(1000);
  lijnsensor.calibrateBrown(false);

  Serial1.println("bruin gescand");
  Serial1.println("Leg de ZUMO op Grijs");
  Serial1.println("Druk op knop C om te scannen");
  while (buttonC.isPressed() == false) {}
  delay(1000);
  lijnsensor.calibrateGray(false);

  Serial1.println("grijs gescand");

  Serial1.println("wait for button A");
  buttonA.waitForButton();
  Serial1.println("start!");

  //xbee.begin();
}


void loop() {



  //xbee.update();


  int keuze = lijnsensor.bepaalRichting();



  switch (keuze) {

    case 0:
      //rechtdoor
      motoren.setSpeed(200, 200);
      Serial1.println("case 0 : RECHTDOOR");
      break;

    case 1:
      //SCHERPE LINKS
      motoren.setSpeed(0, 200);
      Serial1.println("case 1 : SCHERP LINKS");
      break;

    case 2:
      //SCHERPE RECHTS
      motoren.setSpeed(200, 0);
      Serial1.println("case 2 : SCHERP RECHTS");
      break;

    case 3:
      //SCHUINE LINKS
      motoren.setSpeed(50, 200);
      Serial1.println("case 3 : SCHUIN LINKS");
      break;


    case 4:
      //SCHUINE RECHTS
      motoren.setSpeed(200, 50);
      Serial1.println("case 4 : SCHUIN RECHTS");
      break;

    case 5:
      //groene lijn
      motoren.setSpeed(100, 100);
      Serial1.println("case  5: GROEN");
      break;

    case 6:
      //bruine lijn
      break;

    case 7:
      motoren.setSpeed(300,300);
      Serial1.println("case 7: HOEK GRADEN ");
      Serial1.print(helling.geefHoek());\
      break;

    case 10:
      //stoppen voor 2 sec
      motoren.stop();
      delay(2000);
      Serial1.println("case 10: STOP 2 SEC");
      break;

    case 11:
      //stoppen als op knop B gedrukt.
      motoren.stop();
      Serial1.println("case 11: STOP");
      break;
  }
}
