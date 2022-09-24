#include <stdio.h>
#include <stdlib.h>
//#include <pthread.h>


#include "C:/raylib/raylib/src/raylib.h"
#include "C:/raylib/raylib/src/raymath.h"        // Required for: MatrixRotateXYZ()

#include "CSerialPort.h"

#define GRID_SLICES 40
#define GRID_SPACING 5
#define DIST_PLANE 90 
#define S_WIDTH 1200
#define S_HEIGHT 700
#define SERIAL_MESSAGE_SIZE 1
#define PORTCOM1 1
#define PORTCOM2 2
#define PORTCOM3 3
#define PORTCOM4 4
#define PORTCOM5 5
#define PORTCOM6 6
#define PORTCOM7 7
#define BUFFER_SIZE 18
//AG1P0000R0000Y0000T
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
    Vector2 screen_position; 
} Estacion;


void Estaciones(void);