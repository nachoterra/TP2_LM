#include "Estaciones.h"


static Estacion* Estacion_init(int number, Estacion* ptr_estacion);
static void matrixrotation(int number, Estacion* ptr_estacion);
static void keyboard_control(Estacion* ptr_estacion);
static float check_angle(float number,int flag);

void Estaciones(void)
{
    // ----------------------------Initialization--------------------------------------------------------------
    
    //-------------------------------PANTALLA------------------------------------------------------------------
    const int screenWidth = S_WIDTH;
    const int screenHeight = S_HEIGHT;
    //SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_HIGHDPI);
    InitWindow(screenWidth, screenHeight, "ESTACIONES");
    //---------------------------------------------------------------------------------------------------------

    //---------------------------------AUDIO-------------------------------------------------------------------
    InitAudioDevice();
    Music music = LoadMusicStream("AUDIO/audio.mp3");
    PlayMusicStream(music);
    float timePlayed =0.0f;
    bool music_pause = false;
    //---------------------------------------------------------------------------------------------------------

    //---------------------------------PAUSA-------------------------------------------------------------------
    bool pause = false;
    int framesCounter = 0;
    //---------------------------------------------------------------------------------------------------------



    
    //---------------------------------------CAMERA------------------------------------------------------------
    bool camera_mode= false;
    Camera camera = { 0 };
    camera.position = (Vector3){ 0.0f, 200.0f, 300.0f };// Camera position perspective
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 30.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera type    
    //---------------------------------------------------------------------------------------------------------
    

    //--------------------------------fondo--------------------------------------------------------------------
    Texture2D background = LoadTexture("resources/background/sky2.png");
    float scrollingBack = 0.0f;
    //---------------------------------------------------------------------------------------------------------
    
    //-------------------------------------Constructor estaciones----------------------------------------------
    Estacion *ptr_estacion=NULL;
    ptr_estacion = malloc(5 * sizeof(Estacion));
    ptr_estacion = Estacion_init(ESTACION0,ptr_estacion);
    ptr_estacion = Estacion_init(ESTACION1,ptr_estacion);
    ptr_estacion = Estacion_init(ESTACION2,ptr_estacion);
    ptr_estacion = Estacion_init(ESTACION3,ptr_estacion);
    ptr_estacion = Estacion_init(ESTACION4,ptr_estacion);
    //---------------------------------------------------------------------------------------------------------

    

    //-------------------------------------INICIALIZA PUERTO SERIE---------------------------------------------
    PORT port_COM3 = OpenPort(PORTCOM4);
    SetPortBoudRate(port_COM3, CP_BOUD_RATE_9600);
    char recivestr[SERIAL_MESSAGE_SIZE];
    int count=0;
    int flag=0;
    char buffer[BUFFER_SIZE] ={0};
    char* pitch_ptr=&buffer[4];
    char* roll_ptr=&buffer[9];
    char* yaw_ptr=&buffer[14];
    //---------------------------------------------------------------------------------------------------------

    //----------------------------------FRAMES POR SEGUNDO-----------------------------------------------------
    SetTargetFPS(FPS);               // Set our game to run at 60 frames-per-second
    //---------------------------------------------------------------------------------------------------------



    //-----------------------------------------CICLO DEL PROGRAMA----------------------------------------------------------------
    //---------------------------------------------------------------------------------------------------------
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        //------------------------------------PANTALLA COMPLETA------------------------------------------------
        if(IsKeyPressed(KEY_F11))
        {
            ToggleFullscreen();
        }
        //-----------------------------------------------------------------------------------------------------

        
        //-------------------------------------------CAMARA UPDATE----------------------------------------------------
        // CAMBIA MODO DE CAMERA A CAMARA LIBRE
        // SE MUEVE Y HACE ZOOM CON EL MOUSE
        if(IsKeyPressed(KEY_F))
        {
            camera_mode =!camera_mode;
            if(camera_mode)
            {
                SetCameraMode(camera, CAMERA_FREE); // Set a free camera mode 
            }
            else
            {
                SetCameraMode(camera, CAMERA_CUSTOM); // Set a free camera mode
            }
            
        }
        //DEVUELVE LA CAMARA A POSICION INICIAL 
        if (IsKeyDown('Z')) 
        {
            camera.position = (Vector3){ 0.0f, 200.0f, 300.0f };// Camera position perspective
            camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
            camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
            camera.fovy = 30.0f;                                // Camera field-of-view Y
            camera.projection = CAMERA_PERSPECTIVE;             // Camera type 
            
        }
        UpdateCamera(&camera);
        //-----------------------------------------------------------------------------------------------------



        
        //------------------------------AUDIO UPDATE-----------------------------------------------------------
        UpdateMusicStream(music);

        // Pause/Resume music playing
        if (IsKeyPressed(KEY_M))
        {
            music_pause = !music_pause;

            if (music_pause) PauseMusicStream(music);
            else ResumeMusicStream(music);
        }
        // Get normalized time played for current music stream
        timePlayed = GetMusicTimePlayed(music)/GetMusicTimeLength(music);
        if (timePlayed > 1.0f) timePlayed = 1.0f;   // Make sure time played is no longer than music
        //-----------------------------------------------------------------------------------------------------


        //------------------------------------BACKGROPUND SCROLL-----------------------------------------------
        scrollingBack -= 0.5f;
        if (scrollingBack <= -background.width*2) scrollingBack = 0;
        //-----------------------------------------------------------------------------------------------------
        



        //----------------------------------------PAUSA--------------------------------------------------------
        if(IsKeyPressed(KEY_P))
        {
            pause= !pause;
        }
        
        if(!pause)
        {
            //mueve los aviones con las flechitas y A y S
            keyboard_control(ptr_estacion);
        
            //---------------------LEE PUERTO SERIE-----------------
            if(ReciveData(port_COM3, recivestr, SERIAL_MESSAGE_SIZE))
            {
                if(recivestr[0]=='A')
                {
                    count=0;
                    flag=1;
                } 
                if(flag)
                {
                buffer[count]=recivestr[0];
                count++;
                if(count==BUFFER_SIZE)
                {
                // ptr_estacion[ESTACION1].pitch = atoi(pitch_ptr);
                    //ptr_estacion[ESTACION1].roll = atoi(roll_ptr);
                    //ptr_estacion[ESTACION1].yaw = atoi(yaw_ptr);
                    count=0;
                    flag=0;
                }
                }

            }
            else
            {
                printf("error recieve");
            }

        }
        else
        {
            framesCounter++;
        }
        //-----------------------------------------------------------------------------------------------------





        background.id=3; // arregla problema de fondo

        //-----------------------------------------ROTACION AVIONES--------------------------------------------
        matrixrotation(ESTACION0,  ptr_estacion);
        matrixrotation(ESTACION1,  ptr_estacion);
        matrixrotation(ESTACION2,  ptr_estacion);
        matrixrotation(ESTACION3,  ptr_estacion);
        matrixrotation(ESTACION4,  ptr_estacion);
        //-----------------------------------------------------------------------------------------------------
        
         
       
    
        // Calculate planes space position (with a little offset to be in top)
        ptr_estacion[ESTACION0].screen_position = GetWorldToScreen((Vector3){ptr_estacion[ESTACION0].position.x, ptr_estacion[ESTACION0].position.y + 2.5f, ptr_estacion[ESTACION0].position.z}, camera);
        ptr_estacion[ESTACION1].screen_position = GetWorldToScreen((Vector3){ptr_estacion[ESTACION1].position.x, ptr_estacion[ESTACION1].position.y + 2.5f, ptr_estacion[ESTACION1].position.z}, camera);
        ptr_estacion[ESTACION2].screen_position = GetWorldToScreen((Vector3){ptr_estacion[ESTACION2].position.x, ptr_estacion[ESTACION2].position.y + 2.5f, ptr_estacion[ESTACION2].position.z}, camera);
        ptr_estacion[ESTACION3].screen_position = GetWorldToScreen((Vector3){ptr_estacion[ESTACION3].position.x, ptr_estacion[ESTACION3].position.y + 2.5f, ptr_estacion[ESTACION3].position.z}, camera);
        ptr_estacion[ESTACION4].screen_position = GetWorldToScreen((Vector3){ptr_estacion[ESTACION4].position.x, ptr_estacion[ESTACION4].position.y + 2.5f, ptr_estacion[ESTACION4].position.z}, camera);
        
        
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            //ClearBackground(GetColor(0x052c46ff));
            ClearBackground(SKYBLUE);
            //DrawTexture(background, 0, 0, WHITE);
            DrawTextureEx(background, (Vector2){ scrollingBack, 0 }, 0.0f, 2.0f, WHITE);
            DrawTextureEx(background, (Vector2){ background.width*2 + scrollingBack, 0 }, 0.0f, 2.0f, WHITE);

            // Draw 3D model (recomended to draw 3D always before 2D)
            BeginMode3D(camera);

                DrawModel( ptr_estacion[ESTACION0].model, ptr_estacion[ESTACION0].position, 0.5f, WHITE);   // Draw 3d model with texture
                DrawModel(ptr_estacion[ESTACION1].model, ptr_estacion[ESTACION1].position, 0.5f, WHITE);   // Draw 3d model with texture
                DrawModel(ptr_estacion[ESTACION2].model, ptr_estacion[ESTACION2].position, 0.5f, WHITE);   // Draw 3d model with texture
                DrawModel(ptr_estacion[ESTACION3].model, ptr_estacion[ESTACION3].position, 0.5f, WHITE);   // Draw 3d model with texture
                DrawModel(ptr_estacion[ESTACION4].model, ptr_estacion[ESTACION4].position, 0.5f, WHITE);   // Draw 3d model with texture
               // DrawModelEx(ptr_estacion[ESTACION0].model,ptr_estacion[ESTACION0].position,(Vector3){ 1,1,1 },ptr_estacion[ESTACION4].pitch,(Vector3){ 0.5f,0.5f,0.5f }, WHITE);
                //DrawGrid(GRID_SLICES, (float)GRID_SPACING);
                // DrawLine3D((Vector3){ 0,0,0 },(Vector3){ 100,0,0 },BLACK);   
                // DrawLine3D((Vector3){ 0,0,0 },(Vector3){ 0,100,0 },MAROON);   
                // DrawLine3D((Vector3){ 0,0,0 },(Vector3){ 0,0,100 },BLUE); 
            EndMode3D();
            DrawFPS(50, 50);
            // Draw controls info
            // DrawRectangle(30, 370, 260, 70, Fade(GREEN, 0.5f));
            // DrawRectangleLines(30, 370, 260, 70, Fade(DARKGREEN, 0.5f));

            //---------------ESCRIBE POSICIONES DE CADA AVION----------------------------------------------
            DrawText(TextFormat("ESTACION: %01i\nPITCH: %04i\nROLL:   %04i\nYAW:    %04i",ESTACION0,(int)ptr_estacion[ESTACION0].pitch,(int)ptr_estacion[ESTACION0].roll,(int)ptr_estacion[ESTACION0].yaw), (int)ptr_estacion[ESTACION0].screen_position.x - MeasureText(TextFormat("ESTACION: %01i\nPITCH: %04i\nROLL:   %04i\nYAW:    %04i",ESTACION0,(int)ptr_estacion[ESTACION0].pitch,(int)ptr_estacion[ESTACION0].roll,(int)ptr_estacion[ESTACION0].yaw), 10)/2, (int)ptr_estacion[ESTACION0].screen_position.y-150, 10, BLACK);
            DrawText(TextFormat("ESTACION: %01i\nPITCH: %04i\nROLL:   %04i\nYAW:    %04i",ESTACION1,(int)ptr_estacion[ESTACION1].pitch,(int)ptr_estacion[ESTACION1].roll,(int)ptr_estacion[ESTACION1].yaw), (int)ptr_estacion[ESTACION1].screen_position.x - MeasureText(TextFormat("ESTACION: %01i\nPITCH: %04i\nROLL:   %04i\nYAW:    %04i",ESTACION1,(int)ptr_estacion[ESTACION1].pitch,(int)ptr_estacion[ESTACION1].roll,(int)ptr_estacion[ESTACION1].yaw), 10)/2, (int)ptr_estacion[ESTACION1].screen_position.y-150, 10, BLACK);
            DrawText(TextFormat("ESTACION: %01i\nPITCH: %04i\nROLL:   %04i\nYAW:    %04i",ESTACION2,(int)ptr_estacion[ESTACION2].pitch,(int)ptr_estacion[ESTACION2].roll,(int)ptr_estacion[ESTACION2].yaw), (int)ptr_estacion[ESTACION2].screen_position.x - MeasureText(TextFormat("ESTACION: %01i\nPITCH: %04i\nROLL:   %04i\nYAW:    %04i",ESTACION2,(int)ptr_estacion[ESTACION2].pitch,(int)ptr_estacion[ESTACION2].roll,(int)ptr_estacion[ESTACION2].yaw), 10)/2, (int)ptr_estacion[ESTACION2].screen_position.y-150, 10, BLACK);
            DrawText(TextFormat("ESTACION: %01i\nPITCH: %04i\nROLL:   %04i\nYAW:    %04i",ESTACION3,(int)ptr_estacion[ESTACION3].pitch,(int)ptr_estacion[ESTACION3].roll,(int)ptr_estacion[ESTACION3].yaw), (int)ptr_estacion[ESTACION3].screen_position.x - MeasureText(TextFormat("ESTACION: %01i\nPITCH: %04i\nROLL:   %04i\nYAW:    %04i",ESTACION3,(int)ptr_estacion[ESTACION3].pitch,(int)ptr_estacion[ESTACION3].roll,(int)ptr_estacion[ESTACION3].yaw), 10)/2, (int)ptr_estacion[ESTACION3].screen_position.y-150, 10, BLACK);
            DrawText(TextFormat("ESTACION: %01i\nPITCH: %04i\nROLL:   %04i\nYAW:    %04i",ESTACION4,(int)ptr_estacion[ESTACION4].pitch,(int)ptr_estacion[ESTACION4].roll,(int)ptr_estacion[ESTACION4].yaw), (int)ptr_estacion[ESTACION4].screen_position.x - MeasureText(TextFormat("ESTACION: %01i\nPITCH: %04i\nROLL:   %04i\nYAW:    %04i",ESTACION4,(int)ptr_estacion[ESTACION4].pitch,(int)ptr_estacion[ESTACION4].roll,(int)ptr_estacion[ESTACION4].yaw), 10)/2, (int)ptr_estacion[ESTACION4].screen_position.y-150, 10, BLACK);
            
            // On pause, we draw a blinking message
            if (pause && ((framesCounter/30)%2)) DrawText("PAUSED", screenWidth/2-MeasureText("PAUSED",40)/2, screenHeight/2, 40, GRAY);




            

            //com_port= GuiTextInputBox((Rectangle){600,40,120,20}, "COM","Enter COM number","OK",NULL,50,NULL);
            
            DrawText("(c) Laboratorio de Microprosesadores - Grupo 4", screenWidth - MeasureText("(c) Laboratorio de Microprosesadores - Grupo 4",10)-20, screenHeight - 20, 10, DARKGRAY);
        
        EndDrawing();


    }



    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadModel(ptr_estacion[ESTACION0].model);     // Unload model data
    UnloadModel(ptr_estacion[ESTACION1].model);     // Unload model data
    UnloadModel(ptr_estacion[ESTACION2].model);     // Unload model data
    UnloadModel(ptr_estacion[ESTACION3].model);     // Unload model data
    UnloadModel(ptr_estacion[ESTACION4].model);     // Unload model data
    free(ptr_estacion);
    CloseWindow();          // Close window and OpenGL context

    UnloadTexture(background);  // Unload background texture

    UnloadMusicStream(music);   // Unload music stream buffers from RAM

    CloseAudioDevice();         // Close audio device (music streaming is automatically stopped)
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
        case ESTACION3:
            ptr_estacion[number].position = (Vector3){ 0.0f, 0.0f, 0.0f };
            ptr_estacion[number].screen_position = (Vector2){ 0.0f, 0.0f };
            break;
        case ESTACION1:
            ptr_estacion[number].position = (Vector3){ (float)DIST_PLANE, 0.0f, (float)DIST_PLANE };
            ptr_estacion[number].screen_position = (Vector2){ (float)DIST_PLANE, 0.0f};
            break;
        case ESTACION2:
            ptr_estacion[number].position = (Vector3){ -(float)DIST_PLANE, 0.0f, -(float)DIST_PLANE };
            ptr_estacion[number].screen_position = (Vector2){ -(float)DIST_PLANE, 0.0f};
            break;
        case ESTACION4:
            ptr_estacion[number].position = (Vector3){ (float)DIST_PLANE, 0.0f, -(float)DIST_PLANE };
            ptr_estacion[number].screen_position = (Vector2){ (float)DIST_PLANE, 0.0f};
            break;
        case ESTACION0:
            ptr_estacion[number].position = (Vector3){ -(float)DIST_PLANE, 0.0f, (float)DIST_PLANE };
            ptr_estacion[number].screen_position = (Vector2){ -(float)DIST_PLANE, 0.0f};
            break;   
        default:
            break;             
    }

    

    return ptr_estacion;
}

static void matrixrotation(int number, Estacion* ptr_estacion)
{
    Matrix matrizY = { 0 }; 
    Matrix matrizX = { 0 };
    Matrix matrizZ = { 0 };    
    Matrix matrizFINAL = { 0 }; 


    matrizX.m0 = 1;
    matrizX.m4 = 0;
    matrizX.m8 = 0;
    matrizX.m12 = 0;

    matrizX.m1 = 0;
    matrizX.m5 = cosf(-DEG2RAD*ptr_estacion[number].pitch);
    matrizX.m9 = -sinf(-DEG2RAD*ptr_estacion[number].pitch);
    matrizX.m13 = 0;

    matrizX.m2 = 0;
    matrizX.m6 = sinf(-DEG2RAD*ptr_estacion[number].pitch);
    matrizX.m10 = cosf(-DEG2RAD*ptr_estacion[number].pitch);
    matrizX.m14 = 0;

    matrizX.m3 = 0;
    matrizX.m7 = 0;
    matrizX.m11 = 0;
    matrizX.m15 = 1;



    matrizZ.m0 = cosf(-DEG2RAD*ptr_estacion[number].roll);
    matrizZ.m4 = -sinf(-DEG2RAD*ptr_estacion[number].roll);
    matrizZ.m8 = 0;
    matrizZ.m12 = 0;

    matrizZ.m1 = sinf(-DEG2RAD*ptr_estacion[number].roll);
    matrizZ.m5 = cosf(-DEG2RAD*ptr_estacion[number].roll);
    matrizZ.m9 = 
    matrizZ.m13 = 0;

    matrizZ.m2 = 0;
    matrizZ.m6 = 0;
    matrizZ.m10 = 1;
    matrizZ.m14 = 0;

    matrizZ.m3 = 0;
    matrizZ.m7 = 0;
    matrizZ.m11 = 0;
    matrizZ.m15 = 1;



    matrizY.m0 = cosf(-DEG2RAD*ptr_estacion[number].yaw);
    matrizY.m4 = 0;
    matrizY.m8 = sinf(-DEG2RAD*ptr_estacion[number].yaw);
    matrizY.m12 = 0;

    matrizY.m1 = 0;
    matrizY.m5 = 1;
    matrizY.m9 = 0;
    matrizY.m13 = 0;

    matrizY.m2 = -sinf(-DEG2RAD*ptr_estacion[number].yaw);
    matrizY.m6 = 0;
    matrizY.m10 = cosf(-DEG2RAD*ptr_estacion[number].yaw);
    matrizY.m14 = 0;

    matrizY.m3 = 0;
    matrizY.m7 = 0;
    matrizY.m11 = 0;
    matrizY.m15 = 1;   

    // if((ptr_estacion[number].yaw != 0.0f) && (ptr_estacion[number].pitch != 0.0f)  )
    // {
        matrizFINAL = MatrixMultiply(matrizZ,matrizX);
        matrizFINAL = MatrixMultiply(matrizFINAL,matrizY);
    // }
    // else
    // {
    //     matrizFINAL = MatrixMultiply(matrizZ,matrizX);
    //     matrizFINAL = MatrixMultiply(matrizY,matrizFINAL);
    // }

    ptr_estacion[number].model.transform = matrizFINAL;
}

static void keyboard_control(Estacion* ptr_estacion)
{
        //----------------------------------------------------------------------------------
        // Plane pitch (x-axis) controls
        if (IsKeyDown(KEY_UP)) 
        {
            ptr_estacion[ESTACION0].pitch =check_angle(ptr_estacion[ESTACION0].pitch,TRUE);
            ptr_estacion[ESTACION1].pitch =check_angle(ptr_estacion[ESTACION1].pitch,TRUE);
            ptr_estacion[ESTACION2].pitch =check_angle(ptr_estacion[ESTACION2].pitch,TRUE);
            ptr_estacion[ESTACION3].pitch =check_angle(ptr_estacion[ESTACION3].pitch,TRUE);
            ptr_estacion[ESTACION4].pitch =check_angle(ptr_estacion[ESTACION4].pitch,TRUE);

        }
        else if (IsKeyDown(KEY_DOWN)) 
        {
            ptr_estacion[ESTACION0].pitch =check_angle(ptr_estacion[ESTACION0].pitch,FALSE);
            ptr_estacion[ESTACION1].pitch =check_angle(ptr_estacion[ESTACION1].pitch,FALSE);
            ptr_estacion[ESTACION2].pitch =check_angle(ptr_estacion[ESTACION2].pitch,FALSE);
            ptr_estacion[ESTACION3].pitch =check_angle(ptr_estacion[ESTACION3].pitch,FALSE);
            ptr_estacion[ESTACION4].pitch =check_angle(ptr_estacion[ESTACION4].pitch,FALSE);

        }
        // else
        // {
        //     if (pitch > 0.3f) pitch -= 0.3f;
        //     else if (pitch < -0.3f) pitch += 0.3f;
        // }

        // Plane yaw (y-axis) controls
        if (IsKeyDown(KEY_A)) 
        {
            ptr_estacion[ESTACION0].yaw =check_angle(ptr_estacion[ESTACION0].yaw,TRUE);
            ptr_estacion[ESTACION1].yaw =check_angle(ptr_estacion[ESTACION1].yaw,TRUE);
            ptr_estacion[ESTACION2].yaw =check_angle(ptr_estacion[ESTACION2].yaw,TRUE);
            ptr_estacion[ESTACION3].yaw =check_angle(ptr_estacion[ESTACION3].yaw,TRUE);
            ptr_estacion[ESTACION4].yaw =check_angle(ptr_estacion[ESTACION4].yaw,TRUE);            

        }
        else if (IsKeyDown(KEY_S))
        { 
            
            ptr_estacion[ESTACION0].yaw =check_angle(ptr_estacion[ESTACION0].yaw,FALSE);
            ptr_estacion[ESTACION1].yaw =check_angle(ptr_estacion[ESTACION1].yaw,FALSE);
            ptr_estacion[ESTACION2].yaw =check_angle(ptr_estacion[ESTACION2].yaw,FALSE);
            ptr_estacion[ESTACION3].yaw =check_angle(ptr_estacion[ESTACION3].yaw,FALSE);
            ptr_estacion[ESTACION4].yaw =check_angle(ptr_estacion[ESTACION4].yaw,FALSE); 
        }
        // else
        // {
        //     if (yaw > 0.0f) yaw -= 0.5f;
        //     else if (yaw < 0.0f) yaw += 0.5f;
        // }

        // Plane roll (z-axis) controls
        if (IsKeyDown(KEY_RIGHT)) 
        {
            ptr_estacion[ESTACION0].roll =check_angle(ptr_estacion[ESTACION0].roll,TRUE);
            ptr_estacion[ESTACION1].roll =check_angle(ptr_estacion[ESTACION1].roll,TRUE);
            ptr_estacion[ESTACION2].roll =check_angle(ptr_estacion[ESTACION2].roll,TRUE);
            ptr_estacion[ESTACION3].roll =check_angle(ptr_estacion[ESTACION3].roll,TRUE);
            ptr_estacion[ESTACION4].roll =check_angle(ptr_estacion[ESTACION4].roll,TRUE);             

        
        }
        else if (IsKeyDown(KEY_LEFT)) 
        {
            ptr_estacion[ESTACION0].roll =check_angle(ptr_estacion[ESTACION0].roll,FALSE);
            ptr_estacion[ESTACION1].roll =check_angle(ptr_estacion[ESTACION1].roll,FALSE);
            ptr_estacion[ESTACION2].roll =check_angle(ptr_estacion[ESTACION2].roll,FALSE);
            ptr_estacion[ESTACION3].roll =check_angle(ptr_estacion[ESTACION3].roll,FALSE);
            ptr_estacion[ESTACION4].roll =check_angle(ptr_estacion[ESTACION4].roll,FALSE);   
        }
        // else

        // {
        //     if (roll > 0.0f) roll -= 0.5f;
        //     else if (roll < 0.0f) roll += 0.5f;
        // }    
}

static float check_angle(float number, int flag)
{
    if(flag)
    {
        if(number >= 180.0f)
        {
            number= -179.0f;
        }            
        number += 1.0f;
    }
    else
    {
        if(number <= -179.0f)
        {
            number= 180.0f;
        }            
        number -= 1.0f;
    }
    return number;
}