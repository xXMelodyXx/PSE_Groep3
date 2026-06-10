#include <Wire.h>
#include "Lijnsensor.h"
#include <Zumo32U4.h>
#include "Xbee.h"
#include "Motoren.h"



Zumo32U4ButtonC buttonC;
Zumo32U4ButtonA buttonA;
//Zumo32U4ButtonB buttonB;
//Zumo32U4Motors motors;
Motoren motoren;

Xbee xb;
Lijnsensor lijnsensor(&xb);


void setup() {
  //calibreren van de benodigde kleuren
  //Serial1.begin(9600);
  Serial1.begin(9600);
  xb.print("test");
  delay(2000);
  lijnsensor.init();
  xb.print("Leg de ZUMO op WIT");
  xb.print("Druk op knop C om te starten");
  while (buttonC.isPressed() == false) {}
  delay(1000);
  lijnsensor.calibrateWhite();
  xb.print("--------------------------------");
  xb.print("Leg de ZUMO op ZWART");
  xb.print("Druk op knop C om te scannen");
  while (buttonC.isPressed() == false) {}
  delay(1000);
  lijnsensor.calibrateBlack();

  xb.print("zwart gescand");
  xb.print("Leg de ZUMO op Groen");
  xb.print("Druk op knop C om te scannen");
  while (buttonC.isPressed() == false) {}
  delay(1000);
  lijnsensor.calibrateGreen();

  xb.print("groen gescand");

  xb.print("Leg de ZUMO op Bruin");
  xb.print("Druk op knop C om te scannen");
  while (buttonC.isPressed() == false) {}
  delay(1000);
  lijnsensor.calibrateBrown();

  xb.print("bruin gescand");
  xb.print("Leg de ZUMO op Grijs");
  xb.print("Druk op knop C om te scannen");
  while (buttonC.isPressed() == false) {}
  delay(1000);
  lijnsensor.calibrateGray();

  xb.print("grijs gescand");

  xb.print("wait for button A");
  buttonA.waitForButton();
  xb.print("start!");

  //xbee.begin();
}


void loop() {



  //xbee.update();


  int keuze = lijnsensor.bepaalRichting();



  switch (keuze) {

    case 0:
      //rechtdoor
      motoren.setSpeed(200, 200);
      xb.print("case 0 : RECHTDOOR");
      break;

    case 1:
      //SCHERPE LINKS
      motoren.setSpeed(0, 200);
      xb.print("case 1 : SCHERP LINKS");
      break;

    case 2:
      //SCHERPE RECHTS
      motoren.setSpeed(200, 0);
      xb.print("case 2 : SCHERP RECHTS");
      break;

    case 3:
      //SCHUINE LINKS
      motoren.setSpeed(50, 200);
      xb.print("case 3 : SCHUIN LINKS");
      break;


    case 4:
      //SCHUINE RECHTS
      motoren.setSpeed(200, 50);
      xb.print("case 4 : SCHUIN RECHTS");
      break;

    case 5:
      //groene lijn
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
      motoren.stop();
      xb.print("case 11: STOP");
      break;
  }
}
