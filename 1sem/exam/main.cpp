#include "TXLib.h"
#include "physics.h"
#include "vectors.h"
#include "graphics.h"

Vector ResultForce (MassPoint Point, MassPoint Earth, MassPoint Moon, bool draw_status);

int main ()
{
    txCreateWindow (SizeX, SizeY);

    MassPoint Earth = { {         0*KM          ,          0*KM       },  MASS_EARTH, RAD_EARTH };
    MassPoint Moon  = { {    DIST_EARTH_MOON    ,          0*KM       },  MASS_MOON , RAD_MOON  };
    MassPoint Comet = { {         0*KM          ,    DIST_EARTH_MOON  },  MASS_COMET, RAD_COMET };

    bool PrevButton = false;

    while (txSleep(), !GetAsyncKeyState (VK_ESCAPE))
    {
        POINT ms = txMousePos();
        if (ms.x < 0 || ms.y < 0)
            continue;

        FreezingSystem ();

        Draw (Earth, TX_LIGHTGREEN);
        Draw (Moon , TX_WHITE);
        Draw (Comet, TX_LIGHTCYAN);

        MassPoint Mouse = { { XToKMs (ms.x) , YToKMs (ms.y) }, MASS_COMET, RAD_COMET };

        bool CurButton  = txMouseButtons () & 1;

        if (  CurButton && !PrevButton ) { Comet.pos = Mouse.pos; } //TODO -> func -> "launch comet"
        if ( !CurButton &&  PrevButton ) { Comet.v   = {};        }

        PrevButton = CurButton;

        if (!CurButton)
        {
            Vector CometForceV = ResultForce (Comet, Earth, Moon, false);

            Kinematics (&Comet, CometForceV);
        }

        $( Length( Comet.v ) );

        Vector PointForceV = ResultForce (Mouse, Earth, Moon, true);
    }

    return 0;
}

Vector ResultForce (MassPoint Point, MassPoint Earth, MassPoint Moon, bool draw_status)
{
    Vector       EarthForceV = Gravity (Earth, Point);
    Vector        MoonForceV = Gravity (Moon , Point);
    Vector CentrifugalForceV = CentrifugalForce (Point, Earth);

    Vector ResultForceV = EarthForceV + MoonForceV + CentrifugalForceV;

    if (draw_status == true)
    {
        Draw (EarthForceV, Point.pos, TX_LIGHTGREEN, 3);
        Draw (MoonForceV , Point.pos, TX_WHITE, 3);
        Draw (   EarthForceV + MoonForceV  , Point.pos, TX_RED , 2);
        Draw ( -(EarthForceV + MoonForceV) , Point.pos, TX_CYAN, 2);
        Draw (CentrifugalForceV  * 1, Point.pos, TX_PINK, 1);

        Draw (ResultForceV, Point.pos, TX_YELLOW, 1);
    }

    return ResultForceV;
}

