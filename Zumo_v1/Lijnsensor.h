#include <Wire.h>
#include <Zumo32U4.h>
#include "HardwareSerial.h"
#include "WString.h"
#include "Xbee.h"
#include "Motoren.h"
#define NMRSENSOR 5

struct sensordata {
  int Gemiddelde[5];
  int Min[5];
  int Max[5];
  bool detected[5];
};

class Lijnsensor {
private:
  Zumo32U4LineSensors lineSensors;
  Zumo32U4ButtonB buttonB;
  unsigned int sensorValues[5];
  int positie;
  sensordata greensensors;
  sensordata graysensors;
  sensordata brownsensors;
  sensordata blacksensors;
  sensordata calibreer();
  int hoeveelMetingen;
  Xbee* xb;

public:
  Lijnsensor(Xbee*);
  void init();
  void calibrateWhite();
  void calibrateBlack();
  void calibrateGreen();
  void calibrateBrown();
  void calibrateGray();
  sensordata getGemiddelde(int hoeveelMetingen);
  bool GrayDetected();
  bool GreenDetected();
  bool BrownDetected();
  bool BlackDetected();
  int GrayPosition(int positie);
  int GreenPosition(int positie);
  int BrownPosition(int positie);
  void read(bool debug);
  void read(bool debug, int sensorNr);
  int bepaalRichting();
};