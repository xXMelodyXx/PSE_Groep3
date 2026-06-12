#ifndef HELLING_H
#define HELLING_H

#include <Wire.h>
#include <Zumo32U4.h>

class Helling
{
public:
    Helling();

    void start();
    bool hellingGedetecteerd();
    float geefHoek();
    float getBeginHoek();

private:
    Zumo32U4IMU imu;

    float beginHoek;
    float huidigeHoek;
    float berekenHoek();
};

#endif