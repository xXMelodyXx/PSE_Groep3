#include <Wire.h>
#include <Zumo32U4.h>

class Lijnsensor {
private:
  Zumo32U4LineSensors lineSensors;

  unsigned int sensorValues[5];

  int blackValue[5];
  int blackMin[5];
  int blackMax[5];

  int greenValue[5];
  int greenMin[5];
  int greenMax[5];

  int brownValue[5];
  int brownMin[5];
  int brownMax[5];

  int grayValue[5];
  int grayMin[5];
  int grayMax[5];

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
  void read(bool debug);
  void read(bool debug, int sensorNr);
  char bepaalRichting();
};