#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "animations.h"
#include "collision.h"
#include "menu.h"

int main(void){

    int flagInicio = 0;

    const int screenWidth = 1600;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "HELLCIN");

    SetTargetFPS(60);

    Texture2D fireTexture = LoadTexture("./Assets/fogo.png");

    Texture2D memeTexture = LoadTexture("./Assets/Mud Guard/Run.png");

    Texture2D enter_button = LoadTexture("./Assets/enter.png");

    int nSprites = 6;

    int frameWidth = memeTexture.width/2;
    int frameHeight = memeTexture.height/nSprites;


    Vector2 vectorImage = {630,200};

    Rectangle sourceRect = {0.0f, 0.0f, (float)frameWidth, (float)frameHeight};  
    Rectangle sourceRectEnemies[1];
    for(int contadorInimigos = 0; contadorInimigos < 2;contadorInimigos++){
        sourceRectEnemies[contadorInimigos].x = 0.0;
        sourceRectEnemies[contadorInimigos].y = 0.0;
        sourceRectEnemies[contadorInimigos].width =  (float)frameWidth;
        sourceRectEnemies[contadorInimigos].height = (float)frameHeight;
    }
    Rectangle destRect = {screenWidth/2.0f - 82, screenHeight/2.0f - 46, frameWidth*2.0f, frameHeight*2.0f };
    Camera2D camera = {0};

    camera.target = (Vector2){destRect.x + 20.0f, destRect.y + 20.0f};
    camera.offset = (Vector2){screenWidth/2.0f,screenHeight/2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    Vector2 origin = {0.0f, 0.0f};

    //Rectangle sourceRectEnemy = {0.0f, 0.0f, (float)frameWidth, (float)frameHeight}; 
    Rectangle destRectEnemy = { screenWidth/2.0f, screenHeight/2.0f, frameWidth*2.25f, frameHeight*2.25f };

    int rotation = 0;


    int currentframe = 0;
    int framecounter = 0;
    int framespeed = 8;

    int currentframe2 = 0;
    int framecounter2 = 0;
    int framespeed2 = 8;

    while(!WindowShouldClose()){    

        if(IsKeyDown(KEY_ENTER)){
                flagInicio = 1;
        }else if(IsKeyDown(KEY_F11)){
                ToggleFullscreen();
        }else if(IsKeyDown(KEY_ESCAPE)){
            UnloadTexture(fireTexture);
            UnloadTexture(memeTexture);
            UnloadTexture(enter_button);
            CloseWindow();
            exit(1);

        }

        framecounter++;
        framecounter2++;
        

        if(IsKeyDown(KEY_RIGHT)){

            destRect.x += 4.0;

            if(sourceRect.width < 0)
                sourceRect.width = -1 * sourceRect.width;

            sourceRect.y = runningAnimations(&framecounter,&framespeed,&currentframe,sourceRect.y,frameHeight, nSprites);

        }if(IsKeyDown(KEY_LEFT)){

            destRect.x -= 4.0;

            if(sourceRect.width > 0)
                sourceRect.width = -1 * sourceRect.width;
            
            sourceRectEnemies[0].y = runningAnimations(&framecounter2,&framespeed2,&currentframe2,sourceRectEnemies[0].y,frameHeight,nSprites);

            sourceRect.y = runningAnimations(&framecounter,&framespeed,&currentframe,sourceRect.y,frameHeight, nSprites);
            
        }if(IsKeyDown(KEY_UP)){

            destRect.y -= 4.0;
            sourceRect.y = runningAnimations(&framecounter,&framespeed,&currentframe,sourceRect.y,frameHeight, nSprites);

        }if(IsKeyDown(KEY_DOWN)){

            destRect.y += 4.0;
            sourceRect.y = runningAnimations(&framecounter,&framespeed,&currentframe,sourceRect.y,frameHeight, nSprites);

        }

        mapBorders(&destRect.x,&destRect.y,destRect.width,destRect.height, 1600,800);


        camera.target = (Vector2) {destRect.x + 20.0f, destRect.y + 20.0f};

        if(IsKeyDown(KEY_Z)){
            if(camera.zoom > 5.0){
                camera.zoom = 5.0;
            }
            camera.zoom +=0.25;
        }else if(IsKeyDown(KEY_X)){
            if(camera.zoom < 1.0){
                camera.zoom = 1.0;
            }
            camera.zoom -=0.25;
        }


        if(flagInicio){

            BeginDrawing();
                
                BeginMode2D(camera);
                    ClearBackground(RAYWHITE);
                    DrawRectangle((int)destRect.x,(int)destRect.y, (int)destRect.width, (int)destRect.height, RED);
                    DrawRectangleV(vectorImage, (Vector2) {50.0f, 50.0f}, BLUE);
                    DrawTexturePro(memeTexture, sourceRect, destRect, origin, (float)rotation, WHITE);
                    DrawTexturePro(memeTexture, sourceRectEnemies[0], destRectEnemy, origin, (float)rotation, WHITE);
                    DrawText("Use as setas para se mover", 400, 150, 50, BLACK);
                EndMode2D();

                
            EndDrawing(); 

        }else{
            IniciarMenu ();
        }

    
    }
    return 0;
}
