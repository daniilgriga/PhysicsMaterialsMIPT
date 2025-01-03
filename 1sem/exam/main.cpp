#include "TXLib.h"
#include "physics.h"
#include "vectors.h"
#include "graphics.h"

int main ()
{
    txCreateWindow (SizeX, SizeY);

    MassPoint Earth = { {         0*KM          ,          0*KM       },  MASS_EARTH, RAD_EARTH };
    MassPoint Moon  = { {    DIST_EARTH_MOON    ,          0*KM       },  MASS_MOON , RAD_MOON  };
    MassPoint Comet = { {         0*KM          ,    DIST_EARTH_MOON  },  MASS_COMET, RAD_COMET };

    while (txSleep(), !GetAsyncKeyState (VK_ESCAPE))
    {
        POINT Mouse = txMousePos();
        if (Mouse.x < 0 || Mouse.y < 0)
            continue;

        FreezingSystem ();

        Draw (Earth, TX_LIGHTGREEN);
        Draw (Moon , TX_WHITE);
        Draw (Comet, TX_LIGHTCYAN);

        MassPoint MouseComet = { { XToKMs (Mouse.x) , YToKMs (Mouse.y) }, MASS_COMET, RAD_COMET };

        bool LeftButton = txMouseButtons () & 1;

    }

    return 0;
}
