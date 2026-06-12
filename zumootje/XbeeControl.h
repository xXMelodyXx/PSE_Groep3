/*!
  @file XBeeControl.h
  @brief Headerbestand van de klasse XBeeControl.

  Deze klasse verwerkt de communicatie via XBee
  en bestuurt de motoren van de Zumo robot.
*/

#ifndef XBEECONTROL_H
#define XBEECONTROL_H

#include <Zumo32U4.h>

class XBeeControl {

  private:

    // Motorobject van de Zumo robot
    Zumo32U4Motors motors;

    // Laatst ontvangen commando
    char command;

    // Tijdstip van laatste commando
    unsigned long lastCommandTime;


  public:

    XBeeControl();

    void begin();

    void update();

    /*!
      @brief Laat de robot rijden op basis van een commando.
       toets Letter van het toetsenbord (W, A, S, D, X)
    */
    void rijden(char toets);

};

#endif