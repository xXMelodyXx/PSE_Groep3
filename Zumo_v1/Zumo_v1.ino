#include <Wire.h>

#include "Lijnsensor.h"

#include <Zumo32U4.h>
#include "XbeeControl.h"


Zumo32U4ButtonC buttonC;

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
  //TODO Serial.println(lijnsensor.bepaalRichting());
}