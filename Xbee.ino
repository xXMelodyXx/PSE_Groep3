/*!
  @file main.ino
  @brief Hoofdprogramma van de XBee Zumo robot.

  Dit programma maakt een object van de klasse XBeeControl
  en zorgt ervoor dat de robot bestuurd kan worden via XBee.
*/

#include "XBeeControl.h"

/*!
  @brief Object voor de XBee besturing.
*/
XBeeControl xbee;

/*!
  @brief Setup functie.

  Deze functie wordt één keer uitgevoerd bij het opstarten
  van de Zumo robot.
*/
void setup() {
  xbee.begin();
}

/*!
  @brief Loop functie.

  Deze functie blijft continu herhalen en verwerkt
  de ontvangen XBee commando's.
*/
void loop() {
  xbee.update();
}