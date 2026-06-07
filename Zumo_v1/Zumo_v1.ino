#include <Wire.h>

#include "Lijnsensor.h"

#include <Zumo32U4.h>
#include "XbeeControl.h"
#include "Motoren.h"


Zumo32U4ButtonC buttonC;
//Zumo32U4Motors motors;
Motoren motors;

Lijnsensor lijnsensor;
XBeeControl xbee;

void setup() {
  //calibreren van de benodigde kleuren
  Serial.begin(9600);
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

  Serial.println("zwart gescand");
  Serial.println("Leg de ZUMO op Grijs");
  Serial.println("Druk op knop C om te scannen");
  while (buttonC.isPressed() == false) {}
  delay(1000);
  lijnsensor.calibrateGray(false);
  xbee.begin();
}


void loop() {
  xbee.update();
  lijnsensor.read(false, 2);
  lijnsensor.read(false, 1);
  lijnsensor.read(false, 3);
  lijnsensor.read(false, 0);
  lijnsensor.read(false, 4);

  char richting = lijnsensor.bepaalRichting();

  switch (richting) {

    case 'D':
      motors.setSpeeds(200, 200);
      break;

    // case 'A':
    //   motors.setSpeeds(50, 200);
    //   break;

    // case 'Z':
    //   motors.setSpeeds(200, 50);
    //   break;

    case 'L':
      motors.setSpeeds(0, 200);
      break;

    case 'R':
      motors.setSpeeds(200, 0);
      break;

    // case "KRUISING":
    //   motors.setSpeeds(0, 0);
    //   break;
  }
    
  
  
}
