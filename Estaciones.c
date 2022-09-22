


#include "Estaciones.h"


static Estacion* Estacion_init(int number, Estacion* ptr_estacion);

void Estaciones(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = S_WIDTH;
    const int screenHeight = S_HEIGHT;

    //SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_HIGHDPI);
    InitWindow(screenWidth, screenHeight, "ESTACIONES");

    Camera camera = { 0 };
    camera.position = (Vector3){ 0.0f, 150.0f, 300.0f };// Camera position perspective
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 30.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera type    

    //fondo
    Texture2D background = LoadTexture("resources/background/sky2.png");
    float scrollingBack = 0.0f;

    
    //inicializa estaciones
    Estacion *ptr_estacion=NULL;
    ptr_estacion = malloc(5 * sizeof(Estacion));
    ptr_estacion = Estacion_init(ESTACION0,ptr_estacion);
    ptr_estacion = Estacion_init(ESTACION1,ptr_estacion);
    ptr_estacion = Estacion_init(ESTACION2,ptr_estacion);
    ptr_estacion = Estacion_init(ESTACION3,ptr_estacion);
    ptr_estacion = Estacion_init(ESTACION4,ptr_estacion);


    SetTargetFPS(100);               // Set our game to run at 60 frames-per-second


    PORT port_COM3 = OpenPort(3);
    char recivestr[SERIAL_MESSAGE_SIZE];


    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        ReciveData(port_COM3, recivestr, SERIAL_MESSAGE_SIZE); 
        //printf("recivo:%s\n",recivestr);   
        // Update
        scrollingBack -= 0.5f;
        if (scrollingBack <= -background.width*2) scrollingBack = 0;
        //----------------------------------------------------------------------------------
        // Plane pitch (x-axis) controls
        if (IsKeyDown(KEY_DOWN)) 
        {
            ptr_estacion[ESTACION0].pitch += 0.6f;
        }
        else if (IsKeyDown(KEY_UP)) 
        {
            ptr_estacion[ESTACION0].pitch -= 0.6f;
        }
        // else
        // {
        //     if (pitch > 0.3f) pitch -= 0.3f;
        //     else if (pitch < -0.3f) pitch += 0.3f;
        // }

        // Plane yaw (y-axis) controls
        if (IsKeyDown(KEY_S)) 
        {
            ptr_estacion[ESTACION0].yaw -= 1.0f;
        }
        else if (IsKeyDown(KEY_A))
        { 
            ptr_estacion[ESTACION0].yaw += 1.0f;
        }
        // else
        // {
        //     if (yaw > 0.0f) yaw -= 0.5f;
        //     else if (yaw < 0.0f) yaw += 0.5f;
        // }

        // Plane roll (z-axis) controls
        if (IsKeyDown(KEY_LEFT)) 
        {
        ptr_estacion[ESTACION0].roll -= 1.0f;
        }
        else if (IsKeyDown(KEY_RIGHT)) 
        {
        ptr_estacion[ESTACION0].roll += 1.0f;
        }
        // else

        // {
        //     if (roll > 0.0f) roll -= 0.5f;
        //     else if (roll < 0.0f) roll += 0.5f;
        // }





        ptr_estacion[ESTACION0].model.transform = MatrixRotateXYZ((Vector3){ DEG2RAD*ptr_estacion[ESTACION0].pitch, DEG2RAD*ptr_estacion[ESTACION0].yaw, DEG2RAD*ptr_estacion[ESTACION0].roll });
        ptr_estacion[ESTACION1].model.transform = MatrixRotateXYZ((Vector3){ DEG2RAD*ptr_estacion[ESTACION1].pitch, DEG2RAD*ptr_estacion[ESTACION1].yaw, DEG2RAD*ptr_estacion[ESTACION1].roll });
        ptr_estacion[ESTACION2].model.transform = MatrixRotateXYZ((Vector3){ DEG2RAD*ptr_estacion[ESTACION2].pitch, DEG2RAD*ptr_estacion[ESTACION2].yaw, DEG2RAD*ptr_estacion[ESTACION2].roll });
        ptr_estacion[ESTACION3].model.transform = MatrixRotateXYZ((Vector3){ DEG2RAD*ptr_estacion[ESTACION3].pitch, DEG2RAD*ptr_estacion[ESTACION3].yaw, DEG2RAD*ptr_estacion[ESTACION3].roll }); 
        ptr_estacion[ESTACION4].model.transform = MatrixRotateXYZ((Vector3){ DEG2RAD*ptr_estacion[ESTACION4].pitch, DEG2RAD*ptr_estacion[ESTACION4].yaw, DEG2RAD*ptr_estacion[ESTACION4].roll });
    
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            //ClearBackground(GetColor(0x052c46ff));
            ClearBackground(SKYBLUE);

            DrawTextureEx(background, (Vector2){ scrollingBack, 0 }, 0.0f, 2.0f, WHITE);
            DrawTextureEx(background, (Vector2){ background.width*2 + scrollingBack, 0 }, 0.0f, 2.0f, WHITE);

            // Draw 3D model (recomended to draw 3D always before 2D)
            BeginMode3D(camera);

                DrawModel( ptr_estacion[ESTACION0].model, ptr_estacion[ESTACION0].position, 0.5f, WHITE);   // Draw 3d model with texture
                DrawModel(ptr_estacion[ESTACION1].model, ptr_estacion[ESTACION1].position, 0.5f, WHITE);   // Draw 3d model with texture
                DrawModel(ptr_estacion[ESTACION2].model, ptr_estacion[ESTACION2].position, 0.5f, WHITE);   // Draw 3d model with texture
                DrawModel(ptr_estacion[ESTACION3].model, ptr_estacion[ESTACION3].position, 0.5f, WHITE);   // Draw 3d model with texture
                DrawModel(ptr_estacion[ESTACION4].model, ptr_estacion[ESTACION4].position, 0.5f, WHITE);   // Draw 3d model with texture
                DrawGrid(GRID_SLICES, (float)GRID_SPACING);
                    
            EndMode3D();
            DrawFPS(50, 50);
            // Draw controls info
            // DrawRectangle(30, 370, 260, 70, Fade(GREEN, 0.5f));
            // DrawRectangleLines(30, 370, 260, 70, Fade(DARKGREEN, 0.5f));
            // DrawText("Pitch controlled with: KEY_UP / KEY_DOWN", 40, 380, 10, DARKGRAY);
            // DrawText("Roll controlled with: KEY_LEFT / KEY_RIGHT", 40, 400, 10, DARKGRAY);
            // DrawText("Yaw controlled with: KEY_A / KEY_S", 40, 420, 10, DARKGRAY);

            // DrawText("(c) WWI Plane Model created by GiaHanLam", screenWidth - 240, screenHeight - 20, 10, DARKGRAY);

        EndDrawing();
        //---------------------------------------------------------------------------------- 
    
    }
    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadModel(ptr_estacion[ESTACION0].model);     // Unload model data
    UnloadModel(ptr_estacion[ESTACION1].model);     // Unload model data
    UnloadModel(ptr_estacion[ESTACION2].model);     // Unload model data
    UnloadModel(ptr_estacion[ESTACION3].model);     // Unload model data
    UnloadModel(ptr_estacion[ESTACION4].model);     // Unload model data
    free(ptr_estacion);
    //CloseWindow();          // Close window and OpenGL context

    UnloadTexture(background);  // Unload background texture
    //--------------------------------------------------------------------------------------

    //return 0;    



}

static Estacion* Estacion_init(int number, Estacion* ptr_estacion)
{
    

    ptr_estacion[number].model = LoadModel("resources/models/obj/plane.obj");         // Load model
    ptr_estacion[number].texture = LoadTexture("resources/models/obj/plane_diffuse.png");  // Load model texture
    ptr_estacion[number].model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = ptr_estacion[number].texture;            // Set map diffuse texture
    ptr_estacion[number].pitch = 0.0f;
    ptr_estacion[number].roll = 0.0f;
    ptr_estacion[number].yaw = 0.0f;
    switch(number)
    {
        case ESTACION0:
            ptr_estacion[number].position = (Vector3){ 0.0f, 0.0f, 0.0f };
            break;
        case ESTACION1:
            ptr_estacion[number].position = (Vector3){ (float)DIST_PLANE, 0.0f, (float)DIST_PLANE };
            break;
        case ESTACION2:
            ptr_estacion[number].position = (Vector3){ -(float)DIST_PLANE, 0.0f, -(float)DIST_PLANE };
            break;
        case ESTACION3:
            ptr_estacion[number].position = (Vector3){ (float)DIST_PLANE, 0.0f, -(float)DIST_PLANE };
            break;
        case ESTACION4:
            ptr_estacion[number].position = (Vector3){ -(float)DIST_PLANE, 0.0f, (float)DIST_PLANE };
            break;   
        default:
            break;             
    }

    

    return ptr_estacion;
}

