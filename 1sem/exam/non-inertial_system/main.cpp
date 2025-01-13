
#include "TXLib.h"
#include "physics.h"
#include "vectors.h"
#include "graphics.h"

Vector ResultForce (MassPoint Point, MassPoint Earth, MassPoint Moon, bool draw_status);

int main ()
{
    _txWindowStyle &= ~WS_CAPTION;
    txCreateWindow (SizeX, SizeY);

    MassPoint Earth = { {       0*KM - DIST_EARTH_CM      ,          0*KM       },  MASS_EARTH, RAD_EARTH, { 0, -EARTH_SPEED } };
    MassPoint Moon  = { { DIST_EARTH_MOON - DIST_EARTH_CM ,          0*KM       },  MASS_MOON , RAD_MOON , { 0,  +MOON_SPEED } };
    MassPoint Comet = { {       2.5*DIST_EARTH_MOON       ,    DIST_EARTH_MOON  },  MASS_COMET, RAD_COMET                      };

    MassPoint L_1   = { {  DIST_EARTH_MOON - DIST_EARTH_CM - 61479.2*KM , 0*KM } ,   MASS_COMET, RAD_COMET};
    MassPoint L_2   = { {  DIST_EARTH_MOON - DIST_EARTH_CM + 61479.2*KM , 0*KM } ,   MASS_COMET, RAD_COMET};
    MassPoint L_3   = { {    - 385969.8*KM                              , 0*KM } ,   MASS_COMET, RAD_COMET};   
    MassPoint L_4   = { { (DIST_EARTH_MOON - DIST_EARTH_CM)/2 ,    332553.8*KM } ,   MASS_COMET, RAD_COMET};
    MassPoint L_5   = { { (DIST_EARTH_MOON - DIST_EARTH_CM)/2 ,   -332553.8*KM } ,   MASS_COMET, RAD_COMET};

    bool PrevButton = false;

    while (txSleep(), !GetAsyncKeyState (VK_ESCAPE))
    {
        POINT ms = txMousePos();
        if (ms.x < 0 || ms.y < 0)
            continue;

        StopClear ();

        Draw (Earth, TX_LIGHTGREEN);
        Draw (Moon , TX_WHITE);
        Draw (Comet, TX_LIGHTCYAN);

	Draw (L_1, TX_CYAN);
	Draw (L_2, TX_CYAN);
	Draw (L_3, TX_CYAN);
	Draw (L_4, TX_CYAN);
	Draw (L_5, TX_CYAN);

        MassPoint Mouse = { { XToKMs (ms.x) , YToKMs (ms.y) }, MASS_COMET, RAD_COMET };

        bool CurButton  = txMouseButtons () & 1;

        if (  CurButton && !PrevButton ) { Comet.pos = Mouse.pos;         }               //TODO ->  func  -> "launch comet"
        if ( !CurButton &&  PrevButton ) { Comet.v   = (Comet.pos - Mouse.pos) / 100e3; } //TODO -> Rotate -> Windows with datas
        if (  CurButton  ) Line (Mouse.pos, Comet.pos, TX_WHITE, 1);

        PrevButton = CurButton;

        if (!CurButton)
        {
            Vector CometForceV = ResultForce (Comet, Earth, Moon, true);

            Kinematics (&Comet, CometForceV);
        }

        $ (Length (Comet.v));

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
        Draw (EarthForceV * 175, Point.pos, TX_LIGHTGREEN, 3);
        Draw (MoonForceV * 175 , Point.pos, TX_WHITE, 2);
        //Draw (   (EarthForceV + MoonForceV) * 175, Point.pos, TX_RED , 2);
        //Draw ( -(EarthForceV + MoonForceV) * 175 , Point.pos, TX_CYAN, 2);
        Draw (CentrifugalForceV  * 175, Point.pos, TX_PINK, 1);

        Draw (ResultForceV*175, Point.pos, TX_YELLOW, 1);
    }

    return ResultForceV;
}