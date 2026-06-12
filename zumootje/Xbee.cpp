#include "WString.h"
#include "Xbee.h"
#include <ctype.h>

Xbee::Xbee() {

  command = '\0';
  beschikbaar = false;
}

void Xbee::begin() {

  Serial.begin(9600);
  Serial1.begin(9600);
}

void Xbee::print(String text){
    Serial1.println(text);
}

void Xbee::update() {

  // Controleer of data beschikbaar is
  if (Serial1.available()) {

    // Lees karakter en zet om naar hoofdletter
    command = toupper(Serial1.read());

    beschikbaar = true;

    Serial.print("Command: ");
    Serial.println(command);
  }

  else {
    beschikbaar = false;
  }
}

bool Xbee::toetsIngedrukt(char toets) {

  return beschikbaar &&
         command == toupper(toets);
}

bool Xbee::knopA() {

  return aKnop.getSingleDebouncedPress();
}

bool Xbee::knopB() {

  return bKnop.getSingleDebouncedPress();
}

bool Xbee::knopC() {

  return cKnop.getSingleDebouncedPress();
}

// void Xbee::print(String text){
//     Serial1.println(text);
// }

char Xbee::getCommand() {

  return command;
}