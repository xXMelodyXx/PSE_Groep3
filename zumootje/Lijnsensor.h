#include <Wire.h>
#include <Zumo32U4.h>
#include "HardwareSerial.h"
#include "WString.h"
#include "Xbee.h"
#include "Motoren.h"
#include "Helling.h"
#include "ProximityBlok.h"
#define NMRSENSOR 5

struct sensordata {
  int Gemiddelde[5];
  int Min[5];
  int Max[5];
  bool detected[5];
};

class Lijnsensor {

private:
  Zumo32U4LineSensors lineSensors;
  Helling helling;
  ProximityBlok* proximityBlok;
  Zumo32U4ButtonB buttonB;
  unsigned int sensorValues[5];
  int positie;

  bool grijsLinks = false;
  bool grijsRechts = false;
  bool grijsActief = false;


  sensordata groensensors;
  sensordata grijssensors;
  sensordata bruinsensors;
  sensordata zwartsensors;

  int hoeveelMetingen;
  Xbee* xb;
  Zumo32U4ButtonC buttonC;


public:
  /*! \brief Constructor voor de Lijnsensor klasse
  *  \param xbee Pointer naar de Xbee klasse voor communicatie
  *  \param p Pointer toegevoegd voor toegang tot ProximityBlok functies
  */
  Lijnsensor(Xbee* xbee, ProximityBlok* p);

  /*! 
  \brief Initialiseert de lijnsensor, inclusief kalibratie
  */
  void init();

  /*! 
  \brief Leest de lijnsensoren en roept de juiste kalibratiefunctie 
  aan per kleur (wit, zwart, groen, bruin, grijs)
  */
  void getCalibratie();

  /*! 
  \brief Kalibreert de sensoren voor wit
   */
  void calibrateWit();

  /*! 
  \brief Kalibreert de sensoren voor zwart
   */
  void calibrateZwart();

  /*! 
    \brief Kalibreert de sensoren voor groen
    */
  void calibrateGroen();

  /*! 
  \brief Kalibreert de sensoren voor Bruin
  */
  void calibrateBruin();

  /*! 
  \brief Kalibreert de sensoren voor grijs
  */
  void calibrateGrijs();

  /*! \brief Leest de positie van de lijn. 
   *  \return 1000 als bij sensor 0, 2000 als bij sensor 1, ..., 5000 als bij sensor 4.
   *  \return 3000 als geen lijn gedetecteerd (gaat dan gewoon rechtdoor)
   */
  int leesPositie();

  /*! 
  \brief Voert een eenvoudige kalibratie uit om de zumo 
  voor te bereiden op het detecteren van kleuren
   */
  void simpelCalibreer();

  /*! 
  \brief Kalibreert de sensoren voor een bepaalde kleur
   */
  sensordata calibreer(String kleur);

  /*! 
  \brief Haalt het gemiddelde van de sensordata op
   */
  sensordata getGemiddelde(int hoeveelMetingen);

  /*! 
  \brief Controleert of grijs gedetecteerd is
   */
  bool GrijsDetected(sensordata);

  /*! 
  \brief Controleert of groen gedetecteerd is
   */
  bool GroenDetected(sensordata);

  /*! 
  \brief Controleert of bruin gedetecteerd is
   */
  bool BruinDetected(sensordata);

  /*! 
  \brief Controleert of zwart gedetecteerd is
   */
  bool ZwartDetected(sensordata);

  /*! 
  \brief Controleert of een zwart kruispunt gedetecteerd is
   */
  bool zwartKruispunt();

  /*! 
    \brief Bepaalt de positie van het grijze tape
    \param data De sensordata
    \return 2 als tape links, 3 als tape rechts, 6 als tape in het midden, anders -1
   */
  int GrijsPosition(sensordata);

  /*! 
    \brief Logica voor wat er moet gebeuren als grijs tape wordt gedetecteerd
    \param motoren De motoren
   */
  bool handleGrijsTape(Motoren);


  /*! 
      \brief Bepaalt welke case moet worden uitgevoerd
      \return Een integer die de actie aangeeft
    */
  int bepaalCase();



  // void resetGrijs();
};