#include "HardwareSerial.h"
#include "WString.h"
#include "Lijnsensor.h"
#include "XbeeControl.h"
#include "Motoren.h"
//#include "Helling.h"

Lijnsensor::Lijnsensor() {}

//Helling helling;

void Lijnsensor::init() {
  helling.start();
  proximityBlok.init();
  lineSensors.initFiveSensors();

  for (int i = 0; i < 5; i++) {
    blacksensors.Value[i] = 0;
    blacksensors.Min[i] = 0;
    blacksensors.Max[i] = 0;

    greensensors.Value[i] = 0;
    greensensors.Min[i] = 0;
    greensensors.Max[i] = 0;
  }
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
void Lijnsensor::calibrateGreen(bool debug) {
  calibreer(debug, greenMin, greenMax);
}
*/

void Lijnsensor::calibrateWhite(bool debug) {
  lineSensors.calibrate();
}

void Lijnsensor::calibrateBlack(bool debug) {
  lineSensors.calibrate();

  lineSensors.readCalibrated(sensorValues);
  for (int i = 0; i < 5; i++) {
    blacksensors.Min[i] = sensorValues[i];
    blacksensors.Max[i] = sensorValues[i];

    totaal = 0;

    for (int j = 0; j < 40; j++) {
      lineSensors.readCalibrated(sensorValues);

      totaal += sensorValues[i];
      if (debug == true) {
        Serial1.println(sensorValues[i]);
      }
      if (sensorValues[i] < blacksensors.Min[i]) {
        blacksensors.Min[i] = sensorValues[i];
      }
      if (sensorValues[i] > blacksensors.Max[i]) {
        blacksensors.Max[i] = sensorValues[i];
      }
      delay(5);
    }

    Serial1.println("ZWART KALIBRATIE KLAAR");
    Serial1.print("zwartwaarde: ");
    Serial1.println(blacksensors.Value[i]);
    Serial1.print("Zwart min: ");
    Serial1.println(blacksensors.Min[i]);
    Serial1.print("Zwart max: ");
    Serial1.println(blacksensors.Max[i]);
  }
}

/*
void Lijnsensor::calibrateGreen(bool debug) {
  lineSensors.calibrate();

  lineSensors.readCalibrated(sensorValues);
  for (int i = 0; i < 5; i++) {
    greensensors.Min[i] = sensorValues[i];
    greensensors.Max[i] = sensorValues[i];

    totaal = 0;
    for (int j = 0; j < 40; j++) {
      lineSensors.readCalibrated(sensorValues);
      totaal += sensorValues[i];
      if (debug == true) {
        Serial1.println(sensorValues[i]);
      }
      if (sensorValues[i] < greensensors.Min[i]) {
        greensensors.Min[i] = sensorValues[i];
      }
      if (sensorValues[i] > greensensors.Max[i]) {
        greensensors.Max[i] = sensorValues[i];
      }
      delay(5);
    }

    Serial1.println("GREEN KALIBRATIE KLAAR");
    Serial1.print("greenwaarde: ");
    Serial1.println(greensensors.Value[i]);
    Serial1.print("Green min: ");
    Serial1.println(greensensors.Min[i]);
    Serial1.print("Green max: ");
    Serial1.println(greensensors.Max[i]);
  }
}
*/

void Lijnsensor::calibrateGray(bool debug) {
  lineSensors.calibrate();

  lineSensors.readCalibrated(sensorValues);
  for (int i = 0; i < 5; i++) {
    graysensors.Min[i] = sensorValues[i];
    graysensors.Max[i] = sensorValues[i];

    totaal = 0;
    for (int j = 0; j < 40; j++) {
      lineSensors.readCalibrated(sensorValues);
      totaal += sensorValues[i];
      if (debug == true) {
        Serial1.println(sensorValues[i]);
      }
      if (sensorValues[i] < graysensors.Min[i]) {
        graysensors.Min[i] = sensorValues[i];
      }
      if (sensorValues[i] > graysensors.Max[i]) {
        graysensors.Max[i] = sensorValues[i];
      }
      delay(5);
    }

    Serial1.println("GRAY KALIBRATIE KLAAR");
    Serial1.print("graywaarde: ");
    Serial1.println(graysensors.Value[i]);
    Serial1.print("Gray min: ");
    Serial1.println(graysensors.Min[i]);
    Serial1.print("Gray max: ");
    Serial1.println(graysensors.Max[i]);
  }
}

void Lijnsensor::calibrateBrown(bool debug) {
  lineSensors.calibrate();

  lineSensors.readCalibrated(sensorValues);
  for (int i = 0; i < 5; i++) {
    brownsensors.Min[i] = sensorValues[i];
    brownsensors.Max[i] = sensorValues[i];

    totaal = 0;
    for (int j = 0; j < 40; j++) {
      lineSensors.readCalibrated(sensorValues);
      totaal += sensorValues[i];
      if (debug == true) {
        Serial1.println(sensorValues[i]);
      }
      if (sensorValues[i] < brownsensors.Min[i]) {
        brownsensors.Min[i] = sensorValues[i];
      }
      if (sensorValues[i] > brownsensors.Max[i]) {
        brownsensors.Max[i] = sensorValues[i];
      }
      delay(5);
    }
    //correctie comment optie
    /*
    brownsensors.Value[i] = totaal / 40;
    brownsensors.Min[i] = brownsensors.Min[i] - 30;
    brownsensors.Max[i] = brownsensors.Max[i] + 30;
     */
    //readcalibrated toegevoegd die kijkt naar 0 tot 30

    Serial1.println("BROWN KALIBRATIE KLAAR");
    Serial1.print("Brown waarde: ");
    Serial1.println(brownsensors.Value[i]);
    Serial1.print("Brown min: ");
    Serial1.println(brownsensors.Min[i]);
    Serial1.print("Brown max: ");
    Serial1.println(brownsensors.Max[i]);
  }
}

bool Lijnsensor::GrayDetected() {
  for (int i = 0; i < 5; i++) {
    graysensors.detected[i] = false;
  }
  for (int i = 0; i < 5; i++) {
    if (sensorValues[i] >= graysensors.Min[i] && sensorValues[i] <= graysensors.Max[i]) {
      graysensors.detected[i] = true;
      return true;
    }
  }
}

int Lijnsensor::GrayPosition(int positie) {
  if (GrayDetected()) {
    if (graysensors.detected[0] && graysensors.detected[4]) {
      // evt. delay als hij te snel positie herkent
      if (positie < 300 || positie > 2500) {
        return 10;
      }
    }

    if (graysensors.detected[0]) {
      if (positie < 300 || positie > 2500) {  //heb && replaced met ||
        return 1;
      }
    }

    if (graysensors.detected[4]) {
      if (positie < 300 || positie > 2500) {
        return 2;
      }
    }
  }
}

bool Lijnsensor::GreenDetected() {
  for (int i = 0; i < 5; i++) {
    greensensors.detected[i] = false;
  }
  for (int i = 0; i < 5; i++) {
    if (sensorValues[i] >= greensensors.Min[i] && sensorValues[i] <= greensensors.Max[i]) {
      Serial1.println("GROEN IS GEDETECTEERD");
      greensensors.detected[i] = true;
      return true;
    }
  }
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
  for (int i = 0; i < 5; i++) {
    if (sensorValues[i] >= brownsensors.Min[i] && sensorValues[i] <= brownsensors.Max[i]) {
      brownsensors.detected[i] = true;
      return true;
    }
  }
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

  if()

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
