#ifndef _COLLISION_H
#define _COLLISION_H

#include "raylib.h"

void mapBorders(float *rectanglePosX, float *rectanglePosY, float rectangleWidth, float rectangleHeight, int beginMapWidht, int beginMapHeight, int mapWidth, int mapHeight);
void structureCollision(Rectangle *playerRec, Rectangle *structureRec);
Vector2 randomVector(int minX, int maxX, int minY,int maxY);
#endif