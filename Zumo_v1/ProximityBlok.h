#ifndef PROXIMITYBLOK_H
#define PROXIMITYBLOK_H

#include <Zumo32U4.h>
#include "Motoren.h"

class ProximityBlok {

private:
  Zumo32U4LineSensors lineSensors;
  Zumo32U4ProximitySensors proxSensors;

  Motoren motoren;

  unsigned int sensorValues[5];

  bool bruinAlGedetecteerd;

  int rijSnelheid;
  int draaiSnelheid;
  int duwSnelheid;

  long vooruitTicksNaBruin;
  long draai360Ticks;

  int bruinMinWaarde;
  int bruinMaxWaarde;
  int zwartMinWaarde;

  int objectMinWaarde;

  void rijdVooruitTicks(long ticks);
  void zoekBlok();
  void draaiTerug(long ticks);
  void duwTotZwart();

  bool BrownDetected();
  bool BlackDetected();

  void leesProximity(int links, int rechts);
  long gemiddeldeTicks();

  void stopVoorAltijd();

public:
  ProximityBlok();

  void init();
  void start();
};

#endif