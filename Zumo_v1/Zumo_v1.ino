#include <Wire.h>

#include "Lijnsensor.h"

#include <Zumo32U4.h>
#include "XbeeControl.h"
#include "Motoren.h"


Zumo32U4ButtonC buttonC;
Zumo32U4ButtonA buttonA;
//Zumo32U4Motors motors;
Motoren motoren;

Lijnsensor lijnsensor;
//Xbee xbee;


void setup() {
  //calibreren van de benodigde kleuren
  Serial.begin(9600);
  Serial1.begin(9600);

  delay(2000);
  lijnsensor.init();
  Serial.println("Leg de ZUMO op WIT");
  Serial.println("Druk op knop C om te starten");
  while (buttonC.isPressed() == false) {}
  delay(1000);
  lijnsensor.calibrateWhite(false);
  Serial.println("--------------------------------");
  Serial.println("Leg de ZUMO op ZWART");
  Serial.println("Druk op knop C om te scannen");
  while (buttonC.isPressed() == false) {}
  delay(1000);
  lijnsensor.calibrateBlack(false);

  Serial.println("zwart gescand");
  Serial.println("Leg de ZUMO op Groen");
  Serial.println("Druk op knop C om te scannen");
  while (buttonC.isPressed() == false) {}
  delay(1000);
  lijnsensor.calibrateGreen(false);

  Serial.println("groen gescand");

  Serial.println("Leg de ZUMO op Bruin");
  Serial.println("Druk op knop C om te scannen");
  while (buttonC.isPressed() == false) {}
  delay(1000);
  lijnsensor.calibrateBrown(false);

  Serial.println("bruin gescand");
  Serial.println("Leg de ZUMO op Grijs");
  Serial.println("Druk op knop C om te scannen");
  while (buttonC.isPressed() == false) {}
  delay(1000);
  lijnsensor.calibrateGray(false);

  Serial.println("grijs gescand");

  buttonA.waitForButton();
  Serial.println("wait for button A");
  
  //xbee.begin();
}


void loop() {
  lijnsensor.BlackDetected();
 // xbee.update();
  

  //int keuze = lijnsensor.bepaalRichting();

  // switch(keuze){

  //   case 0 : 
  //     motoren.setSpeed(200,200);
  //     break;

  //   case 1: 
  //     //SCHERPE LINKS
  //     motoren.setSpeed(0, 200);
  //     break;



  //   case 2:
  //   //SCHERPE RECHTS
  //     motoren.setSpeed(200, 0);
  //     break;



  //   case 3:
  //   //SCHUINE LINKS
  //     motoren.setSpeed(50, 150); //Snelheid meot nog getest worden
  //     break;


  //   case 4:
  //   //SCHUINE RECHTS
  //   motoren.setSpeed(150, 50);
  //   break;
  // }


  
}
