#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "animations.h"
#include "collision.h"


void enemyAttack(bool collision, int *frameCounter, int *currentFrame, int nSprites, int frameSpeed, float *sourceRecty, float height){
        if(collision){
            if((*frameCounter) >= (60/frameSpeed)){
                (*frameCounter)++;
                
                if((*frameCounter)>2){
                    (*currentFrame)++;
                    
                    if((*currentFrame) >= nSprites){
                        
                        (*currentFrame) = 0;
                        (*frameCounter) = 0;
                    
                    }
                    
                    (*frameCounter) = 0;
                }    
            }
        }
        (*sourceRecty) = (float)((*currentFrame)) * (float)(height);



}

void displaySanity(int *sanityLevel, bool heroCollision){
    DrawRectangle(20, 20, 400, 20, RED);
    DrawRectangle(20, 20, *sanityLevel, 20, DARKBLUE);
    DrawText("SANIDADE", 430, 20, 25, DARKGRAY);
    if(heroCollision)
        (*sanityLevel) -= 1;
}


int main(void){

    const int screenWidth = 1600;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "HellCIN");

    SetTargetFPS(60);

    Texture2D stormheadRun = LoadTexture("./Assets/stormhead/run3.png");
    Texture2D stormheadAttack = LoadTexture("./Assets/stormhead/attack.png");

    Texture2D mudGuard = LoadTexture("./Assets/Mud Guard/run.png");
    Texture2D mudGAttack = LoadTexture("./Assets/Mud Guard/attack 1.png");

    int stormheadRun_nSprites = 10;
    int stormheadRun_Width = stormheadRun.width;
    int stormheadRun_Heigth = stormheadRun.height/stormheadRun_nSprites;

    int stormheadAttack_nSprites = 21;
    int stormheadAttack_Width = stormheadAttack.width;
    int stormheadAttack_Heigth = stormheadAttack.height/stormheadAttack_nSprites;

    int mudGuardRun_nSprites = 6;
    int mudGuardRun_width = mudGuard.width;
    int mudGuardRun_height = mudGuard.height/mudGuardRun_nSprites;

    int mudGAttack_nSprites = 7;
    int mudGAttack_width = mudGAttack.width;
    int mudGAttack_height = mudGAttack.height/mudGAttack_nSprites;

    Vector2 origin = {0.0f, 0.0f};
    Rectangle stormheadRun_sourceRect = {0.0f, 0.0f, (float)stormheadRun_Width, (float)stormheadRun_Heigth};
    Rectangle stormheadRun_destRect = {screenWidth/2.0f, screenHeight/2.0f, stormheadRun_Width*2.0f, stormheadRun_Heigth*2.0f };

    Rectangle stormheadAttack_sourceRect = {0.0f, 0.0f, (float)stormheadAttack_Width, (float)stormheadAttack_Heigth};
    Rectangle stormheadAttack_destRect = {screenWidth/2.0f - 82, screenHeight/2.0f - 46, stormheadAttack_Width*2.0f, stormheadAttack_Heigth*2.0f };

    Rectangle mudGuardRun_sourceRect = {0.0f, 0.0f, (float)mudGuardRun_width, (float)mudGuardRun_height};
    Rectangle mudGuard_destRect = {screenWidth/2.0f - 82, screenHeight/2.0f - 46, mudGuardRun_width*3.0f, mudGuardRun_height*3.0f};

    Rectangle mudGAttack_sourceRect = {0.0f, 0.0f, (float)mudGAttack_width, (float)mudGAttack_height};
    Rectangle mudGAttack_destRect = {screenWidth/2.0f - 82, screenHeight/2.0f - 46, mudGAttack_width*3.0f, mudGAttack_height};


    int rotation = 0;
    int stormheadRun_framecounter = 0;
    int stormheadRun_framespeed = 8;
    int stormheadRun_currentframe = 0;

    int stormheadAttack_framecounter = 0;
    int stormheadAttack_framespeed = 8;
    int stormheadAttack_currentframe = 0;
    bool stormheadAttack_active = false;
    int stormheadAttack_count = 0;

    int mudGAttack_frameCounter = 0;
    int mudGAttack_framespeed = 8;
    int mudGAttack_currentframe = 0;

    int sanityLevel = 395;
    bool heroCollision;


    while(!WindowShouldClose()){

        heroCollision = CheckCollisionRecs(stormheadRun_destRect, mudGuard_destRect);
    
        stormheadRun_framecounter++;
        stormheadAttack_framecounter++;
        //stormheadDamaged_framecounter++;
        
        if(IsKeyDown(KEY_RIGHT)){
            stormheadRun_destRect.x +=4;

            if(stormheadRun_sourceRect.width < 0){
                stormheadRun_sourceRect.width = -1 * stormheadRun_sourceRect.width;
                stormheadAttack_sourceRect.width = -1 * stormheadAttack_sourceRect.width;
            }

            stormheadRun_sourceRect.y = runningAnimations(&stormheadRun_framecounter, &stormheadRun_framespeed, &stormheadRun_currentframe, stormheadRun_sourceRect.y, stormheadRun_Heigth, stormheadRun_nSprites);
        }
        if(IsKeyDown(KEY_LEFT)){
            stormheadRun_destRect.x -=4;

            if(stormheadRun_sourceRect.width > 0){
                stormheadRun_sourceRect.width = -1 * stormheadRun_sourceRect.width;
                stormheadAttack_sourceRect.width = -1 * stormheadAttack_sourceRect.width;
            }

            stormheadRun_sourceRect.y = runningAnimations(&stormheadRun_framecounter, &stormheadRun_framespeed, &stormheadRun_currentframe, stormheadRun_sourceRect.y, stormheadRun_Heigth, stormheadRun_nSprites);
        }
        if(IsKeyDown(KEY_DOWN)){
            stormheadRun_destRect.y +=4;

            stormheadRun_sourceRect.y = runningAnimations(&stormheadRun_framecounter, &stormheadRun_framespeed, &stormheadRun_currentframe, stormheadRun_sourceRect.y, stormheadRun_Heigth, stormheadRun_nSprites);
        }
        if(IsKeyDown(KEY_UP)){
            stormheadRun_destRect.y -=4;

            stormheadRun_sourceRect.y = runningAnimations(&stormheadRun_framecounter, &stormheadRun_framespeed, &stormheadRun_currentframe, stormheadRun_sourceRect.y, stormheadRun_Heigth, stormheadRun_nSprites);
        }

        if(IsKeyPressed(KEY_B) && !stormheadAttack_active)
           stormheadAttack_active = true;

        if(stormheadAttack_active){
            
            stormheadAttack_destRect.x = stormheadRun_destRect.x;
            stormheadAttack_destRect.y = stormheadRun_destRect.y;

            if(stormheadAttack_framecounter >= (60/stormheadAttack_framespeed)){
                stormheadAttack_framecounter++;
                
                if(stormheadAttack_framecounter>2){
                    stormheadAttack_currentframe++;
                    
                    if(stormheadAttack_currentframe >= 8){
                        
                        stormheadAttack_currentframe = 0;
                        stormheadAttack_active = false;
                        stormheadAttack_count++;
                    
                    }
                    
                    stormheadAttack_framecounter = 0;
                }  
               stormheadAttack_sourceRect.y = (float)(stormheadAttack_currentframe) * (float)(stormheadAttack_Heigth);    
            }
                
        } 
        
            mapBorders(&stormheadRun_destRect.x,&stormheadRun_destRect.y,stormheadRun_destRect.width,stormheadRun_destRect.height, 1600, 800);
            mapBorders(&stormheadAttack_destRect.x, &stormheadAttack_destRect.y, stormheadAttack_destRect.width, stormheadAttack_destRect.height, 1600, 800);

            if(stormheadAttack_active){
                BeginDrawing();
                ClearBackground(RAYWHITE);
                displaySanity(&sanityLevel, heroCollision);
                DrawTexturePro(mudGuard, mudGuardRun_sourceRect, mudGuard_destRect, origin, rotation, RAYWHITE);
                DrawTexturePro(stormheadAttack, stormheadAttack_sourceRect, stormheadAttack_destRect, origin, rotation, RAYWHITE);            
                EndDrawing();  
            }else{
                BeginDrawing();
                ClearBackground(RAYWHITE);
                displaySanity(&sanityLevel, heroCollision);
                //bool collision, int *frameCounter, int *currentFrame, int nSprites, int frameSpeed, float *sourceRecty, float height
                enemyAttack(heroCollision, &mudGAttack_frameCounter, &mudGAttack_currentframe, mudGAttack_nSprites, mudGAttack_framespeed, &mudGAttack_sourceRect.y, mudGAttack_height);
                //DrawRectangle(21, 205, 50, 20, RED);
                DrawTexturePro(mudGuard, mudGuardRun_sourceRect, mudGuard_destRect, origin, rotation, RAYWHITE);
                DrawTexturePro(stormheadRun, stormheadRun_sourceRect, stormheadRun_destRect, origin, rotation, RAYWHITE);            
                EndDrawing(); 
            }
    }

    UnloadTexture(stormheadRun);
    UnloadTexture(stormheadAttack);
    UnloadTexture(mudGuard);
    UnloadTexture(mudGAttack);

    return 0;
}