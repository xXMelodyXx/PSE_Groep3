//#include "WString.h"
#include "Lijnsensor.h"

Lijnsensor::Lijnsensor() {}

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
        Serial.println(sensorValues[i]);
      }
      if (sensorValues[i] < waarde_min[i]) {
        waarde_min[i] = sensorValues[j];
      }
      if (sensorValues[i] > waarde_max[i]) {
        waarde_max[i] = sensorValues[j];
      }
      delay(5);
    }

    // OPTIE TODO if statements dichtsbijzijnde kleur plaats van tolerantie
    gem_waarde[i] = totaal / 40;
    waarde_min[i] = waarde_min[i] - 30;
    waarde_max[i] = waarde_max[i] + 30;
    //tolerantie +/- 120 tijdens testen
    Serial.println("KALIBRATIE KLAAR");
    Serial.print("Gemiddelde: ");
    Serial.println(gem_waarde[i]);
    Serial.print("Minimum: ");
    Serial.println(waarde_min[i]);
    Serial.print("Maximum: ");
    Serial.println(waarde_max[i]);
  }
}

void Lijnsensor::calibrateWhite(bool debug) {
  lineSensors.calibrate();
}
/*
void Lijnsensor::calibrateBlack(bool debug) {
  calibreer(debug, blackMin, blackMax);
}
*/

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
        Serial.println(sensorValues[i]);
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

    Serial.println("ZWART KALIBRATIE KLAAR");
    Serial.print("zwartwaarde: ");
    Serial.println(blackValue[i]);
    Serial.print("Zwart min: ");
    Serial.println(blackMin[i]);
    Serial.print("Zwart max: ");
    Serial.println(blackMax[i]);
  }
}

/*
void Lijnsensor::calibrateGreen(bool debug) {
  calibreer(debug, greenMin, greenMax);
}
*/

void Lijnsensor::calibrateGreen(bool debug) {
  lineSensors.read(sensorValues);
  for (int i = 0; i < 5; i++) {
    greenMin[i] = sensorValues[i];
    greenMax[i] = sensorValues[i];

    totaal = 0;
    for (int j = 0; j < 40; j++) {
      lineSensors.read(sensorValues);
      totaal += sensorValues[i];
      if (debug == true) {
        Serial.println(sensorValues[i]);
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

    Serial.println("GREEN KALIBRATIE KLAAR");
    Serial.print("greenwaarde: ");
    Serial.println(greenValue[i]);
    Serial.print("Green min: ");
    Serial.println(greenMin[i]);
    Serial.print("Green max: ");
    Serial.println(greenMax[i]);
    
    //TODO voor grijs & bruin
  }
}

/*
void Lijnsensor::calibrateBrown(bool debug) {
  calibreer(debug, brownMin, brownMax);
  //calibreer(debug, color_Min[0], color_Max[0]);
}

void Lijnsensor::calibrateGray(bool debug) {
  calibreer(debug, grayMin, grayMax);
}
*/
void Lijnsensor::read(bool debug) {
  lineSensors.read(sensorValues);

  bool zwartGedetecteerd = false;
  bool groenGedetecteerd = false;
  if (debug == true) {
    for (int i = 0; i < 5; i++) {
      int waarde = sensorValues[i];

      Serial.print("Sensor ");
      Serial.print(i);
      Serial.print(": ");
      Serial.println(waarde);
    }
  }
  if (sensorValues[2] >= blackMin[2] && sensorValues[2] <= blackMax[2]) {
    zwartGedetecteerd = true;
  }

  if (sensorValues[2] >= greenMin[2] && sensorValues[2] <= greenMax[2]) {
    groenGedetecteerd = true;
  }
//geen grijs en bruin nog toegevoegd
  if (zwartGedetecteerd) {
    Serial.println(">>> ZWARTE LIJN GEDETECTEERD");
  } else if (groenGedetecteerd) {
    Serial.println(">>> GROENE LIJN GEDETECTEERD");
  } else {
    Serial.println(">>> GEEN LIJN");
  }

  Serial.println("--------------------");
  delay(100);
  // TODO voor sensor 1, 3, 0, 4
  // TODO (if) left, center, right
  // TODO grijs eerst volgende kruising een bocht die kant op
  // TODO bruin stoppen
}

void Lijnsensor::read(bool debug, int sensorNr) {
  lineSensors.read(sensorValues);

  bool zwartGedetecteerd = false;
  bool groenGedetecteerd = false;
  if (debug == true) {

    int waarde = sensorValues[sensorNr];

    Serial.print("Sensor ");
    Serial.print(sensorNr);
    Serial.print(": ");
    Serial.println(waarde);
  }
  if (sensorValues[sensorNr] >= blackMin[sensorNr] && sensorValues[sensorNr] <= blackMax[sensorNr]) {
    zwartGedetecteerd = true;
  }

  if (sensorValues[sensorNr] >= greenMin[sensorNr] && sensorValues[sensorNr] <= greenMax[sensorNr]) {
    groenGedetecteerd = true;
  }

  if (zwartGedetecteerd) {
    Serial.println(">>> ZWARTE LIJN GEDETECTEERD");
  } else if (groenGedetecteerd) {
    Serial.println(">>> GROENE LIJN GEDETECTEERD");
  } else {
    Serial.println(">>> GEEN LIJN");
  }

  Serial.println("--------------------");
  delay(100);
}

String Lijnsensor::bepaalRichting() {
  return "richting";
  //TODO richting vastellen afhankelijk van gebruikte positie sensor
}