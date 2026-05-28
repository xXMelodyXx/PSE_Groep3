/*!
  @file XBeeControl.h
  @brief Headerbestand van de klasse XBeeControl.

  Deze klasse verwerkt de communicatie via XBee
  en bestuurt de motoren van de Zumo robot.
*/

#ifndef XBEECONTROL_H
#define XBEECONTROL_H

#include <Zumo32U4.h>

/*!
  @class XBeeControl
  @brief Klasse voor XBee communicatie en motorbesturing.
*/
class XBeeControl {

  private:

    /*!
      @brief Motorobject van de Zumo robot.
    */
    Zumo32U4Motors motors;

    /*!
      @brief Laatst ontvangen commando.
    */
    char command;

    /*!
      @brief Tijdstip van het laatste ontvangen commando.
    */
    unsigned long lastCommandTime;

  public:

    /*!
      @brief Constructor van de klasse XBeeControl.
    */
    XBeeControl();

    /*!
      @brief Initialiseert de seriële communicatie.
    */
    void begin();

    /*!
      @brief Verwerkt XBee input en bestuurt de robot.
    */
    void update();
};

#endif