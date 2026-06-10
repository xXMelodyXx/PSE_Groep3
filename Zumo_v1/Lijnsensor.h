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
  sensordata groensensors;
  sensordata grijssensors;
  sensordata bruinsensors;
  sensordata zwartsensors;
  sensordata calibreer(String kleur);
  int hoeveelMetingen;
  Xbee* xb;
  Zumo32U4ButtonC buttonC;
public:
  Lijnsensor(Xbee*);
  void init();
  void getCalibratie();
  void calibrateWit();
  void calibrateZwart();
  void calibrateGroen();
  void calibrateBruin();
  void calibrateGrijs();
  int leesPositie();
  sensordata getGemiddelde(int hoeveelMetingen);
  bool GrijsDetected();
  bool GroenDetected();
  bool BruinDetected();
  bool ZwartDetected();
  int GrijsPosition(int positie);
  int GroenPosition(int positie);
  int BruinPosition(int positie);
  int bepaalRichting();
};