#include <Wire.h>
#include "lijnsensor.h"

Zumo32U4ButtonC buttonC;

Lijnsensor lijnsensor;

void setup() {
  //calibreren van de benodoigden kleuren
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
  /*  Serial.println("Leg de ZUMO op Groen");
  Serial.println("Druk op knop C om te scannen");
  while (buttonC.isPressed() == false) {}
  delay(1000);
  lijnsensor.calibrateGreen(false);

  Serial.println("groen gescand");
  /*
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
  */
}


void loop() {
  lijnsensor.read(false, 2);
  //TODO Serial.println(lijnsensor.bepaalRichting());
}