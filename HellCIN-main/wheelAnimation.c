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

    Texture2D wheelRun = LoadTexture("./Assets/Bot Wheel/move with FX.png");
    Texture2D wheelCharge = LoadTexture("./Assets/Bot Wheel/charge.png");
    Texture2D wheelAttack = LoadTexture("./Assets/Bot Wheel/shoot with FX.png");
    Texture2D wheelGas = LoadTexture("./Assets/Bot Wheel/GAS dash with FX.png");
    Texture2D wheelDeath = LoadTexture("./Assets/Bot Wheel/death.png");

    int wheelRun_nSprites = 8;
    int wheelRun_Width = wheelRun.width;
    int wheelRun_Heigth = wheelRun.height/wheelRun_nSprites;

    int wheelCharge_nSprites = 4;
    int wheelCharge_Width = wheelCharge.width;
    int wheelCharge_Heigth = wheelCharge.height/wheelCharge_nSprites;

    int wheelAttack_nSprites = 4;
    int wheelAttack_Width = wheelAttack.width;
    int wheelAttack_Heigth = wheelAttack.height/wheelAttack_nSprites;

    int wheelGas_nSprites = 7;
    int wheelGas_Width = wheelGas.width;
    int wheelGas_Heigth = wheelGas.height/wheelGas_nSprites;

    int wheelDeath_nSprites = 6;
    int wheelDeath_Width = wheelDeath.width;
    int wheelDeath_Heigth = wheelDeath.height/wheelDeath_nSprites;

    Vector2 origin = {0.0f, 0.0f};
    Rectangle wheelRun_sourceRect = {0.0f, 0.0f, (float)wheelRun_Width, (float)wheelRun_Heigth};
    Rectangle wheelRun_destRect = {screenWidth/2.0f - 82, screenHeight/2.0f - 46, wheelRun_Width*2.0f, wheelRun_Heigth*2.0f };

    Rectangle wheelCharge_sourceRect = {0.0f, 0.0f, (float)wheelCharge_Width, (float)wheelCharge_Heigth};
    Rectangle wheelCharge_destRect = {screenWidth/2.0f - 82, screenHeight/2.0f - 46, wheelCharge_Width*2.0f, wheelCharge_Heigth*2.0f };

    Rectangle wheelAttack_sourceRect = {0.0f, 0.0f, (float)wheelAttack_Width, (float)wheelAttack_Heigth};
    Rectangle wheelAttack_destRect = {screenWidth/2.0f - 82, screenHeight/2.0f - 46, wheelAttack_Width*2.0f, wheelAttack_Heigth*2.0f };

    Rectangle wheelGas_sourceRect = {0.0f, 0.0f, (float)wheelGas_Width, (float)wheelGas_Heigth};
    Rectangle wheelGas_destRect = {screenWidth/2.0f - 82, screenHeight/2.0f - 46, wheelGas_Width*2.0f, wheelGas_Heigth*2.0f };

    Rectangle wheelDeath_sourceRect = {0.0f, 0.0f, (float)wheelDeath_Width, (float)wheelDeath_Heigth};
    Rectangle wheelDeath_destRect = {screenWidth/2.0f - 82, screenHeight/2.0f - 46, wheelDeath_Width*2.0f, wheelDeath_Heigth*2.0f };

    int rotation = 0;
    int wheelRun_framecounter = 0;
    int wheelRun_framespeed = 8;
    int wheelRun_currentframe = 0;

    int wheelCharge_framecounter = 0;
    int wheelCharge_framespeed = 8;
    int wheelCharge_currentframe = 0;
    bool wheelCharge_active = false;
    bool wheelAttack_active = false;

    int wheelAttack_framecounter = 0;
    int wheelAttack_framespeed = 10;
    int wheelAttack_currentframe = 0;

    int wheelGas_framecounter = 0;
    int wheelGas_framespeed = 15;
    int wheelGas_currentframe = 0;
    bool wheelGas_active = false;

    int wheelDeath_framecounter = 0;
    int wheelDeath_framespeed = 4;
    int wheelDeath_currentframe = 0;
    bool wheelDeath_active = false;
    bool IsWheelDead = false;
    
   while(!WindowShouldClose()){

        wheelRun_framecounter++;
        
        if(IsKeyDown(KEY_RIGHT) && !IsWheelDead){

            wheelRun_destRect.x +=4;

            if(wheelRun_sourceRect.width < 0){
                wheelRun_sourceRect.width = -1 * wheelRun_sourceRect.width;
                wheelCharge_sourceRect.width = -1 * wheelCharge_sourceRect.width;
                wheelAttack_sourceRect.width = -1 * wheelAttack_sourceRect.width;
                wheelGas_sourceRect.width = -1 * wheelGas_sourceRect.width;
            }

            wheelRun_sourceRect.y = runningAnimations(&wheelRun_framecounter, &wheelRun_framespeed, &wheelRun_currentframe, wheelRun_sourceRect.y, wheelRun_Heigth, wheelRun_nSprites);
        }
        if(IsKeyDown(KEY_LEFT) && !IsWheelDead){
            wheelRun_destRect.x -=4;

            if(wheelRun_sourceRect.width > 0){
                wheelRun_sourceRect.width = -1 * wheelRun_sourceRect.width;
                wheelCharge_sourceRect.width = -1 * wheelCharge_sourceRect.width;
                wheelAttack_sourceRect.width = -1 * wheelAttack_sourceRect.width;
                wheelGas_sourceRect.width = -1 * wheelGas_sourceRect.width;
            }

            wheelRun_sourceRect.y = runningAnimations(&wheelRun_framecounter, &wheelRun_framespeed, &wheelRun_currentframe, wheelRun_sourceRect.y, wheelRun_Heigth, wheelRun_nSprites);
        }
        if(IsKeyDown(KEY_DOWN) && !IsWheelDead){
            wheelRun_destRect.y +=4;

            wheelRun_sourceRect.y = runningAnimations(&wheelRun_framecounter, &wheelRun_framespeed, &wheelRun_currentframe, wheelRun_sourceRect.y, wheelRun_Heigth, wheelRun_nSprites);
        }
        if(IsKeyDown(KEY_UP) && !IsWheelDead){
            wheelRun_destRect.y -=4;

            wheelRun_sourceRect.y = runningAnimations(&wheelRun_framecounter, &wheelRun_framespeed, &wheelRun_currentframe, wheelRun_sourceRect.y, wheelRun_Heigth, wheelRun_nSprites);
        }
        
        if(IsKeyPressed(KEY_C) && !wheelCharge_active){
            
            wheelCharge_active = true;
        }
        
        if(wheelCharge_active){

            wheelCharge_destRect.x = wheelRun_destRect.x;
            wheelCharge_destRect.y = wheelRun_destRect.y;
            
            if(wheelCharge_framecounter >= (60/wheelCharge_framespeed)){
                wheelCharge_framecounter++;
                
                if(wheelCharge_framecounter>2){
                    wheelCharge_currentframe++;
                    
                    if(wheelCharge_currentframe >= 4){
                        
                        wheelCharge_currentframe = 0;
                        wheelCharge_active = false;
                        wheelAttack_active = true;
                    
                    }
                    
                    wheelCharge_framecounter = 0;
                }    
            }            
        }
        wheelCharge_sourceRect.y = (float)(wheelCharge_currentframe) * (float)(wheelCharge_Heigth);

        if(wheelAttack_active){

            wheelAttack_destRect.x = wheelRun_destRect.x;
            wheelAttack_destRect.y = wheelRun_destRect.y;
            
            if(wheelAttack_framecounter >= (60/wheelAttack_framespeed)){
                wheelAttack_framecounter++;
                
                if(wheelAttack_framecounter>2){
                    wheelAttack_currentframe++;
                    
                    if(wheelAttack_currentframe >= 4){
                        
                        wheelAttack_currentframe = 0;
                        wheelAttack_framecounter = 0;
                        wheelAttack_active = false;
                    
                    }
                    
                    wheelAttack_framecounter = 0;
                }    
            }            
        }
        wheelAttack_sourceRect.y = (float)(wheelAttack_currentframe) * (float)(wheelAttack_Heigth);


        if(IsKeyDown(KEY_G))
            wheelGas_active = true;

        if(wheelGas_active){

            wheelGas_destRect.x = wheelRun_destRect.x;
            wheelGas_destRect.y = wheelRun_destRect.y;

            if(wheelGas_framecounter >= (60/wheelGas_framespeed)){
                wheelGas_framecounter++;

                if(wheelGas_framecounter>2){
                    wheelGas_currentframe++;

                    if(wheelGas_currentframe >= wheelGas_nSprites){
                        wheelGas_sourceRect.width = -1 * wheelGas_sourceRect.width;
                        
                        wheelRun_destRect.x += wheelGas_destRect.width;
                        wheelGas_currentframe = 0;
                        wheelGas_framecounter = 0;
                        wheelGas_active = false;
                    }

                    wheelGas_framecounter = 0;
                }
            }
        }
        wheelGas_sourceRect.y = (float)(wheelGas_currentframe) * (float)(wheelGas_Heigth);

        if(IsKeyPressed(KEY_M))
            wheelDeath_active = true;
        
        if(wheelDeath_active){

            wheelDeath_destRect.x = wheelRun_destRect.x;
            wheelDeath_destRect.y = wheelRun_destRect.y;

            if(wheelDeath_framecounter >= (60/wheelDeath_framespeed)){
                wheelDeath_framecounter++;

                if(wheelDeath_framecounter>2){

                    wheelDeath_currentframe++;

                    if(wheelDeath_currentframe > wheelDeath_nSprites-1){

                        wheelDeath_currentframe = wheelDeath_nSprites-1;
                        wheelDeath_active = false;
                        IsWheelDead = true;
                    }

                    wheelDeath_framecounter = 0;

                }
            }
        }
        wheelDeath_sourceRect.y = (float)(wheelDeath_currentframe) * (float)(wheelDeath_Heigth);

        wheelGas_framecounter++;
        wheelCharge_framecounter++;
        wheelAttack_framecounter++;
        wheelDeath_framecounter++;

        mapBorders(&wheelRun_destRect.x,&wheelRun_destRect.y,wheelRun_destRect.width,wheelRun_destRect.height, 1600,800);
        mapBorders(&wheelGas_destRect.x,&wheelGas_destRect.y,wheelGas_destRect.width,wheelGas_destRect.height, 1600,800);
        mapBorders(&wheelCharge_destRect.x,&wheelCharge_destRect.y,wheelCharge_destRect.width,wheelCharge_destRect.height, 1600,800);
        mapBorders(&wheelAttack_destRect.x,&wheelAttack_destRect.y,wheelAttack_destRect.width,wheelAttack_destRect.height, 1600,800);


        if(wheelCharge_active && !IsWheelDead){
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawTexturePro(wheelCharge, wheelCharge_sourceRect, wheelCharge_destRect, origin, rotation, RAYWHITE);
            EndDrawing();          
        }else if(wheelAttack_active && !IsWheelDead){
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawTexturePro(wheelAttack, wheelAttack_sourceRect, wheelAttack_destRect, origin, rotation, RAYWHITE);
            EndDrawing();
        }else if(wheelGas_active && !IsWheelDead){
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawTexturePro(wheelGas, wheelGas_sourceRect, wheelGas_destRect, origin, rotation, RAYWHITE);
            EndDrawing();
        }else if(wheelDeath_active && !IsWheelDead){
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawTexturePro(wheelDeath, wheelDeath_sourceRect, wheelDeath_destRect, origin, rotation, RAYWHITE);
            EndDrawing();   
        }else if(!IsWheelDead){
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawTexturePro(wheelRun, wheelRun_sourceRect, wheelRun_destRect, origin, rotation, RAYWHITE); 
            EndDrawing();
        }else if(IsWheelDead){
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawTexturePro(wheelDeath, wheelDeath_sourceRect, wheelDeath_destRect, origin, rotation, RAYWHITE);
            EndDrawing();
        }

    }

    UnloadTexture(wheelCharge);
    UnloadTexture(wheelAttack);
    UnloadTexture(wheelRun);
    UnloadTexture(wheelGas);
    UnloadTexture(wheelDeath);

    return 0;
}