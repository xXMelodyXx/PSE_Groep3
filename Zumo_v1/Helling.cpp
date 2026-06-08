#include "Helling.h"
#include <math.h>

Helling::Helling()
{
    beginHoek = 0;
    huidigeHoek = 0;
}

void Helling::start()
{
    Wire.begin();

    imu.init();
    imu.enableDefault();

    delay(1000);

    // Zumo moet stil staan tijdens opstarten
    float totaal = 0;

    // Meerdere metingen voor stabielere beginwaarde
    for (int i = 0; i < 20; i++)
    {
        totaal += berekenHoek();
        delay(20);
    }

    beginHoek = totaal / 20;
}

float Helling::berekenHoek()
{
    imu.read();

    int x = imu.a.x;
    int z = imu.a.z;

    // Hoek berekenen in graden
    float hoek = atan2(x, z) * 180.0 / PI;

    return hoek;
}

float Helling::geefHoek()
{
    huidigeHoek = berekenHoek();
    return huidigeHoek;
}

bool Helling::hellingGedetecteerd()
{
    float totaal = 0;

    // Gemiddelde nemen om trillingen te verminderen
    for (int i = 0; i < 5; i++)
    {
        totaal += berekenHoek();
    }

    huidigeHoek = totaal / 5;

    float verschil = huidigeHoek - beginHoek;

    // Positieve helling (omhoog)
    if (verschil > 10)
    {
        return true;
    }

    return false;
}