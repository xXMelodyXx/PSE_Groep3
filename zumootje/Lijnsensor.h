#include <Wire.h>
#include <Zumo32U4.h>
#include "HardwareSerial.h"
#include "WString.h"
#include "Xbee.h"
#include "Motoren.h"
#include "Helling.h"
#include "ProximityBlok.h"
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
  Helling helling;
  ProximityBlok* proximityBlok;
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
  Lijnsensor(Xbee* xbee, ProximityBlok* p);
  void init();
  void getCalibratie();
  void calibrateWit();
  void calibrateZwart();
  void calibrateGroen();
  void calibrateBruin();
  void calibrateGrijs();
  int leesPositie();
  void simpelCalibreer();
  sensordata getGemiddelde(int hoeveelMetingen);
  bool GrijsDetected(sensordata);
  bool GroenDetected(sensordata);
  bool BruinDetected(sensordata);
  bool ZwartDetected(sensordata);
  int GrijsPosition(sensordata);
  int BruinPosition(sensordata);
  int bepaalRichting();
};