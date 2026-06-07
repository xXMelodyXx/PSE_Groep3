#include "WString.h"
#include "Lijnsensor.h"
#include "XbeeControl.h"
#include "Motoren.h"

Lijnsensor::Lijnsensor() {}
//Zumo32U4Motors motors;
Motoren motors;

void Lijnsensor::init() {
  lineSensors.initFiveSensors();
  for (int i = 0; i < 5; i++) {
    blacksensors.Value[i] = 0;
    blacksensors.Min[i] = 0;
    blacksensors.Max[i] = 0;

    greensensors.Value[i] = 0;
    greensensors.Min[i] = 0;
    greensensors.Max[i] = 0;
  }
}
/*
void Lijnsensor::calibreer(bool debug, int waarde_min[5], int waarde_max[5]) {
  lineSensors.calibrate();
  // bool debug gebruikt om onnodige data outprint te beperken en overzichterlijker te maken
  lineSensors.readCalibrated(sensorValues);
  int gem_waarde[5];
  for (int i = 0; i < 5; i++) {
    waarde_min[i] = sensorValues[i];
    waarde_max[i] = sensorValues[i];

    totaal = 0;

    for (int j = 0; j < 40; j++) {
      lineSensors.readCalibrated(sensorValues);

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
  //lineSensors.read(unsigned int *sensor_values)
  //lineSensors.readLine(unsigned int *sensor_values)

  lineSensors.readCalibrated(sensorValues);
  for (int i = 0; i < 5; i++) {
    blacksensors.Min[i] = sensorValues[i];
    blacksensors.Max[i] = sensorValues[i];

    totaal = 0;

    for (int j = 0; j < 40; j++) {
      lineSensors.readCalibrated(sensorValues);

      totaal += sensorValues[i];
      if (debug == true) {
        Serial1.println(sensorValues[i]);
      }
      if (sensorValues[i] < blacksensors.Min[i]) {
        blacksensors.Min[i] = sensorValues[i];
      }
      if (sensorValues[i] > blacksensors.Max[i]) {
        blacksensors.Max[i] = sensorValues[i];
      }
      delay(5);
    }



    // OPTIE TODO if statements dichtsbijzijnde kleur plaats van tolerantie
    /*
    blacksensors.Value[i] = totaal / 40;
    blacksensors.Min[i] = blacksensors.Min[i] - 30;
    blacksensors.Max[i] = blacksensors.Max[i] + 30;
    */
    //readcalibrated toegevoegd die kijkt naar 0 tot 30

    Serial1.println("ZWART KALIBRATIE KLAAR");
    Serial1.print("zwartwaarde: ");
    Serial1.println(blacksensors.Value[i]);
    Serial1.print("Zwart min: ");
    Serial1.println(blacksensors.Min[i]);
    Serial1.print("Zwart max: ");
    Serial1.println(blacksensors.Max[i]);
  }
}


void Lijnsensor::calibrateGreen(bool debug) {
  lineSensors.calibrate();

  lineSensors.readCalibrated(sensorValues);
  for (int i = 0; i < 5; i++) {
    greensensors.Min[i] = sensorValues[i];
    greensensors.Max[i] = sensorValues[i];

    totaal = 0;
    for (int j = 0; j < 40; j++) {
      lineSensors.readCalibrated(sensorValues);
      totaal += sensorValues[i];
      if (debug == true) {
        Serial1.println(sensorValues[i]);
      }
      if (sensorValues[i] < greensensors.Min[i]) {
        greensensors.Min[i] = sensorValues[i];
      }
      if (sensorValues[i] > greensensors.Max[i]) {
        greensensors.Max[i] = sensorValues[i];
      }
      delay(5);
    }
    /*
    greensensors.Value[i] = totaal / 40;
    greensensors.Min[i] = greensensors.Min[i] - 30;
    greensensors.Max[i] = greensensors.Max[i] + 30;
     */
    //readcalibrated toegevoegd die kijkt naar 0 tot 30

    Serial1.println("GREEN KALIBRATIE KLAAR");
    Serial1.print("greenwaarde: ");
    Serial1.println(greensensors.Value[i]);
    Serial1.print("Green min: ");
    Serial1.println(greensensors.Min[i]);
    Serial1.print("Green max: ");
    Serial1.println(greensensors.Max[i]);

    //TODO voor grijs & bruin
  }
}


void Lijnsensor::calibrateGray(bool debug) {
  lineSensors.calibrate();

  lineSensors.readCalibrated(sensorValues);
  for (int i = 0; i < 5; i++) {
    graysensors.Min[i] = sensorValues[i];
    graysensors.Max[i] = sensorValues[i];

    totaal = 0;
    for (int j = 0; j < 40; j++) {
      lineSensors.readCalibrated(sensorValues);
      totaal += sensorValues[i];
      if (debug == true) {
        Serial1.println(sensorValues[i]);
      }
      if (sensorValues[i] < graysensors.Min[i]) {
        graysensors.Min[i] = sensorValues[i];
      }
      if (sensorValues[i] > graysensors.Max[i]) {
        graysensors.Max[i] = sensorValues[i];
      }
      delay(5);
    }
    /*
    graysensors.Value[i] = totaal / 40;
    graysensors.Min[i] = graysensors.Min[i] - 30;
    graysensors.Max[i] = graysensors.Max[i] + 30;
     */
    //readcalibrated toegevoegd die kijkt naar 0 tot 30

    Serial1.println("GRAY KALIBRATIE KLAAR");
    Serial1.print("graywaarde: ");
    Serial1.println(graysensors.Value[i]);
    Serial1.print("Gray min: ");
    Serial1.println(graysensors.Min[i]);
    Serial1.print("Gray max: ");
    Serial1.println(graysensors.Max[i]);
  }
}

void Lijnsensor::calibrateBrown(bool debug) {
  lineSensors.calibrate();

  lineSensors.readCalibrated(sensorValues);
  for (int i = 0; i < 5; i++) {
    brownsensors.Min[i] = sensorValues[i];
    brownsensors.Max[i] = sensorValues[i];

    totaal = 0;
    for (int j = 0; j < 40; j++) {
      lineSensors.readCalibrated(sensorValues);
      totaal += sensorValues[i];
      if (debug == true) {
        Serial1.println(sensorValues[i]);
      }
      if (sensorValues[i] < brownsensors.Min[i]) {
        brownsensors.Min[i] = sensorValues[i];
      }
      if (sensorValues[i] > brownsensors.Max[i]) {
        brownsensors.Max[i] = sensorValues[i];
      }
      delay(5);
    }
    /*
    brownsensors.Value[i] = totaal / 40;
    brownsensors.Min[i] = brownsensors.Min[i] - 30;
    brownsensors.Max[i] = brownsensors.Max[i] + 30;
     */
    //readcalibrated toegevoegd die kijkt naar 0 tot 30

    Serial1.println("BROWN KALIBRATIE KLAAR");
    Serial1.print("Brown waarde: ");
    Serial1.println(brownsensors.Value[i]);
    Serial1.print("Brown min: ");
    Serial1.println(brownsensors.Min[i]);
    Serial1.print("Brown max: ");
    Serial1.println(brownsensors.Max[i]);
  }
}

bool Lijnsensor::BlackDetected() {
  blacksensors.detected[0] = false;
  blacksensors.detected[1] = false;
  blacksensors.detected[2] = false;
  blacksensors.detected[3] = false;
  blacksensors.detected[4] = false;
  bool blackDetected = false;
  for (int i = 0; i < 5; i++) {
    if (sensorValues[i] >= blacksensors.Min[i] && sensorValues[i] <= blacksensors.Max[i]) {
      bool blackDetected = false;
      if (sensorValues[i] = sensorValues[0]) {
        blacksensors.detected[0] = true;
      }
      if (sensorValues[i] = sensorValues[1]) {
        blacksensors.detected[1] = true;
      }
      if (sensorValues[i] = sensorValues[2]) {
        blacksensors.detected[2] = true;
      }
      if (sensorValues[i] = sensorValues[3]) {
        blacksensors.detected[3] = true;
      }
      if (sensorValues[i] = sensorValues[4]) {
        blacksensors.detected[4] = true;
      }
    }
  }
  if (blacksensors.detected[0] && blacksensors.detected[1] && blacksensors.detected[2]) {
    motors.setSpeed(0, 100);
  }
}

bool Lijnsensor::GreyDetected() {
  graysensors.detected[0] = false;
  graysensors.detected[1] = false;
  graysensors.detected[2] = false;
  graysensors.detected[3] = false;
  graysensors.detected[4] = false;
  bool grayDetected = false;
  for (int i = 0; i < 5; i++) {
    if (sensorValues[i] >= graysensors.Min[i] && sensorValues[i] <= graysensors.Max[i]) {
      bool greyDetected = false;
      if (sensorValues[i] = sensorValues[0]) {
        graysensors.detected[0] = true;
      }
      if (sensorValues[i] = sensorValues[1]) {
        graysensors.detected[1] = true;
      }
      if (sensorValues[i] = sensorValues[2]) {
        graysensors.detected[2] = true;
      }
      if (sensorValues[i] = sensorValues[3]) {
        graysensors.detected[3] = true;
      }
      if (sensorValues[i] = sensorValues[4]) {
        graysensors.detected[4] = true;
      }
    }
  }
  if ((graysensors.detected[0] || graysensors.detected[1]) && (graysensors.detected[3] || graysensors.detected[4])) {
    if ((blacksensors.detected[0] || blacksensors.detected[1]) && (blacksensors.detected[3] || blacksensors.detected[4])) {
      motors.setSpeed(0, 0);
      delay(2000);
      motors.setSpeed(200, 200);
    }
  }

  if (graysensors.detected[0] || graysensors.detected[1]) {
    if ((blacksensors.detected[0] || blacksensors.detected[1]) && (blacksensors.detected[3] || blacksensors.detected[4])) {
      motors.setSpeed(0, 100);
    }
  }

  if (graysensors.detected[3] || graysensors.detected[4]) {
    if ((blacksensors.detected[0] || blacksensors.detected[1]) && (blacksensors.detected[3] || blacksensors.detected[4])) {
      motors.setSpeed(100, 0);
    }
  }
}

/*
void Lijnsensor::readCalibrated(bool debug) {
  lineSensors.readCalibrated(sensorValues);

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
  if (sensorValues[2] >= blacksensors.Min[2] && sensorValues[2] <= blacksensors.Max[2]) {
    zwartGedetecteerd = true;
  }

  if (sensorValues[2] >= greensensors.Min[2] && sensorValues[2] <= greensensors.Max[2]) {
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

void Lijnsensor::read(bool debug, int sensorNr) {
  lineSensors.readCalibrated(sensorValues);


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
  if (sensorValues[sensorNr] >= blacksensors.Min[sensorNr] && sensorValues[sensorNr] <= blacksensors.Max[sensorNr]) {
    zwartGedetecteerd = true;
  }

  if (sensorValues[sensorNr] >= greensensors.Min[sensorNr] && sensorValues[sensorNr] <= greensensors.Max[sensorNr]) {
    groenGedetecteerd = true;
  }

  if (sensorValues[sensorNr] >= graysensors.Min[sensorNr] && sensorValues[sensorNr] <= graysensors.Max[sensorNr]) {
    grijsGedetecteerd = true;
  }

  if (zwartGedetecteerd) {
    Serial1.println(">>> ZWARTE LIJN GEDETECTEERD");
   // motors.setSpeeds(200, 200);
  } else if (groenGedetecteerd) {
    Serial1.println(">>> GROENE LIJN GEDETECTEERD");
    //motors.setSpeeds(100, 100);
  }

  else if (grijsGedetecteerd) {
    Serial1.println(">>> GRIJZE LIJN GEDETECTEERD");
  } else {
    Serial1.println(">>> GEEN LIJN");
  }

  Serial1.println("--------------------");
  delay(100);
}




 

// String Lijnsensor::bepaalRichting() {
//   return "richting";
  //TODO richting vastellen afhankelijk van gebruikte positie sensor


  char Lijnsensor::bepaalRichting() {

  lineSensors.read(sensorValues);

  bool s[5];

  for (int i = 0; i < 5; i++) {

    s[i] =
      sensorValues[i] >= blackMin[i] &&
      sensorValues[i] <= blackMax[i];
  }

  

//rechtdoor
  if (s[2] && !s[0] && !s[4]) {
    return 'D';
  }



//Scherpe links
  if (s[0] && s[1] && s[2]) {
    return 'L';
  }

//Scherpe rechts
  if (s[2] && s[3] && s[4]) {
    return 'R';
  }

}

*/

int Lijnsensor :: bepaalRichting(){
  unsigned int positie = lineSensors.readLine(sensorValues);

  //SCherpe bocht LINKS, tussen S0 en S1 gemiddelde
  if(positie < 500){
    return 1;
  }
  //Scherpe bocht RECHTS, Dit is tussen sensor 3 en 4
  if(positie >3500){
    return 2;
  }
  //Schuine LINKS
  if(positie < 1500){
    return 3;
  }
  //schuine RECHTS
  if(positie > 3000){
    return 4;
  }
  else{
    return 0;
  }
  


}
