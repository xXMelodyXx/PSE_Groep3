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

  

public:
  ProximityBlok(Motoren* m, Lijnsensor* l);

  /**
   *  @brief Initialiseert de proximityblok
   */
  void init();

  /**
   * @brief start de zumo voor het detecteren en duwen van een blok
   */
  void start();

  /**
   * @brief rijd vooruit tot een blok gedetecteerd wordt
   */
  void rijdVooruitTicks(long ticks);

  /**
   * @brief zoekt naar een blok
   */
  void zoekBlok();
  /**
   * @brief draait de zumo terug
   */
  void draaiTerug(long ticks);
  /**
   * @brief duwt tot een zwarte lijn gedetecteerd wordt
   */
  void duwTotZwart();

  /**
   * @brief leest de proximity sensoren
   * @param links De waarde van de linkerste proximity sensor
   * @param rechts De waarde van de rechterste proximity sensor
   */
  void leesProximity(int &links, int &rechts);

  /**
   * @brief berekent het gemiddelde aantal ticks
   * @return Het gemiddelde aantal ticks
   */
  long gemiddeldeTicks();

  //void stop();
};

#endif