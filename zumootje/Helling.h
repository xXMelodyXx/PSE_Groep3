#ifndef HELLING_H
#define HELLING_H

#include <Wire.h>
#include <Zumo32U4.h>

class Helling
{
public:
    Helling();

    /*!
    \brief Starts the helling detection.
    */
    void start();

    /*!
    \brief Check als een helling is gedetecteerd.
    \return True als een helling is gedetecteerd, anders false.
    */
    bool hellingGedetecteerd();


    /*!
    \brief geeft de huidige hoek terug
    \return huidige hoek
    */
    float geefHoek();


    /*!
    \brief berekent de hoek
    \return berekende hoek
    */
    float berekenHoek();

private:
    Zumo32U4IMU imu;

    float beginHoek;
    float huidigeHoek;
};

#endif