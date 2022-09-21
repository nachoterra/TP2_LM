#include <stdio.h>
#include <stdlib.h>

#include "C:/raylib/raylib/src/raylib.h"
#include "C:/raylib/raylib/src/raymath.h"        // Required for: MatrixRotateXYZ()

//#include "lib/CSerialPort.h"

#define GRID_SLICES 40
#define GRID_SPACING 5
#define DIST_PLANE 75 
#define S_WIDTH 1200
#define S_HEIGHT 700

enum Estaciones
{
    ESTACION0,
    ESTACION1,
    ESTACION2,
    ESTACION3,
    ESTACION4
};


typedef struct Estacion {
    Texture2D texture;      // textura
    Model model;            // objeto
    float pitch;            // cabeceo
    float roll;            // rolido
    float yaw;            // orientacion
    Vector3 position;     //posicion
} Estacion;


void Estaciones(void);