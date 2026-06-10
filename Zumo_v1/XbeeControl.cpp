/*!
  @file XBeeControl.cpp
  @brief Implementatiebestand van de klasse XBeeControl.
*/

#include "XBeeControl.h"

XBeeControl::XBeeControl() {
  command = 'X';
  lastCommandTime = 0;
}

void XBeeControl::begin() {
  Serial.begin(9600);
  Serial1.begin(9600);
}

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

  // Laat de robot rijden op basis van commando
  rijden(command);
}

/*!
  @brief Bestuurt de motoren op basis van een toets.
  @param toets Letter van toetsenbord (W, A, S, D, X)
*/
void XBeeControl::rijden(char toets) {

  // Vooruit rijden
  if (toets == 'W') {
    motors.setSpeeds(200, 200);
  }

  // Stoppen
  else if (toets == 'X') {
    motors.setSpeeds(0, 0);
  }

  // Achteruit rijden
  else if (toets == 'S') {
    motors.setSpeeds(-200, -200);
  }

  // Links draaien
  else if (toets == 'A') {
    motors.setSpeeds(0, 400);
  }

  // Rechts draaien
  else if (toets == 'D') {
    motors.setSpeeds(200, 0);
  }
}