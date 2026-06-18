#ifndef PROXIMITYBLOK_H
#define PROXIMITYBLOK_H

#include <Zumo32U4.h>
#include "Motoren.h"

//class Lijnsensor;

class ProximityBlok {

private:
  Zumo32U4ProximitySensors proxSensors;

  Motoren* motoren;
  Lijnsensor* lijnsensor;

  bool bruinAlGedetecteerd;

  int duwSnelheid;
  long vooruitTicksNaBruin;
  long draai360Ticks;
  int objectMinWaarde;

  void rijdVooruitTicks(long ticks);
  void zoekBlok();
  void draaiTerug(long ticks);
  void duwTotZwart();

  //bool BruinDetected();
  //bool ZwartDetected();

  void leesProximity(int &links, int &rechts);
  long gemiddeldeTicks();

  void stop();

public:
  ProximityBlok(Motoren* m, Lijnsensor* l);

  //void setLijnsensor(Lijnsensor* l);

  void init();
  void start();
};

#endif