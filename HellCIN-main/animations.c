#include "animations.h"
#include <raylib.h>

//    Definição das funções de animações do HELLCIN ~~ Rodrigo ;3

// De acordo com os parametros de contador de frames (para só tocar certas animações a cada certo intervalo), a velocidade da passagem de frames
// e o frame atual(esse precisa ser ponteiro para ter acesso a essa variavel de fora da animação), sourceValue(valor de passagem pra outros frames)
// de animação) e measureFrame(tamanho dos frames de animação) - Rodrigo

float runningAnimations(int *frameCounter, int *frameSpeed, int *currentFrame, float sourceValue, int measureFrame, int nSprites){
    if(*(frameCounter) >= (60/(*(frameSpeed)))){
        *(frameCounter) = 0;
        (*(currentFrame)) += 1;
        if(*(currentFrame) > nSprites)  
            *(currentFrame) = 0;
        sourceValue = (float)(*(currentFrame)) * (float)measureFrame;
    }
    return sourceValue;
}

void drawingStatusAnimations(bool statusAttack, bool statusDeath, bool statusDeathRun, Texture2D *textureRun, Texture2D *textureAttack, Texture2D *textureDeath, Rectangle *recRun, Rectangle *recAttack, Rectangle *recDeath, Rectangle *recRunDest, Rectangle *recAttackDest, Rectangle *recDeathDest, Vector2 *origin, int rotation){
    if(statusAttack && !statusDeath){

        DrawTexturePro(*textureAttack,*recAttack, *recAttackDest, *origin, rotation, RAYWHITE); 
            
    }else if(statusAttack){
                
        DrawTexturePro(*textureDeath, *recDeath, *recDeathDest, *origin, rotation, RAYWHITE);            

            
    }else if(statusDeathRun){

        DrawTexturePro(*textureDeath, *recDeath, *recDeathDest, *origin, rotation, RAYWHITE);
    
    }else if(!statusDeath){      

        DrawTexturePro(*textureRun, *recRun, *recRunDest, *origin, rotation, RAYWHITE);            
    
                
    }else if(statusDeath){
            
        DrawTexturePro(*textureDeath, *recDeath, *recDeathDest, *origin, rotation, RAYWHITE);            

    }
}

void attackAndDeath(Rectangle *sourceRectAD ,Rectangle *recDestAD, Rectangle *recDestRun, int *frameCounter, int *currentFrame, int *frameSpeed, int textAnimation, int *measureFrame, bool *status){

    recDestAD[0].x = recDestRun[0].x;
    recDestAD[0].y = recDestRun[0].y;
            
    if((*frameCounter) >= (60/(*frameSpeed))){
        (*frameCounter) += 1;
                
        if((*(frameCounter)) > 2){
            (*currentFrame) += 1;
                    
            if(*(currentFrame) >= textAnimation){
                        
                (*currentFrame) = 0;
                *status = false;   
            }
                    
            (*frameCounter) = 0;
        }  
        (*sourceRectAD).y = (float)((*currentFrame)) * (float)((*measureFrame));    
    }
}