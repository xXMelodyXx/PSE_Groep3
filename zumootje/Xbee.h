#ifndef XBEE_H
#define XBEE_H

#include <Arduino.h>
#include <Zumo32U4.h>

/*!
  @class Xbee
  @brief Verwerkt communicatie via XBee
  en leest de knoppen van de Zumo.
*/
class Xbee {

private:

  // Laatst ontvangen commando
  char command;

  // Geeft aan of nieuwe data ontvangen is
  bool beschikbaar;

  // Zumo knoppen
  Zumo32U4ButtonA aKnop;
  Zumo32U4ButtonB bKnop;
  Zumo32U4ButtonC cKnop;
  String text;

public:

void print(String text);
  /*!
    @brief Constructor van de Xbee klasse.
  */
  Xbee();

  /*!
    @brief Start de communicatie.
  */
  void begin();

  /*!
    @brief Leest nieuwe data van de XBee.
  */
  void update();

  /*!
    @brief Controleert of een toets via XBee is ontvangen.

    @param toets Toets die gecontroleerd wordt.
    @return true als toets ontvangen is.
    @return false als toets niet ontvangen is.
  */
  bool toetsIngedrukt(char toets);

  /*!
    @brief Controleert of knop A is ingedrukt.
  */
  bool knopA();

  /*!
    @brief Controleert of knop B is ingedrukt.
  */
  bool knopB();

  /*!
    @brief Controleert of knop C is ingedrukt.
  */
  bool knopC();

  /*!
    @brief Geeft laatste ontvangen commando terug.
  */
  char getCommand();
};

#endif