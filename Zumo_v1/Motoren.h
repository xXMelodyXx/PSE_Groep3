#ifndef MOTOREN_H
#define MOTOREN_H

#include <Zumo32U4.h>
#include "Lijnsensor.h"

/*!
  @class Motoren
  @brief Bestuurt motoren en encoders van de Zumo.
*/
class Motoren {

private:

  Zumo32U4Motors motors;
  Zumo32U4Encoders encoders;
  Lijnsensor* lijnsensor;

public:

  /*!
    @brief Constructor van de Motoren klasse.
  */
  Motoren(Lijnsensor*);

  /*!
    @brief Zet snelheid van beide motoren.

    @param links Snelheid linker motor.
    @param rechts Snelheid rechter motor.
  */
  void setSpeed(int links, int rechts);

  /*!
    @brief Stopt beide motoren.
  */
  void stop();

  /*!
    @brief Geeft encoderwaarde links terug.
  */
  long getEncoderLinks();

  /*!
    @brief Geeft encoderwaarde rechts terug.
  */
  long getEncoderRechts();

  /*!
    @brief Reset beide encoders.
  */
  void resetEncoders();

  void initialiseer();
};

#endif