#include "HardwareSerial.h"
#include "WString.h"
#include "Lijnsensor.h"
#include "XbeeControl.h"
#include "Motoren.h"

Lijnsensor::Lijnsensor() {}

Motoren motors;

void Lijnsensor::init() {
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
//If grey detected statements hergebruiken, zwart aanpassen.
/*
void Lijnsensor::BlackDetected() {
  lineSensors.readCalibrated(sensorValues);
  blacksensors.detected[0] = false;
  blacksensors.detected[1] = false;
  blacksensors.detected[2] = false;
  blacksensors.detected[3] = false;
  blacksensors.detected[4] = false;
  bool blackDetected = false;
  for (int i = 0; i < 5; i++) {
    if (sensorValues[i] >= blacksensors.Min[i] && sensorValues[i] <= blacksensors.Max[i]) {
      bool blackDetected = false;
      if (sensorValues[i] == sensorValues[0]) {
        blacksensors.detected[0] = true;
        Serial1.println("S0 zwart");
      }
      if (sensorValues[i] == sensorValues[1]) {
        blacksensors.detected[1] = true;
        Serial1.println("S1 zwart");
      }
      if (sensorValues[i] == sensorValues[2]) {
        blacksensors.detected[2] = true;
        Serial1.println("S2 zwart");
      }
      if (sensorValues[i] == sensorValues[3]) {
        blacksensors.detected[3] = true;
        Serial1.println("S3 zwart");
      }
      if (sensorValues[i] == sensorValues[4]) {
        blacksensors.detected[4] = true;
        Serial1.println("S4 zwart");
      } else {
        Serial1.println("else");
      }
    }
  }
  if (!blacksensors.detected[0] && !blacksensors.detected[4] && blacksensors.detected[2]) {
    motors.setSpeed(100, 100);
  }

  if (blacksensors.detected[0] && blacksensors.detected[1] && blacksensors.detected[2]) {
    motors.setSpeed(0, 100);
  }

  if (blacksensors.detected[4] && blacksensors.detected[3] && blacksensors.detected[2]) {
    motors.setSpeed(100, 0);
  } else {
    motors.setSpeed(50, 50);
  }
}

void Lijnsensor::GreyDetected() {
  graysensors.detected[0] = false;
  graysensors.detected[1] = false;
  graysensors.detected[2] = false;
  graysensors.detected[3] = false;
  graysensors.detected[4] = false;
  bool grayDetected = false;
  for (int i = 0; i < 5; i++) {
    if (sensorValues[i] >= graysensors.Min[i] && sensorValues[i] <= graysensors.Max[i]) {
      bool greyDetected = false;
      if (sensorValues[i] = sensorValues[0]) {
        graysensors.detected[0] = true;
      }
      if (sensorValues[i] = sensorValues[1]) {
        graysensors.detected[1] = true;
      }
      if (sensorValues[i] = sensorValues[2]) {
        graysensors.detected[2] = true;
      }
      if (sensorValues[i] = sensorValues[3]) {
        graysensors.detected[3] = true;
      }
      if (sensorValues[i] = sensorValues[4]) {
        graysensors.detected[4] = true;
      }
    }
  }
  if ((graysensors.detected[0] || graysensors.detected[1]) && (graysensors.detected[3] || graysensors.detected[4])) {
    if ((blacksensors.detected[0] || blacksensors.detected[1]) && (blacksensors.detected[3] || blacksensors.detected[4])) {
      motors.setSpeed(0, 0);
      delay(2000);
      motors.setSpeed(200, 200);
    }
  }

  if (graysensors.detected[0] || graysensors.detected[1]) {
    if ((blacksensors.detected[0] || blacksensors.detected[1]) && (blacksensors.detected[3] || blacksensors.detected[4])) {
      motors.setSpeed(0, 100);
    }
  }

  if (graysensors.detected[3] || graysensors.detected[4]) {
    if ((blacksensors.detected[0] || blacksensors.detected[1]) && (blacksensors.detected[3] || blacksensors.detected[4])) {
      motors.setSpeed(100, 0);
    }
  }
}
*/


int Lijnsensor::bepaalRichting2() {

  unsigned int positie = lineSensors.readLine(sensorValues);

  if (positie < 300) {
    return 1;
  }

  if (positie > 3700) {
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


