#include "TXLib.h"
#include "physics.h"
#include "vectors.h"
#include "graphics.h"

int main ()
{
    txCreateWindow (SizeX, SizeY);

    MassPoint Earth = { {      0*KM    , 0 },  5.9700e24*KG, 6400*KM };
    MassPoint Moon  = { { 384000*KM    , 0 },  0.0735e24*KG, 1737*KM };
    MassPoint Comet = { { 384000*KM / 2, 0 },        100*KG, 0.01*KM };

    while (txSleep(), !GetAsyncKeyState (VK_ESCAPE))
    {
        Draw (Earth, TX_LIGHTGREEN);
        Draw (Moon,  TX_YELLOW);
    }

    return 0;
}
