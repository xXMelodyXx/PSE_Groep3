#include "HardwareSerial.h"
#include "WString.h"
#include "ProximityBlok.h"
#include "Lijnsensor.h"

ProximityBlok::ProximityBlok(Motoren* m, Lijnsensor* l) : motoren(m), lijnsensor(l) {
  //lijnsensor = NULL;

  bruinAlGedetecteerd = false;

  duwSnelheid = 300;

  // Aantal ticks vooruit nadat bruin is gezien
  vooruitTicksNaBruin = 2029;

  // Veiligheidslimiet voor ongeveer 360 graden
  // Deze waarde kun je handmatig aanpassen
  draai360Ticks = 6100;

  // Minimale proximity waarde om het blok te zien
  objectMinWaarde = 4;
}

/*
void ProximityBlok::setLijnsensor(Lijnsensor* l) {
  lijnsensor = l;
}
*/

//TODO zumoo
void ProximityBlok::init() {
  proxSensors.initFrontSensor();

  motoren->stop();
}

void ProximityBlok::start() {
  sensordata meting = lijnsensor->getGemiddelde(1);
  if (lijnsensor->BruinDetected(meting) && !bruinAlGedetecteerd) {
    motoren->stop();
    delay(300);

    // Eerst vooruit rijden
    rijdVooruitTicks(vooruitTicksNaBruin);

    // Daarna blok zoeken, terugdraaien en duwen
    zoekBlok();

    bruinAlGedetecteerd = true;
  }
}

void ProximityBlok::rijdVooruitTicks(long ticks) {
  motoren->resetEncoders();

  motoren->setSpeed(200, 200);

  while (gemiddeldeTicks() < ticks) {
    delay(5);
  }

  motoren->stop();
}

void ProximityBlok::zoekBlok() {
  motoren->resetEncoders();
  //sensordata meting = lijnsensor->getGemiddelde(1);

  long besteTicks = 0;

  int besteSterkte = 0;
  int links = 0;
  int rechts = 0;

  bool blokGezien = false;
  bool bestePuntGevonden = false;

  // Zumo draait rond om het blok te zoeken
  motoren->setSpeed(200, -200);

  while (gemiddeldeTicks() < draai360Ticks) {
    leesProximity(links, rechts);

    int sterkte = links + rechts;
    long huidigeTicks = gemiddeldeTicks();

    // Blok wordt gezien als minimaal 1 sensor een waarde geeft
    if (links >= objectMinWaarde || rechts >= objectMinWaarde) {
      blokGezien = true;

      // Beste punt is waar beide sensoren samen het sterkst zijn
      if (links >= objectMinWaarde && rechts >= objectMinWaarde) {
        if (sterkte > besteSterkte) {
          besteSterkte = sterkte;
          besteTicks = huidigeTicks;
          bestePuntGevonden = true;
        }
      }
    }

    // Als hij het blok gezien heeft en daarna niet meer ziet,
    // dan is hij voorbij het blok gedraaid
    else {
      if (blokGezien && bestePuntGevonden) {
        break;
      }
    }

    delay(20);
  }

  motoren->stop();
  delay(300);

  if (!bestePuntGevonden) {
    motoren->stop();
  }

  // Terugdraaien naar het punt waar de sensoren het sterkst waren
  long huidigeTicks = gemiddeldeTicks();
  long terugTicks = huidigeTicks - besteTicks;

  draaiTerug(terugTicks);

  // Daarna recht vooruit duwen tot zwart
  
  duwTotZwart();
}

void ProximityBlok::draaiTerug(long ticks) {
  motoren->resetEncoders();

  // Terugdraaien in de andere richting
  motoren->setSpeed(-200, 200);

  while (gemiddeldeTicks() < ticks) {
    delay(5);
  }

  motoren->stop();
  delay(300);
}

/*
void ProximityBlok::duwTotZwart() {
  motoren->setSpeed(duwSnelheid, duwSnelheid);

  while (!lijnsensor->ZwartDetected(meting)) {
    motoren->setSpeed(duwSnelheid, duwSnelheid);
    delay(20);
  }

  stop();
}
*/
void ProximityBlok::duwTotZwart() {
  motoren->setSpeed(duwSnelheid, duwSnelheid);
  bool running = true;

  while (running) {
    sensordata meting = lijnsensor->getGemiddelde(1);

    if (lijnsensor->ZwartDetected(meting)) {
      running = false;
    }

    delay(20);
  }

  motoren->stop();
}
 

void ProximityBlok::leesProximity(int &links, int &rechts) {
  proxSensors.read();

  links = proxSensors.countsFrontWithLeftLeds();
  rechts = proxSensors.countsFrontWithRightLeds();
}

long ProximityBlok::gemiddeldeTicks() {
  long links = abs(motoren->getEncoderLinks());
  long rechts = abs(motoren->getEncoderRechts());

  return (links + rechts) / 2;
}

/*
void ProximityBlok::stop() {
  motoren->stop();

  while (true) {
    delay(100);
  }

}
*/