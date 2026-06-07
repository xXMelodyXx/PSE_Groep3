#include <Wire.h>
#include <Zumo32U4.h>

struct sensordata {
  int Value[5];
  int Min[5];
  int Max[5];
  bool detected[5];
};

class Lijnsensor {
private:
  Zumo32U4LineSensors lineSensors;

  unsigned int sensorValues[5];


  sensordata blacksensors;
  sensordata greensensors;
  sensordata graysensors;
  sensordata brownsensors;

  /* TO DO array voor kleuren 
  int color_Value[5][4];
  int color_Min[5][4];
  int color_Max[5][4];
  */

  long totaal = 0;

  void calibreer(bool debug, int waarde_min[5], int waarde_max[5]);

public:
  Lijnsensor();
  void init();
  void calibrateWhite(bool debug);
  void calibrateBlack(bool debug);
  void calibrateGreen(bool debug);
  void calibrateBrown(bool debug);
  void calibrateGray(bool debug);
  bool GreyDetected();
  bool BlackDetected();
  void read(bool debug);
  void read(bool debug, int sensorNr);
  char bepaalRichting();
};