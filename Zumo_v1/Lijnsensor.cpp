#include "WString.h"
#include "Lijnsensor.h"
#include "XbeeControl.h"

Lijnsensor::Lijnsensor() {}
Zumo32U4Motors motors;

void Lijnsensor::init() {
  lineSensors.initFiveSensors();
  for (int i = 0; i < 5; i++) {
    blackValue[i] = 0;
    blackMin[i] = 0;
    blackMax[i] = 0;

    greenValue[i] = 0;
    greenMin[i] = 0;
    greenMax[i] = 0;
  }
}
/*
void Lijnsensor::calibreer(bool debug, int waarde_min[5], int waarde_max[5]) {
  lineSensors.calibrate();
  // bool debug gebruikt om onnodige data outprint te beperken en overzichterlijker te maken
  lineSensors.read(sensorValues);
  int gem_waarde[5];
  for (int i = 0; i < 5; i++) {
    waarde_min[i] = sensorValues[i];
    waarde_max[i] = sensorValues[i];

    totaal = 0;

    for (int j = 0; j < 40; j++) {
      lineSensors.read(sensorValues);

      totaal += sensorValues[i];
      if (debug == true) {
        Serial1.println(sensorValues[i]);
      }
      if (sensorValues[i] < waarde_min[i]) {
        waarde_min[i] = sensorValues[i];
      }
      if (sensorValues[i] > waarde_max[i]) {
        waarde_max[i] = sensorValues[i];
      }
      delay(5);
    }

    // OPTIE TODO if statements dichtsbijzijnde kleur plaats van tolerantie
    gem_waarde[i] = totaal / 40;
    waarde_min[i] = waarde_min[i] - 30;
    waarde_max[i] = waarde_max[i] + 30;
    //tolerantie +/- 120 tijdens testen
    Serial1.println("KALIBRATIE KLAAR");
    Serial1.print("Gemiddelde: ");
    Serial1.println(gem_waarde[i]);
    Serial1.print("Minimum: ");
    Serial1.println(waarde_min[i]);
    Serial1.print("Maximum: ");
    Serial1.println(waarde_max[i]);
  }
}

*/
void Lijnsensor::calibrateWhite(bool debug) {
  lineSensors.calibrate();
}

void Lijnsensor::calibrateBlack(bool debug) {
  lineSensors.calibrate();

  lineSensors.read(sensorValues);
  for (int i = 0; i < 5; i++) {
    blackMin[i] = sensorValues[i];
    blackMax[i] = sensorValues[i];

    totaal = 0;

    for (int j = 0; j < 40; j++) {
      lineSensors.read(sensorValues);

      totaal += sensorValues[i];
      if (debug == true) {
        Serial1.println(sensorValues[i]);
      }
      if (sensorValues[i] < blackMin[i]) {
        blackMin[i] = sensorValues[i];
      }
      if (sensorValues[i] > blackMax[i]) {
        blackMax[i] = sensorValues[i];
      }
      delay(5);
    }



    // OPTIE TODO if statements dichtsbijzijnde kleur plaats van tolerantie
    blackValue[i] = totaal / 40;
    blackMin[i] = blackMin[i] - 30;
    blackMax[i] = blackMax[i] + 30;

    Serial1.println("ZWART KALIBRATIE KLAAR");
    Serial1.print("zwartwaarde: ");
    Serial1.println(blackValue[i]);
    Serial1.print("Zwart min: ");
    Serial1.println(blackMin[i]);
    Serial1.print("Zwart max: ");
    Serial1.println(blackMax[i]);
  }
}


void Lijnsensor::calibrateGreen(bool debug) {
  lineSensors.calibrate();

  lineSensors.read(sensorValues);
  for (int i = 0; i < 5; i++) {
    greenMin[i] = sensorValues[i];
    greenMax[i] = sensorValues[i];

    totaal = 0;
    for (int j = 0; j < 40; j++) {
      lineSensors.read(sensorValues);
      totaal += sensorValues[i];
      if (debug == true) {
        Serial1.println(sensorValues[i]);
      }
      if (sensorValues[i] < greenMin[i]) {
        greenMin[i] = sensorValues[j];
      }
      if (sensorValues[i] > greenMax[i]) {
        greenMax[i] = sensorValues[j];
      }
      delay(5);
    }

    greenValue[i] = totaal / 40;
    greenMin[i] = greenMin[i] - 30;
    greenMax[i] = greenMax[i] + 30;

    Serial1.println("GREEN KALIBRATIE KLAAR");
    Serial1.print("greenwaarde: ");
    Serial1.println(greenValue[i]);
    Serial1.print("Green min: ");
    Serial1.println(greenMin[i]);
    Serial1.print("Green max: ");
    Serial1.println(greenMax[i]);

    //TODO voor grijs & bruin
  }
}


void Lijnsensor::calibrateGray(bool debug) {
  lineSensors.calibrate();

  lineSensors.read(sensorValues);
  for (int i = 0; i < 5; i++) {
    grayMin[i] = sensorValues[i];
    grayMax[i] = sensorValues[i];

    totaal = 0;
    for (int j = 0; j < 40; j++) {
      lineSensors.read(sensorValues);
      totaal += sensorValues[i];
      if (debug == true) {
        Serial1.println(sensorValues[i]);
      }
      if (sensorValues[i] < grayMin[i]) {
        grayMin[i] = sensorValues[j];
      }
      if (sensorValues[i] > grayMax[i]) {
        grayMax[i] = sensorValues[j];
      }
      delay(5);
    }

    grayValue[i] = totaal / 40;
    grayMin[i] = grayMin[i] - 30;
    grayMax[i] = grayMax[i] + 30;

    Serial1.println("GRAY KALIBRATIE KLAAR");
    Serial1.print("graywaarde: ");
    Serial1.println(grayValue[i]);
    Serial1.print("Gray min: ");
    Serial1.println(grayMin[i]);
    Serial1.print("Gray max: ");
    Serial1.println(grayMax[i]);

  }
}

void Lijnsensor::calibrateBrown(bool debug) {
  lineSensors.calibrate();

  lineSensors.read(sensorValues);
  for (int i = 0; i < 5; i++) {
    brownMin[i] = sensorValues[i];
    brownMax[i] = sensorValues[i];

    totaal = 0;
    for (int j = 0; j < 40; j++) {
      lineSensors.read(sensorValues);
      totaal += sensorValues[i];
      if (debug == true) {
        Serial1.println(sensorValues[i]);
      }
      if (sensorValues[i] < brownMin[i]) {
        brownMin[i] = sensorValues[j];
      }
      if (sensorValues[i] > brownMax[i]) {
        brownMax[i] = sensorValues[j];
      }
      delay(5);
    }

    brownValue[i] = totaal / 40;
    brownMin[i] = brownMin[i] - 30;
    brownMax[i] = brownMax[i] + 30;

    Serial1.println("BROWN KALIBRATIE KLAAR");
    Serial1.print("Brown waarde: ");
    Serial1.println(brownValue[i]);
    Serial1.print("Brown min: ");
    Serial1.println(brownMin[i]);
    Serial1.print("Brown max: ");
    Serial1.println(brownMax[i]);

  }
}

void Lijnsensor::calibrateGray(bool debug) {
  calibreer(debug, grayMin, grayMax);
}

/*
void Lijnsensor::read(bool debug) {
  lineSensors.read(sensorValues);

  bool zwartGedetecteerd = false;
  bool groenGedetecteerd = false;
  bool grijsGedetecteerd = false;
  if (debug == true) {
    for (int i = 0; i < 5; i++) {
      int waarde = sensorValues[i];

      Serial1.print("Sensor ");
      Serial1.print(i);
      Serial1.print(": ");
      Serial1.println(waarde);
    }
  }
  if (sensorValues[2] >= blackMin[2] && sensorValues[2] <= blackMax[2]) {
    zwartGedetecteerd = true;
  }

  if (sensorValues[2] >= greenMin[2] && sensorValues[2] <= greenMax[2]) {
    groenGedetecteerd = true;
  }
  if (sensorValues[2] >= grijsGedetecteerd[2] && sensorValues[2] <= grijsGedetecteerd[2]) {
    grijsGedetecteerd = true;
  }
//geen grijs en bruin nog toegevoegd
  if (zwartGedetecteerd) {
    Serial1.println(">>> ZWARTE LIJN GEDETECTEERD");
  } 
  else if (groenGedetecteerd) {
    Serial1.println(">>> GROENE LIJN GEDETECTEERD");
  }

  else if(grijsGedetecteerd){
      Serial1.println("GRIJZE LIJN GEDETECTEERD");
    }
   else {
    Serial1.println(">>> GEEN LIJN");
  }

  Serial1.println("--------------------");
  delay(100);
  // TODO voor sensor 1, 3, 0, 4
  // TODO (if) left, center, right
  // TODO grijs eerst volgende kruising een bocht die kant op
  // TODO bruin stoppen
}
*/

void Lijnsensor::read(bool debug, int sensorNr) {
  lineSensors.read(sensorValues);

  bool zwartGedetecteerd = false;
  bool groenGedetecteerd = false;
  bool grijsGedetecteerd = false;
  bool brownGedetecteerd = false;

  if (debug == true) {

    int waarde = sensorValues[sensorNr];

    Serial1.print("Sensor ");
    Serial1.print(sensorNr);
    Serial1.print(": ");
    Serial1.println(waarde);
  }
  if (sensorValues[sensorNr] >= blackMin[sensorNr] && sensorValues[sensorNr] <= blackMax[sensorNr]) {
    zwartGedetecteerd = true;
    for 
    //if (sensorValues[0] && zwartGedetecteerd = true) {
    //  s0zwart = true; }
  }

  if (sensorValues[sensorNr] >= greenMin[sensorNr] && sensorValues[sensorNr] <= greenMax[sensorNr]) {
    groenGedetecteerd = true;
  }

  if (sensorValues[sensorNr] >= grayMin[sensorNr] && sensorValues[sensorNr] <= grayMax[sensorNr]) {
    grijsGedetecteerd = true;
  }

  if (zwartGedetecteerd) {
    Serial1.println(">>> ZWARTE LIJN GEDETECTEERD");
    motors.setSpeeds(200, 200);
  } else if (groenGedetecteerd) {
    Serial1.println(">>> GROENE LIJN GEDETECTEERD");
    motors.setSpeeds(100, 100);
  }

  else if (grijsGedetecteerd) {
    Serial1.println(">>> GRIJZE LIJN GEDETECTEERD");
  } else {
    Serial1.println(">>> GEEN LIJN");
  }

  Serial1.println("--------------------");
  delay(100);
}

String Lijnsensor::bepaalRichting() {
  return "richting";
  //TODO richting vastellen afhankelijk van gebruikte positie sensor
