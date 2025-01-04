
#include "TXLib.h"
#include "physics.h"
#include "vectors.h"
#include "graphics.h"

Vector ResultForceForPoint (const MassPoint& Point, const MassPoint& Earth, const MassPoint& Moon, bool draw_status);
Vector ResultForceForMoon  (const MassPoint& Earth, const MassPoint& Moon, bool draw_status);

int main ()
{
    _txWindowStyle &= ~WS_CAPTION;
    txCreateWindow (SizeX, SizeY);

    MassPoint Earth = { {       0*KM - DIST_EARTH_CM      ,          0*KM       },  MASS_EARTH, RAD_EARTH, { 0, -EARTH_SPEED } };
    MassPoint Moon  = { { DIST_EARTH_MOON - DIST_EARTH_CM ,          0*KM       },  MASS_MOON , RAD_MOON , { 0,  +MOON_SPEED } };
    MassPoint Comet = { {              0*KM               ,    DIST_EARTH_MOON  },  MASS_COMET, RAD_COMET                      };

    bool PrevButton = false;

    while (txSleep(), !GetAsyncKeyState (VK_ESCAPE))
    {
        POINT ms = txMousePos();
        if (ms.x < 0 || ms.y < 0)
            continue;

        StopClear();

        Draw (Earth, TX_LIGHTGREEN);
        Draw (Moon , TX_WHITE);
        Draw (Comet, TX_LIGHTCYAN);

        MassPoint Mouse = { { XToKMs (ms.x) , YToKMs (ms.y) }, MASS_COMET, RAD_COMET };

        bool CurButton  = txMouseButtons () & 1;

        if (  CurButton && !PrevButton ) { Comet.pos = Mouse.pos;         }               //TODO ->  func  -> "launch comet"
        if ( !CurButton &&  PrevButton ) { Comet.v   = (Comet.pos - Mouse.pos) / 100e3; } //TODO -> Rotate -> Windows with datas
        if (  CurButton  ) Line (Mouse.pos, Comet.pos, TX_WHITE, 1);

        PrevButton = CurButton;

        Vector MoonForceV = ResultForceForMoon  (Earth, Moon,        true);
        Kinematics (&Moon,MoonForceV);

        Vector EarthForceV = ResultForceForMoon (Moon, Earth,        true);
        Kinematics (&Earth, EarthForceV);

        ResultForceForPoint (Mouse, Earth, Moon, true);

        $_(Length (Comet.v));
        $ (Length (Moon.pos));

        if (!CurButton)
        {
            Vector CometForceV = ResultForceForPoint (Comet, Earth, Moon, false);
            Kinematics (&Comet, CometForceV);
        }
    }

    return 0;
}

// #==========================================================================================# //

Vector ResultForceForPoint (const MassPoint& Point, const MassPoint& Earth, const MassPoint& Moon, bool draw_status)
{
    Vector       EarthForceV = Gravity (Earth, Point);
    Vector        MoonForceV = Gravity (Moon , Point);
    //Vector CentrifugalForceV = CentrifugalForce (Point, Earth);

    Vector ResultForceV = EarthForceV + MoonForceV; //+ CentrifugalForceV;

    if (draw_status == true)
    {
        Draw (EarthForceV, Point.pos, TX_LIGHTGREEN, 3);
        Draw (MoonForceV , Point.pos, TX_WHITE, 2);
        Draw (   EarthForceV + MoonForceV  , Point.pos, TX_RED , 2);
        Draw ( -(EarthForceV + MoonForceV) , Point.pos, TX_CYAN, 2);
        // Draw (CentrifugalForceV  * 1, Point.pos, TX_PINK, 1);

        Draw (ResultForceV, Point.pos, TX_YELLOW, 1);
    }

    return ResultForceV;
}

Vector ResultForceForMoon (const MassPoint& Earth, const MassPoint& Moon, bool draw_status)
{
    Vector       EarthForceV = Gravity (Earth, Moon);
//  Vector CentrifugalForceV = CentrifugalForce (Moon, Earth);
    Vector ResultForceV = EarthForceV; // + CentrifugalForceV;

    if (draw_status == true)
    {
//     Draw (EarthForceV / 3e20, Moon.pos, TX_LIGHTGREEN, 3);

//     Draw (CentrifugalForceV  / 3e20, Moon.pos, TX_PINK, 1);

       Draw (ResultForceV / 5e20, Moon.pos, TX_YELLOW, 1);
    }

    return ResultForceV;
}
