#include "collision.h"
#include "raylib.h"

//    Definição das funções de colisões do HELLCIN ~~ Rodrigo ;3

// Com base nos da posição x e y do retangulo do personagem, do comprimento e largura do retangulo do personagem, e do mapa, define as bordas
// do mapas(Pode precisar ser mudada na adição de inimigos) - Rodrigo
void mapBorders(float *rectanglePosX, float *rectanglePosY, float rectangleWidth, float rectangleHeight, int beginMapWidht, int beginMapHeight, int mapWidth, int mapHeight){

    if(*(rectanglePosX) + rectangleWidth >= mapWidth){
        (*(rectanglePosX)) = mapWidth - rectangleWidth;
    }else if(*(rectanglePosX) <= beginMapWidht){
        (*(rectanglePosX)) = beginMapWidht;
    }

    if(*(rectanglePosY) + rectangleHeight >= mapHeight){
        (*(rectanglePosY)) = mapHeight - rectangleHeight;
    }else if(*(rectanglePosY) <= beginMapHeight){
        (*(rectanglePosY)) = beginMapHeight;
    }
}
void structureCollision(Rectangle *playerRec, Rectangle *structureRec){

    if(CheckCollisionRecs((*playerRec),(*structureRec))){
        if(IsKeyDown(KEY_RIGHT)){
            (*playerRec).x -=4;
        }
        if(IsKeyDown(KEY_LEFT)){
            (*playerRec).x +=4;
        }
        if(IsKeyDown(KEY_DOWN)){
            (*playerRec).y -=4;
        }
        if(IsKeyDown(KEY_UP)){
            (*playerRec).y +=4;
        }
    }

}

Vector2 randomVector(int minX, int maxX, int minY,int maxY){
    Vector2 randVec = {((float)GetRandomValue(minX, maxX)), ((float)GetRandomValue(minY,maxY))};
    return randVec;
}