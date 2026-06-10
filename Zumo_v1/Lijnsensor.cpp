
#include "Lijnsensor.h"

Lijnsensor::Lijnsensor(Xbee* xbee)
  : xb(xbee) {}

Motoren motors;

void Lijnsensor::init() {
  lineSensors.initFiveSensors();
  for (int i = 0; i < 5; i++) {
    blacksensors.Gemiddelde[i] = 0;
    blacksensors.Min[i] = 0;
    blacksensors.Max[i] = 0;

    greensensors.Gemiddelde[i] = 0;
    greensensors.Min[i] = 0;
    greensensors.Max[i] = 0;
  }
}

//TODO: kalibreer functie terug erinstoppen en aanroepen per kleur

sensordata Lijnsensor::getGemiddelde(int hoeveelMetingen) {
  sensordata resultaat;
  lineSensors.readCalibrated(sensorValues);
  long totaal[NMRSENSOR];
  for (int i = 0; i < NMRSENSOR; i++) {
    totaal[i] += sensorValues[i];
    resultaat.Min[i] = sensorValues[i];
    resultaat.Max[i] = sensorValues[i];
  }
  for (int i = 0; i < hoeveelMetingen; i++) {
    lineSensors.readCalibrated(sensorValues);
    for (int j = 0; j < NMRSENSORS; j++) {
      totaal[j] += seensorValues[j];
      if (sensorValues[j] < resultaat.Min[j]) {
        resultaat.Min[i] = sensorValues[j];
      }
      if (sensorValues[j] > resultaat.Max[j]) {
        resultaat.Max[j] = sensorValues[j];
      }
    }
  }
  for (int i = 0; i < NMRSENSOR; i++) {
    resultaat.Gemiddelde[i] = totaal[i] / (hoeveelMetingen + 1);
  }
  return resultaat;

sensordata Lijnsensor::calibreer(string kleur) {
  sensordata resultaat =  getGemiddelde(100);
  xb->print("kleur "+ kleur + "aan het kalibreren.");

  xb->print("Gemiddelde: " + resultaat.Gemiddelde[i]);

  xb->print("Minimum: "resultaat.Min[i]);

  xb->print("Maximum: "resultaat.Max[i]);

}


void Lijnsensor::calibrateWhite() {
  calibreer("wit");
}

void Lijnsensor::calibrateBlack() {
  sensordata blacksensors calibreer("zwart");
  //TODO: correctie toevoegen met factor
}

void Lijnsensor::calibrateGreen() {
  calibreer("groen");
  //TODO: correctie toevoegen met factor
}

void Lijnsensor::calibrateGray() {
  calibreer("grijs");
  //TODO: correctie toevoegen met factor
}

void Lijnsensor::calibrateBrown() {
  calibreer("bruin");
  //TODO: correctie toevoegen met factor
}

bool Lijnsensor::BlackDetected() {
  for (int i = 0; i < 5; i++) {
    blacksensors.detected[i] = false;
  }
  bool blackSeen = false;
  for (int i = 0; i < 5; i++) {
    if (sensorValues[i] >= blacksensors.Min[i] && sensorValues[i] <= blacksensors.Max[i]) {
      blacksensors.detected[i] = true;
      blackSeen = true;
    }
  }
  return blackSeen;
}

bool Lijnsensor::GrayDetected() {
  for (int i = 0; i < 5; i++) {
    graysensors.detected[i] = false;
  }
  bool graySeen = false;
  for (int i = 0; i < 5; i++) {
    if (sensorValues[i] >= graysensors.Min[i] && sensorValues[i] <= graysensors.Max[i]) {
      graysensors.detected[i] = true;
      graySeen = true;
    }
  }
  return graySeen;
}

int Lijnsensor::GrayPosition(int positie) {
  if (GrayDetected()) {
    if (graysensors.detected[0] && graysensors.detected[4]) {
      return 10;
    }

    if (graysensors.detected[0]) {
      return 1;
    }

    if (graysensors.detected[4]) {
      return 2;
    }
  }
}

bool Lijnsensor::GreenDetected() {
  for (int i = 0; i < 5; i++) {
    greensensors.detected[i] = false;
  }
  bool greenSeen = false;
  for (int i = 0; i < 5; i++) {
    if (sensorValues[i] >= greensensors.Min[i] && sensorValues[i] <= greensensors.Max[i]) {
      greensensors.detected[i] = true;
      bool greenSeen = true;
    }
  }
  return greenSeen;
}

// als er teveel afwijking is graysensors.detected[1] & graysensors.detected[3] toevoegen
int Lijnsensor::GreenPosition(int positie) {
  if (GreenDetected()) {
    if (greensensors.detected[0]) {
      return 1;
    }

    if (greensensors.detected[4]) {
      return 2;
    }

    if ((greensensors.detected[2]) && (!greensensors.detected[0]) && (!greensensors.detected[4])) {
      return 5;
    }
  }
}

bool Lijnsensor::BrownDetected() {
  for (int i = 0; i < 5; i++) {
    brownsensors.detected[i] = false;
  }
  bool brownSeen = false;
  for (int i = 0; i < 5; i++) {
    if (sensorValues[i] >= brownsensors.Min[i] && sensorValues[i] <= brownsensors.Max[i]) {
      brownsensors.detected[i] = true;
      bool brownSeen = true;
    }
  }
  return brownSeen;
}

// eventueel uit proberen zonder BrownPosition alleen met Bool naar Bepaalrichting
// Staat nu extra erin voor extra nauwkeurigheid
int Lijnsensor::BrownPosition(int positie) {
  if (BrownDetected()) {
    if (brownsensors.detected[0] && brownsensors.detected[4]) {
      return 6;
    }
  }
}

int Lijnsensor::leesPositie() {
}


int Lijnsensor::bepaalRichting() {
  int positie = lineSensors.readLine(sensorValues);

  if ((positie < 300) || (GreenPosition(positie) == 1) || (GrayPosition(positie) == 1)) {
    return 1;
  }

  if ((positie > 3700) || (GrayPosition(positie) == 2)) {
    return 2;
  }

  if (positie < 1500) {
    return 3;
  }

  if (positie > 2500) {
    return 4;
  }

  if (GreenPosition(positie) == 5) {
    return 5;
  }

  if (BrownPosition(positie) == 6) {
    return 6;
  }

  if (GrayPosition(positie) == 10) {
    return 10;
  }

  if (buttonB.isPressed()) {
    return 11;
  }

  return 0;
}
