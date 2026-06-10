#include "Lijnsensor.h"
#define NMRSENSOR 5

Lijnsensor::Lijnsensor(Xbee* xbee)
  : xb(xbee) {}

//Helling helling;

void Lijnsensor::init() {
  helling.start();
  proximityBlok.init();
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
    for (int j = 0; j < NMRSENSOR; j++) {
      totaal[j] += sensorValues[j];
    for (int j = 0; j < NMRSENSOR; j++) {
      totaal[j] += sensorValues[j];
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
}

void Lijnsensor ::simpelCalibreer() {
  lineSensors.calibrate();
}
/*
sensordata Lijnsensor::calibreer(bool debug, int waarde_min[5], int waarde_max[5]) {
  lineSensors.calibrate();
  // bool debug gebruikt om onnodige data outprint te beperken en overzichterlijker te maken
  lineSensors.read(sensorValues);
  int gem_waarde[5];
  for (int i = 0; i < 5; i++) {
    waarde_min[i] = sensorValues[i];
    waarde_max[i] = sensorValues[i];

    totaal = 0;

    for (int j = 0; j < 40; j++) {
      lineSensors.read(sensorValues);

      totaal += sensorValues[i];
      if (debug == true) {
        Serial.println(sensorValues[i]);
      }
      if (sensorValues[i] < waarde_min[i]) {
        waarde_min[i] = sensorValues[j];
      }
      if (sensorValues[i] > waarde_max[i]) {
        waarde_max[i] = sensorValues[j];
      }
      delay(5);
    }

    // OPTIE TODO if statements dichtsbijzijnde kleur plaats van tolerantie
    gem_waarde[i] = totaal / 40;
    waarde_min[i] = waarde_min[i] * 0.5;
    waarde_max[i] = waarde_max[i] * 1.5;
    //tolerantie +/- 120 tijdens testen
    //in plaats van plus x factor doen
    Serial.println("KALIBRATIE KLAAR");
    Serial.print("Gemiddelde: ");
    Serial.println(gem_waarde[i]);
    Serial.print("Minimum: ");
    Serial.println(waarde_min[i]);
    Serial.print("Maximum: ");
    Serial.println(waarde_max[i]);
  }
}
*/


/*
void Lijnsensor::calibrateBlack(bool debug) {
  lineSensors.calibrate();

  lineSensors.readCalibrated(sensorValues);
  long totaal[NMRSENSOR];
  for (int i = 0; i < NMRSENSOR; i++) {
    totaal[i] += sensorValues[i];
    resultaat.Min[i] = sensorValues[i];
    resultaat.Max[i] = sensorValues[i];
  }
  for (int i = 0; i < hoeveelMetingen; i++) {
    lineSensors.readCalibrated(sensorValues);
    for (int j = 0; j < NMRSENSOR; j++) {
      totaal[j] += sensorValues[j];
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
}
*/
sensordata Lijnsensor::calibreer(String kleur) {
  sensordata resultaat = getGemiddelde(100);
  for (int i = 0; i < NMRSENSOR; i++) {
    xb->print("kleur " + kleur + "aan het kalibreren.");
    xb->print("Gemiddelde: " + resultaat.Gemiddelde[i]);
    xb->print("Minimum: " + resultaat.Min[i]);
    xb->print("Maximum: " + resultaat.Max[i]);
  }
  return resultaat;
}


int Lijnsensor::leesPositie() {
  if (BlackDetected() || GreenDetected()) {
    sensordata gemiddeldeMeting = getGemiddelde(3);
    long totaal = 0;
    long gewogenGemiddelde = 0;
    for (int i = 0; i < NMRSENSOR; i++) {
      totaal += gemiddeldeMeting.Gemiddelde[i];                                       // alle gemiddelden van alle sensoren opgeteld
      gewogenGemiddelde += (long)gemiddeldeMeting.Gemiddelde[i] * ((i + 1) * 1000L);  // +1 want *0 = 0.
    }
    if (totaal <= 0) {
      return -1;
    }
    return gewogenGemiddelde / totaal;  //
  }
}
//TODO: toepassing in motoren.cpp

void Lijnsensor::calibrateWhite() {
  calibreer("wit");
}
*/

void Lijnsensor::calibrateBlack() {
  calibreer("zwart");
  //TODO: correctie/drempelwaarde toevoegen met factor
  //TODO: sensordata blacksensors opslaan
}

void Lijnsensor::calibrateGreen() {
  calibreer("groen");
  //TODO: correctie/drempelwaarde toevoegen met factor
  //TODO: sensordata greensensors opslaan
}

void Lijnsensor::calibrateGray() {
  calibreer("grijs");
  //TODO: correctie/drempelwaarde toevoegen met factor
  //TODO: sensordata greysensors opslaan
}

void Lijnsensor::calibrateBrown() {
  calibreer("bruin");
  //TODO: correctie/drempelwaarde toevoegen met factor
  //TODO: sensordata brownsensors opslaan
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
      Serial1.println("GROEN IS GEDETECTEERD");
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

int Lijnsensor::getPositie() {
  return lineSensors.readLine(sensorValues);
}

/**
 * return int voor het switchen van de cases in main
 */
int Lijnsensor::bepaalRichting() {

  positie = lineSensors.readLine(sensorValues);


  if (buttonB.isPressed()) {
    return 11;
  }

  if (helling.hellingGedetecteerd()) {
    return 7;
  }

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

  // if (GreenPosition(positie) == 5) {
  //   return 5;
  // }

  if (BrownPosition(positie) == 6) {
    return 6;
  }


  if (GrayPosition(positie) == 10) {
    return 10;
  }



  return 0;
}
