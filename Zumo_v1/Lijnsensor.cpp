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

  //TODO: graypositie() maken waarin je  if graydetected aanroept return int

  // if (graysensors.detected[0] && graysensors.detected[4]) {
  //   //if (positie < 300) && positie > 2500) {
  //       //case 10
  //     }
  // }

  // if (graysensors.detected[0]) {
  //   //if (positie < 300) && positie > 2500) {
  //       //case 1
  //     }
  // }

  // if (graysensors.detected[4]) {
  //  // if (positie < 300) && positie > 2500) {
  //       //case 2
  //     }
  // }
}

bool Lijnsensor::GreenDetected() {
  for (int i = 0; i < 5; i++) {
    greensensors.detected[i] = false;
  }
  for (int i = 0; i < 5; i++) {
    if (sensorValues[i] >= greensensors.Min[i] && sensorValues[i] <= greensensors.Max[i]) {
      greensensors.detected[i] = true;
      return true;
    }
  }
}

/*
bool Lijnsensor::GreenDetected() {
  for (int i = 0; i < 5; i++) {
    greensensors.detected[i] = false;
  }
  for (int i = 0; i < 5; i++) {
    if (sensorValues[i] >= greensensors.Min[i] && sensorValues[i] <= greensensors.Max[i]) {
      greensensors.detected[i] = true;
      return true;
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

    if (GreenDetected()) {
      //bochten voor groen
      return 5;
    }
    // if functie greypositie() == 10/1/2 dan case 10/1/2

    if(buttonB.isPressed()){
      return 10;
    }



    return 0;
  }
