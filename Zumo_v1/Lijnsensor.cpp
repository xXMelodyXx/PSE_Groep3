#include "Lijnsensor.h"
#define NMRSENSOR 5

Lijnsensor::Lijnsensor(Xbee* xbee, ProximityBlok* p)
  : xb(xbee), proximityBlok(p) {}


//Motoren motors;

void Lijnsensor::init() {
  helling.start();
  proximityBlok->init();
  lineSensors.initFiveSensors();
  for (int i = 0; i < 5; i++) {
    zwartsensors.Gemiddelde[i] = 0;
    zwartsensors.Min[i] = 0;
    zwartsensors.Max[i] = 0;

    groensensors.Gemiddelde[i] = 0;
    groensensors.Min[i] = 0;
    groensensors.Max[i] = 0;
  }
}

sensordata Lijnsensor::getGemiddelde(int hoeveelMetingen) {
  sensordata resultaat;
  long totaal[NMRSENSOR];

  lineSensors.read(sensorValues);

  for (int i = 0; i < NMRSENSOR; i++) {
    totaal[i] = 0;
    resultaat.Min[i] = sensorValues[i];
    resultaat.Max[i] = sensorValues[i];
  }

  for (int i = 0; i < hoeveelMetingen; i++) {
    lineSensors.read(sensorValues);

    for (int j = 0; j < NMRSENSOR; j++) {
      totaal[j] += sensorValues[j];

      if (sensorValues[j] < resultaat.Min[j]) {
        resultaat.Min[j] = sensorValues[j];
      }

      if (sensorValues[j] > resultaat.Max[j]) {
        resultaat.Max[j] = sensorValues[j];
      }
    }

    delay(5);
  }

  for (int i = 0; i < NMRSENSOR; i++) {
    resultaat.Gemiddelde[i] = totaal[i] / hoeveelMetingen;
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
  for (int i = 0; i < NMRSENSOR; i++) {
    xb->print(String("Gemiddelde: ") + resultaat.Gemiddelde[i]);
    xb->print(String("Minimum: ") + resultaat.Min[i]);
    xb->print(String("Maximum: ") + resultaat.Max[i]);
  }
  xb->print(kleur + " gescand");
  return resultaat;
}

int Lijnsensor::leesPositie() {
  sensordata gemiddeldeMeting = getGemiddelde(3);

  long totaal = 0;
  long gewogenGemiddelde = 0;

  for (int i = 0; i < NMRSENSOR; i++) {
    totaal += gemiddeldeMeting.Gemiddelde[i];
    gewogenGemiddelde += (long)gemiddeldeMeting.Gemiddelde[i] * (i * 1000L);
  }

  if (totaal <= 0) {
    return 2000;
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

bool Lijnsensor::ZwartDetected() {

  lineSensors.readCalibrated(sensorValues);

  for (int i = 0; i < 5; i++) {
    zwartsensors.detected[i] = false;
  }

  bool zwartSeen = false;

  for (int i = 0; i < 5; i++) {
    if (sensorValues[i] >= zwartsensors.Min[i] && sensorValues[i] <= zwartsensors.Max[i]) {

      zwartsensors.detected[i] = true;
      zwartSeen = true;
    }
  }

  return zwartSeen;
}

bool Lijnsensor::GrijsDetected() {

  lineSensors.readCalibrated(sensorValues);

  for (int i = 0; i < 5; i++) {
    grijssensors.detected[i] = false;
  }

  bool grijsSeen = false;

  for (int i = 0; i < 5; i++) {
    if (sensorValues[i] >= grijssensors.Min[i] &&
        sensorValues[i] <= grijssensors.Max[i]) {

      grijssensors.detected[i] = true;
      grijsSeen = true;
    }
  }

  return grijsSeen;
}

int Lijnsensor::GrijsPosition(int positie) {
  if (GrijsDetected()) {
    if (grijssensors.detected[0] && grijssensors.detected[4]) {
      return 10;
    }

    if (grijssensors.detected[0]) {
      return 1;
    }

    if (grijssensors.detected[4]) {
      return 2;
    }
  }
  //erbij gezet Melody
  return 0;
}

bool Lijnsensor::GroenDetected() {

  lineSensors.readCalibrated(sensorValues);

  for (int i = 0; i < 5; i++) {
    groensensors.detected[i] = false;
  }

  bool groenSeen = false;

  for (int i = 0; i < 5; i++) {
    if (sensorValues[i] >= groensensors.Min[i] && sensorValues[i] <= groensensors.Max[i]) {

      groensensors.detected[i] = true;
      groenSeen = true;
    }
  }

  return groenSeen;
}

// als er teveel afwijking is grijssensors.detected[1] & grijssensors.detected[3] toevoegen
int Lijnsensor::GroenPosition(int positie) {
  if (GroenDetected()) {
    if (groensensors.detected[0]) {
      return 1;
    }

    if (groensensors.detected[4]) {
      return 2;
    }

    if ((groensensors.detected[2]) && (!groensensors.detected[0]) && (!groensensors.detected[4])) {
      return 5;
    }
  }
}

bool Lijnsensor::BruinDetected() {

  lineSensors.readCalibrated(sensorValues);

  for (int i = 0; i < 5; i++) {
    bruinsensors.detected[i] = false;
  }

  bool bruinSeen = false;

  for (int i = 0; i < 5; i++) {
    if (sensorValues[i] >= bruinsensors.Min[i] &&
        sensorValues[i] <= bruinsensors.Max[i]) {

      bruinsensors.detected[i] = true;
      bruinSeen = true;
    }
  }

  return bruinSeen;
}

// eventueel uit proberen zonder BruinPosition alleen met Bool naar Bepaalrichting
// Staat nu extra erin voor extra nauwkeurigheid
int Lijnsensor::BruinPosition(int positie) {
  if (BruinDetected()) {
    if (bruinsensors.detected[0] && bruinsensors.detected[4]) {
      return 6;
    }
  }
}




int Lijnsensor::bepaalRichting() {
  // int positie = lineSensors.readLine(sensorValues);
  int positie = leesPositie();

  if (buttonB.isPressed()) {
    return 11;
  }
  if (GroenPosition(positie) == 5) {
    return 5;
  }

  if (BruinPosition(positie) == 6) {
    return 6;
  }

  // if (GrijsPosition(positie) == 10) {
  //   return 10;
  // }

  if (positie < 300) {  //|| (GrijsPosition(positie) == 1)) {
    return 1;
  }

  if (positie > 3700) {  // || (GrijsPosition(positie) == 2)) {
    return 2;
  }

  if (positie < 1500) {
    return 3;
  }

  if (positie > 2500) {
    return 4;
  }





  return 0;
}