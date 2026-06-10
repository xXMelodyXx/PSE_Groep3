#include "HardwareSerial.h"
#include "WString.h"
#include "ProximityBlok.h"

ProximityBlok::ProximityBlok() {
  bruinAlGedetecteerd = false;

  rijSnelheid = 180;
  draaiSnelheid = 200;
  duwSnelheid = 300;

  // Aantal ticks vooruit nadat bruin is gezien
  vooruitTicksNaBruin = 1029;

  // Veiligheidslimiet voor ongeveer 360 graden
  // Deze waarde kun je handmatig aanpassen
  draai360Ticks = 6100;

  // Grenswaardes voor bruin
  // Deze waardes kun je handmatig aanpassen
  bruinMinWaarde = 400;
  bruinMaxWaarde = 900;

  // Grenswaarde voor zwart
  // Deze waarde kun je handmatig aanpassen
  zwartMinWaarde = 900;

  // Minimale proximity waarde om het blok te zien
  objectMinWaarde = 4;
}

void ProximityBlok::init() {
  lineSensors.initFiveSensors();
  proxSensors.initFrontSensor();

  motoren.stop();
}

void ProximityBlok::start() {
  if (BrownDetected() && !bruinAlGedetecteerd) {
    motoren.stop();
    delay(300);

    // Eerst vooruit rijden
    rijdVooruitTicks(vooruitTicksNaBruin);

    // Daarna blok zoeken, terugdraaien en duwen
    zoekBlok();

    bruinAlGedetecteerd = true;
  }
}

void ProximityBlok::rijdVooruitTicks(long ticks) {
  motoren.resetEncoders();

  motoren.setSpeed(rijSnelheid, rijSnelheid);

  while (gemiddeldeTicks() < ticks) {
    delay(5);
  }

  motoren.stop();
}

void ProximityBlok::zoekBlok() {
  motoren.resetEncoders();

  long besteTicks = 0;

  int besteSterkte = 0;
  int links = 0;
  int rechts = 0;

  bool blokGezien = false;
  bool bestePuntGevonden = false;

  // Zumo draait rond om het blok te zoeken
  motoren.setSpeed(draaiSnelheid, -draaiSnelheid);

  while (gemiddeldeTicks() < draai360Ticks) {
    leesProximity(links, rechts);

    int sterkte = links + rechts;
    long huidigeTicks = gemiddeldeTicks();

    Serial1.print("Links: ");
    Serial1.print(links);
    Serial1.print(" Rechts: ");
    Serial1.print(rechts);
    Serial1.print(" Sterkte: ");
    Serial1.print(sterkte);
    Serial1.print(" Ticks: ");
    Serial1.println(huidigeTicks);

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

  motoren.stop();
  delay(300);

  if (!bestePuntGevonden) {
    stopVoorAltijd();
  }

  // Terugdraaien naar het punt waar de sensoren het sterkst waren
  long huidigeTicks = gemiddeldeTicks();
  long terugTicks = huidigeTicks - besteTicks;

  draaiTerug(terugTicks);

  // Daarna recht vooruit duwen tot zwart
  duwTotZwart();
}

void ProximityBlok::draaiTerug(long ticks) {
  motoren.resetEncoders();

  // Terugdraaien in de andere richting
  motoren.setSpeed(-draaiSnelheid, draaiSnelheid);

  while (gemiddeldeTicks() < ticks) {
    delay(5);
  }

  motoren.stop();
  delay(300);
}

void ProximityBlok::duwTotZwart() {
  motoren.setSpeed(duwSnelheid, duwSnelheid);

  while (!BlackDetected()) {
    motoren.setSpeed(duwSnelheid, duwSnelheid);
    delay(20);
  }

  stopVoorAltijd();
}

bool ProximityBlok::BrownDetected() {
  lineSensors.read(sensorValues);

  int gemiddelde = (sensorValues[1] + sensorValues[2] + sensorValues[3]) / 3;

  Serial1.print("Lijn gemiddelde: ");
  Serial1.println(gemiddelde);

  if (gemiddelde >= bruinMinWaarde && gemiddelde <= bruinMaxWaarde) {
    return true;
  }

  return false;
}

bool ProximityBlok::BlackDetected() {
  lineSensors.read(sensorValues);

  int gemiddelde = (sensorValues[1] + sensorValues[2] + sensorValues[3]) / 3;

  Serial1.print("Lijn gemiddelde: ");
  Serial1.println(gemiddelde);

  if (gemiddelde >= zwartMinWaarde) {
    return true;
  }

  return false;
}

void ProximityBlok::leesProximity(int links, int rechts) {
  proxSensors.read();

  links = proxSensors.countsFrontWithLeftLeds();
  rechts = proxSensors.countsFrontWithRightLeds();
}

long ProximityBlok::gemiddeldeTicks() {
  long links = abs(motoren.getEncoderLinks());
  long rechts = abs(motoren.getEncoderRechts());

  return (links + rechts) / 2;
}

void ProximityBlok::stopVoorAltijd() {
  motoren.stop();

  while (true) {
    delay(100);
  }
}