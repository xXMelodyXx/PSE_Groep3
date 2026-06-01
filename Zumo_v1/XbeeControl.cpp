/*!
  @file XBeeControl.cpp
  @brief Implementatiebestand van de klasse XBeeControl.
*/

#include "XBeeControl.h"

/*!
  @brief Constructor van XBeeControl.

  Initialiseert de standaardwaarden van de variabelen.
*/

XBeeControl::XBeeControl() {
  command = 'X';
  lastCommandTime = 0;
}

/*!
  @brief Start de seriële communicatie.

  Serial wordt gebruikt voor debug-output.
  Serial1 wordt gebruikt voor de XBee communicatie.
*/
void XBeeControl::begin() {
  Serial.begin(9600);
  Serial1.begin(9600);
}

/*!
  @brief Verwerkt ontvangen commando's van de XBee.

  Deze functie leest de ontvangen tekens via XBee
  en bestuurt de motoren van de robot.
*/
void XBeeControl::update() {

  // Controleer of er data beschikbaar is
  if (Serial1.available()) {

    // Lees karakter en zet om naar hoofdletter
    command = toupper(Serial1.read());

    // Sla tijdstip van laatste commando op
    lastCommandTime = millis();

    Serial.print("Command: ");
    Serial.println(command);
  }

  // Stop de robot als langer dan 500 ms geen commando ontvangen is
  if (millis() - lastCommandTime > 500) {
    command = 'X';
  }

  // Vooruit rijden
  if (command == 'W') {
    motors.setSpeeds(200, 200);
  }

  // Stoppen
  else if (command == 'X') {
    motors.setSpeeds(0, 0);
  }

  // Achteruit rijden
  else if (command == 'S') {
    motors.setSpeeds(-200, -200);
  }

  // Links draaien
  else if (command == 'A') {
    motors.setSpeeds(0, 200);
  }

  // Rechts draaien
  else if (command == 'D') {
    motors.setSpeeds(200, 0);
  }
}