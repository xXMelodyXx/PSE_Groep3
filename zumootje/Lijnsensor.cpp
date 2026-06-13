#include "Lijnsensor.h"
#define NMRSENSOR 5

Lijnsensor::Lijnsensor(Xbee* xbee, ProximityBlok* p)
  : xb(xbee), proximityBlok(p) {}


//Motoren motors;

void Lijnsensor::init() {
  helling.start();
  proximityBlok->init();
  lineSensors.initFiveSensors();
}

sensordata Lijnsensor::getGemiddelde(int hoeveelMetingen) {
  sensordata resultaat;

  lineSensors.readCalibrated(sensorValues);

  long totaal[NMRSENSOR];


  for (int i = 0; i < NMRSENSOR; i++) {
    totaal[i] = sensorValues[i];
    resultaat.Min[i] = sensorValues[i];
    resultaat.Max[i] = sensorValues[i];
  }

  for (int i = 0; i < hoeveelMetingen; i++) {
    lineSensors.readCalibrated(sensorValues);

    for (int j = 0; j < NMRSENSOR; j++) {
      totaal[j] += sensorValues[j];

      if (sensorValues[j] < resultaat.Min[j]) {
        resultaat.Min[j] = sensorValues[j];
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

void Lijnsensor::simpelCalibreer() {
  lineSensors.calibrate();
}

sensordata Lijnsensor::calibreer(String kleur) {
  xb->print("Leg de ZUMO op " + kleur);
  xb->print("Druk op knop C om te scannen");
  buttonC.waitForButton();

  sensordata resultaat = getGemiddelde(100);

  String minString = "Minimum: ";
  String maxString = "Maximum: ";
  String gemString = "Gemiddelde: ";
  for (int i = 0; i < NMRSENSOR; i++) {
    minString += resultaat.Min[i];
    minString += " ";
    maxString += resultaat.Max[i];
    maxString += " ";
    gemString += resultaat.Gemiddelde[i];
    gemString += " ";
  }
  xb->print(minString);
  xb->print(maxString);
  xb->print(gemString);
  xb->print(kleur + " gescand");
  return resultaat;
}

int Lijnsensor::leesPositie() {
  sensordata gemiddeldeMeting = getGemiddelde(3);

  long totaal = 0;
  long gewogenGemiddelde = 0;

  for (int i = 0; i < NMRSENSOR; i++) {
    totaal += gemiddeldeMeting.Gemiddelde[i];                                       // alle gemiddelden van alle sensoren opgeteld
    gewogenGemiddelde += (long)gemiddeldeMeting.Gemiddelde[i] * ((i + 1) * 1000L);  // +1 want *0 = 0.
  }

  if (totaal <= 0) {
    return 3000;  //ALS GEEN LIJN RECHTDOOR
  }

  return gewogenGemiddelde / totaal;
}

void Lijnsensor::getCalibratie() {
  calibrateWit();
  calibrateZwart();
  calibrateGroen();
  calibrateGrijs();
  calibrateBruin();
}

void Lijnsensor::calibrateWit() {
  calibreer("wit");
}

void Lijnsensor::calibrateZwart() {
  sensordata tempZwart = calibreer("zwart");
  for (int i = 0; i < NMRSENSOR; i++) {
    zwartsensors.Gemiddelde[i] = tempZwart.Gemiddelde[i];
    zwartsensors.Min[i] = tempZwart.Min[i] * 0.4;  //toepassing correctie
    zwartsensors.Max[i] = tempZwart.Max[i] * 1.5;
  }
}

void Lijnsensor::calibrateGroen() {
  sensordata tempGroen = calibreer("groen");
  for (int i = 0; i < NMRSENSOR; i++) {
    groensensors.Gemiddelde[i] = tempGroen.Gemiddelde[i];
    groensensors.Min[i] = tempGroen.Min[i] * 0.5;  //toepassing correctie
    groensensors.Max[i] = tempGroen.Max[i] * 1.5;
  }
}

void Lijnsensor::calibrateGrijs() {
  sensordata tempGrijs = calibreer("grijs");
  for (int i = 0; i < NMRSENSOR; i++) {
    grijssensors.Gemiddelde[i] = tempGrijs.Gemiddelde[i];
    grijssensors.Min[i] = tempGrijs.Min[i] * 0.5;  //toepassing correctie
    grijssensors.Max[i] = tempGrijs.Max[i] * 1.5;
  }
}

void Lijnsensor::calibrateBruin() {
  sensordata tempBruin = calibreer("bruin");
  for (int i = 0; i < NMRSENSOR; i++) {
    bruinsensors.Gemiddelde[i] = tempBruin.Gemiddelde[i];
    bruinsensors.Min[i] = tempBruin.Min[i] * 0.5;  //toepassing correctie
    bruinsensors.Max[i] = tempBruin.Max[i] * 1.5;
  }
}

bool Lijnsensor::ZwartDetected(sensordata meting) {

  for (int i = 0; i < 5; i++) {
    zwartsensors.detected[i] = false;
  }

  bool zwartSeen = false;

  for (int i = 0; i < 5; i++) {
    if (meting.Gemiddelde[i] >= zwartsensors.Min[i] && meting.Gemiddelde[i] <= zwartsensors.Max[i]) {

      zwartsensors.detected[i] = true;
      zwartSeen = true;
    }
  }

  return zwartSeen;
}

bool Lijnsensor::GrijsDetected(sensordata meting) {

  for (int i = 0; i < 5; i++) {
    grijssensors.detected[i] = false;
  }

  bool grijsSeen = false;

  for (int i = 0; i < 5; i++) {
    if (meting.Gemiddelde[i] >= grijssensors.Min[i] && meting.Gemiddelde[i] <= grijssensors.Max[i]) {

      grijssensors.detected[i] = true;
      grijsSeen = true;
    }
  }

  return grijsSeen;
}

int Lijnsensor::GrijsPosition(sensordata meting) {
  if (GrijsDetected(meting)) {
    if (grijssensors.detected[0] && grijssensors.detected[4]) {
      return 6;
    }

    if (grijssensors.detected[0]) {
      if (zwartsensors.detected[0]) {
        grijsLinks = true;
        grijsRechts = false;
        grijsActief = true;
        return 2;
      }
    }
    if (grijssensors.detected[4]) {
      if (zwartsensors.detected[4]) {
        grijsRechts = true;
        grijsLinks = false;
        grijsActief = true;
        return 3;
      }
    }
  }
  return -1;
}

bool Lijnsensor::GroenDetected(sensordata meting) {

  for (int i = 0; i < 5; i++) {
    groensensors.detected[i] = false;
  }

  bool groenSeen = false;
  for (int i = 0; i < 5; i++) {
    if (meting.Gemiddelde[i] >= groensensors.Min[i] && meting.Gemiddelde[i] <= groensensors.Max[i]) {

      groensensors.detected[i] = true;
      groenSeen = true;
    }
  }

  return groenSeen;
}

bool Lijnsensor::BruinDetected(sensordata meting) {

  for (int i = 0; i < 5; i++) {
    bruinsensors.detected[i] = false;
  }
  bool bruinSeen = false;

  for (int i = 0; i < 5; i++) {
    if (meting.Gemiddelde[i] >= bruinsensors.Min[i] && meting.Gemiddelde[i] <= bruinsensors.Max[i]) {

      bruinsensors.detected[i] = true;
      bruinSeen = true;
    }
  }

  return bruinSeen;
}
/*
void Lijnsensor::setGrijsLinks() {
  grijsLinksGezien = true;
  grijsRechtsGezien = false;
}

void Lijnsensor::setGrijsRechts() {
  grijsRechtsGezien = true;
  grijsLinksGezien = false;
}

bool Lijnsensor::isGrijsLinks() {
  return grijsLinksGezien;
}

bool Lijnsensor::isGrijsRechts() {
  return grijsRechtsGezien;
}

void Lijnsensor::resetGrijs() {
  grijsLinksGezien = false;
  grijsRechtsGezien = false;
}
*/


bool Lijnsensor::zwartKruispunt() {
  sensordata meting = getGemiddelde(1);
  ZwartDetected(meting);

  bool linksZwart = zwartsensors.detected[0] || zwartsensors.detected[1];
  bool rechtsZwart = zwartsensors.detected[3] || zwartsensors.detected[4];

  return linksZwart && rechtsZwart;
}

bool Lijnsensor::handleGrijsTape(Motoren motoren) {

  if (!grijsActief){
    return false;
  }

  if(!zwartKruispunt()){
    return false;
  }

  if (grijsLinks) {
    motoren.setSpeed(-180, 220);
  }

  if (grijsRechts) {
    motoren.setSpeed(220, -180);
  }

  delay(250);

  grijsLinks = false;
  grijsRechts = false;
  grijsActief = false;

  return true;
}


int Lijnsensor::bepaalCase() {
  sensordata meting = getGemiddelde(1);

  if (buttonB.isPressed()) {
    return 10;
  }

  if (GrijsPosition(meting) == 2) {

    return 2;
  }
  if (GrijsPosition(meting) == 3) {
    return 3;
  }
  if (GrijsPosition(meting) == 6) {
    return 6;
  }
  if (helling.hellingGedetecteerd()) {
    return 5;
  }

  if (ZwartDetected(meting)) {
    return 0;
  }
  if (GroenDetected(meting)) {
    return 1;
  }

  if (BruinDetected(meting)) {
    return 4;
  }



  return -1;
}