#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "raylib.h"
#include "animations.h"
#include "menu.h"
#include "collision.h"

#define MAX_FRAME_SPEED     15
#define MIN_FRAME_SPEED      1

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1600;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "raylib [texture] example - sprite anim");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    Texture2D scarfy = LoadTexture("./Assets/stormhead/idle.png");        // Texture loading

    Vector2 position = { 350.0f, 280.0f };
    //Rectangle frameRec = { 0.0f, 0.0f, (float)scarfy.height/5, (float)scarfy.width };
    Rectangle frameRec2 = { 0.0f, 0.0f,(float)scarfy.width, (float)scarfy.height };
    Rectangle scarfy_destRect = {screenWidth/2.0f - 82, screenHeight/2.0f - 46, scarfy.width*2.0f, scarfy.height*2.0f };
    int rotation = 0;
    Vector2 origin = {0.0f, 0.0f};
    int currentFrame = 0;
    
    int framesCounter = 0;
    int framesSpeed = 8;            // Number of spritesheet frames shown by second
    Vector2 enemiesVector[8] = {0};
    Rectangle colision_enemy[8];    
        
    for(int cnt2 = 0; cnt2 < 8; cnt2++){
        enemiesVector[cnt2] = randomVector(-700,700,-350,350);
        colision_enemy[cnt2].x =  enemiesVector[cnt2].x;
        colision_enemy[cnt2].y =  enemiesVector[cnt2].y;
        colision_enemy[cnt2].width = scarfy.width*2.0f;
        colision_enemy[cnt2].height =  scarfy.width*2.0f;
    }
    for(int cnt3 = 0; cnt3 < 8; cnt3++){
    printf("X[%i]= %.2f\n",cnt3, colision_enemy[cnt3].x);
    printf("Y[%i]= %.2f\n",cnt3, colision_enemy[cnt3].y);
    printf("WIDTH[%i]= %.2f\n",cnt3, colision_enemy[cnt3].width);
    printf("HEIGHT[%i]= %.2f\n",cnt3, colision_enemy[cnt3].height);
    }
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        framesCounter++;

        if (framesCounter >= (60/framesSpeed))
        {
            framesCounter = 0;
            currentFrame++;

            //if (currentFrame > 4) currentFrame = 0;

            //frameRec.x = (float)currentFrame*(float)scarfy.height/5;
            
        }
        frameRec2.y = (float)currentFrame*(float)scarfy.height/9;
        // Control frames speed
        if (IsKeyPressed(KEY_RIGHT)) framesSpeed++;
        else if (IsKeyPressed(KEY_LEFT)) framesSpeed--;

        if (framesSpeed > MAX_FRAME_SPEED) framesSpeed = MAX_FRAME_SPEED;
        else if (framesSpeed < MIN_FRAME_SPEED) framesSpeed = MIN_FRAME_SPEED;
        
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawTexture(scarfy, 15, 40, WHITE);
            //DrawRectangleLines(15, 40, scarfy.width, scarfy.height, LIME);
            //DrawRectangleLines(15 + (int)frameRec.y, 40 + (int)frameRec.x,(int)frameRec.height, (int)frameRec.width, RED);

            DrawText("FRAME SPEED: ", 165, 210, 10, DARKGRAY);
            DrawText(TextFormat("%02i FPS", framesSpeed), 575, 210, 10, DARKGRAY);
            DrawText("PRESS RIGHT/LEFT KEYS to CHANGE SPEED!", 290, 240, 10, DARKGRAY);

            for (int i = 0; i < MAX_FRAME_SPEED; i++)
            {
                if (i < framesSpeed) DrawRectangle(250 + 21*i, 205, 20, 20, RED);
                DrawRectangleLines(250 + 21*i, 205, 20, 20, MAROON);
            }

            DrawTexturePro(scarfy, frameRec2, scarfy_destRect, origin, rotation, RAYWHITE);  // Draw part of the texture

            DrawText("(c) Scarfy sprite by Eiden Marsal", screenWidth - 200, screenHeight - 20, 10, GRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(scarfy);       // Texture unloading

    CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}