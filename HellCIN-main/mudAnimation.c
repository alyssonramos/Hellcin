#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "animations.h"
#include "collision.h"

int main(void){

    const int screenWidth = 1600;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "HellCIN");

    SetTargetFPS(60);

    Texture2D mudRun = LoadTexture("./Assets/Mud Guard/Run.png");
    Texture2D mudAttack1 = LoadTexture("./Assets/Mud Guard/attack 1.png");
    Texture2D mudAttack2 = LoadTexture("./Assets/Mud Guard/attack 2.png");
    Texture2D mudDeath = LoadTexture("./Assets/Mud Guard/damaged and death.png");

    int mudRun_nSprites = 6;
    int mudRun_Width = mudRun.width;
    int mudRun_Heigth = mudRun.height/mudRun_nSprites;

    int mudAttack1_nSprites = 7;
    int mudAttack1_Width = mudAttack1.width;
    int mudAttack1_Heigth = mudAttack1.height/mudAttack1_nSprites;

    int mudAttack2_nSprites = 7;
    int mudAttack2_Width = mudAttack2.width;
    int mudAttack2_Heigth = mudAttack2.height/mudAttack2_nSprites;

    int mudDeath_nSprites = 8;
    int mudDeath_Width = mudDeath.width;
    int mudDeath_Heigth = mudDeath.height/mudDeath_nSprites;

    Vector2 origin = {0.0f, 0.0f};

    Rectangle mudRun_sourceRect = {0.0f, 0.0f, (float)mudRun_Width, (float)mudRun_Heigth};
    Rectangle mudRun_destRect = {screenWidth/2.0f - 82, screenHeight/2.0f - 46, mudRun_Width*2.0f, mudRun_Heigth*2.0f };

    Rectangle mudAttack1_sourceRect = {0.0f, 0.0f, (float)mudAttack1_Width, (float)mudAttack1_Heigth};
    Rectangle mudAttack1_destRect = {screenWidth/2.0f - 82, screenHeight/2.0f - 46, mudAttack1_Width*2.0f, mudAttack1_Heigth*2.0f };

    Rectangle mudAttack2_sourceRect = {0.0f, 0.0f, (float)mudAttack2_Width, (float)mudAttack2_Heigth};
    Rectangle mudAttack2_destRect = {screenWidth/2.0f - 82, screenHeight/2.0f - 46, mudAttack2_Width*2.0f, mudAttack2_Heigth*2.0f };

    Rectangle mudDeath_sourceRect = {0.0f, 0.0f, (float)mudDeath_Width, (float)mudDeath_Heigth};
    Rectangle mudDeath_destRect = {screenWidth/2.0f - 82, screenHeight/2.0f - 46, mudDeath_Width*2.0f, mudDeath_Heigth*2.0f };

    int rotation = 0;
    int mudRun_framecounter = 0;
    int mudRun_framespeed = 8;
    int mudRun_currentframe = 0;

    int mudAttack1_framecounter = 0;
    int mudAttack1_framespeed = 8;
    int mudAttack1_currentframe = 0;
    bool mudAttack1_active = false;

    int mudAttack2_framecounter = 0;
    int mudAttack2_framespeed = 8;
    int mudAttack2_currentframe = 0;
    bool mudAttack2_active = false;

    int mudDeath_framecounter = 0;
    int mudDeath_framespeed = 3;
    int mudDeath_currentframe = 0;
    bool mudDeath_active = false;
    bool IsMudDead = false;

    while(!WindowShouldClose()){

        mudRun_framecounter++;
        mudAttack1_framecounter++;
        mudAttack2_framecounter++;
        mudDeath_framecounter++;

        if(IsKeyDown(KEY_RIGHT) && !IsMudDead){

            mudRun_destRect.x +=4;
            
            if(mudRun_sourceRect.width < 0){
                mudRun_sourceRect.width = -1 * mudRun_sourceRect.width;
                mudAttack1_sourceRect.width = -1 * mudAttack1_sourceRect.width;
                mudAttack2_sourceRect.width = -1 * mudAttack2_sourceRect.width;
                mudDeath_sourceRect.width = -1 * mudDeath_sourceRect.width;
            }

            mudRun_sourceRect.y = runningAnimations(&mudRun_framecounter, &mudRun_framespeed, &mudRun_currentframe, mudRun_sourceRect.y, mudRun_Heigth, mudRun_nSprites);

        }
        if(IsKeyDown(KEY_LEFT) && !IsMudDead){
            
            mudRun_destRect.x -=4;

            if(mudRun_sourceRect.width > 0){
                mudRun_sourceRect.width = -1 * mudRun_sourceRect.width;
                mudAttack1_sourceRect.width = -1 * mudAttack1_sourceRect.width;
                mudAttack2_sourceRect.width = -1 * mudAttack2_sourceRect.width;
                mudDeath_sourceRect.width = -1 * mudDeath_sourceRect.width;
            }

            mudRun_sourceRect.y = runningAnimations(&mudRun_framecounter, &mudRun_framespeed, &mudRun_currentframe, mudRun_sourceRect.y, mudRun_Heigth, mudRun_nSprites);
        }
        if(IsKeyDown(KEY_DOWN) && !IsMudDead){
            mudRun_destRect.y +=4;

            mudRun_sourceRect.y = runningAnimations(&mudRun_framecounter, &mudRun_framespeed, &mudRun_currentframe, mudRun_sourceRect.y, mudRun_Heigth, mudRun_nSprites);
        }
        if(IsKeyDown(KEY_UP) && !IsMudDead){
            mudRun_destRect.y -=4;

            mudRun_sourceRect.y = runningAnimations(&mudRun_framecounter, &mudRun_framespeed, &mudRun_currentframe, mudRun_sourceRect.y, mudRun_Heigth, mudRun_nSprites);
        }

        if(IsKeyPressed(KEY_B) && !mudAttack1_active)            
            mudAttack1_active = true;

        if(mudAttack1_active){

            mudAttack1_destRect.x = mudRun_destRect.x;
            mudAttack1_destRect.y = mudRun_destRect.y;
            
            if(mudAttack1_framecounter >= (60/mudAttack1_framespeed)){
                mudAttack1_framecounter++;
                
                if(mudAttack1_framecounter>2){
                    mudAttack1_currentframe++;
                    
                    if(mudAttack1_currentframe >= mudAttack1_nSprites){
                        
                        mudAttack1_currentframe = 0;
                        mudAttack1_framecounter = 0;
                        mudAttack1_active = false;
                    
                    }
                    
                    mudAttack1_framecounter = 0;
                }    
            }  
            mudAttack1_sourceRect.y = (float)(mudAttack1_currentframe) * (float)(mudAttack1_Heigth);          
        }

        if(IsKeyPressed(KEY_N) && !mudAttack2_active)
            mudAttack2_active = true;

        if(mudAttack2_active){

            mudAttack2_destRect.x = mudRun_destRect.x;
            mudAttack2_destRect.y = mudRun_destRect.y;
            
            if(mudAttack2_framecounter >= (60/mudAttack2_framespeed)){
                mudAttack2_framecounter++;
                
                if(mudAttack2_framecounter>2){
                    mudAttack2_currentframe++;
                    
                    if(mudAttack2_currentframe >= mudAttack2_nSprites){
                        
                        mudAttack2_currentframe = 0;
                        mudAttack2_framecounter = 0;
                        mudAttack2_active = false;
                    
                    }
                    
                    mudAttack2_framecounter = 0;
                }    
            }  
            mudAttack2_sourceRect.y = (float)(mudAttack2_currentframe) * (float)(mudAttack2_Heigth);          
        }

        if(IsKeyPressed(KEY_M) && !mudDeath_active)
            mudDeath_active = true;

        if(mudDeath_active){
            
            mudDeath_destRect.x = mudRun_destRect.x;
            mudDeath_destRect.y = mudRun_destRect.y;

            if(mudDeath_framecounter >= (60/mudDeath_framespeed)){
                mudDeath_framecounter++;
                
                if(mudDeath_framecounter>2){
                    mudDeath_currentframe++;
                    
                    if(mudDeath_currentframe > 4){
                        
                        mudDeath_currentframe = 4;
                        mudDeath_active = false;
                        IsMudDead = true;
                    }
                    mudDeath_framecounter = 0;
                }    
            }  
            mudDeath_sourceRect.y = (float)(mudDeath_currentframe) * (float)(mudDeath_Heigth);          
        }


    mapBorders(&mudRun_destRect.x,&mudRun_destRect.y,mudRun_destRect.width,mudRun_destRect.height, 1600,800); 
    mapBorders(&mudAttack1_destRect.x,&mudAttack1_destRect.y,mudAttack1_destRect.width,mudAttack1_destRect.height, 1600,800);
    mapBorders(&mudAttack2_destRect.x,&mudAttack2_destRect.y,mudAttack2_destRect.width,mudAttack2_destRect.height, 1600,800);

        if(mudAttack1_active && !IsMudDead){
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawTexturePro(mudAttack1, mudAttack1_sourceRect, mudAttack1_destRect, origin, rotation, RAYWHITE);
            EndDrawing();
        }else if(mudAttack2_active && !IsMudDead){
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawTexturePro(mudAttack2, mudAttack2_sourceRect, mudAttack2_destRect, origin, rotation, RAYWHITE);
            EndDrawing();        
        }else if(mudDeath_active){
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawTexturePro(mudDeath, mudDeath_sourceRect, mudDeath_destRect, origin, rotation, RAYWHITE);
            EndDrawing(); 
        }else if(!IsMudDead){
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawTexturePro(mudRun, mudRun_sourceRect, mudRun_destRect, origin, rotation, RAYWHITE);            
            EndDrawing();  
        }else if(IsMudDead){
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawTexturePro(mudDeath, mudDeath_sourceRect, mudDeath_destRect, origin, rotation, RAYWHITE);
            EndDrawing();
        }
    }

    UnloadTexture(mudRun);
    UnloadTexture(mudAttack1);
    UnloadTexture(mudAttack2);
    UnloadTexture(mudDeath);

    return 0;
}