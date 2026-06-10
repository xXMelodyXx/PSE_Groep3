#ifndef LIJNSENSOR_H
#define LIJNSENSOR_H

#include <Wire.h>
#include <Zumo32U4.h>
#include "Helling.h"
#include "ProximityBlok.h"
struct sensordata {
  int Value[5];
  int Min[5];
  int Max[5];
  bool detected[5];
};

class Lijnsensor {
private:
  Zumo32U4LineSensors lineSensors;
  Helling helling;
  ProximityBlok proximityBlok;
  Zumo32U4ButtonB buttonB;

  unsigned int sensorValues[5];
  int positie;
  

  sensordata greensensors;
  sensordata graysensors;
  sensordata brownsensors;

  sensordata blacksensors;


  long totaal = 0;

  void calibreer(bool debug, int waarde_min[5], int waarde_max[5]);

public:
  Lijnsensor();
  void init();
  void calibrateWhite(bool debug);
  void calibrateBlack(bool debug);
  void calibrateGreen(bool debug);
  void calibrateBrown(bool debug);
  void calibrateGray(bool debug);
  void simpelCalibreer();
  bool GrayDetected();
  bool GreenDetected();
  bool BrownDetected();
  int GrayPosition(int positie);
  int GreenPosition(int positie);
  int BrownPosition(int positie);
  void read(bool debug);
  void read(bool debug, int sensorNr);
  int bepaalRichting();
  int getPositie();
};

#endif