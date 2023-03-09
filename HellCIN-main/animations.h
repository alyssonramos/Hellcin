#ifndef _ANIMATIONS_H
#define _ANIMATIONS_H

#include "raylib.h"

float runningAnimations(int *frameCounter, int *frameSpeed, int *currentFrame, float sourceValue, int measureFrame, int nSprites);
void drawingStatusAnimations(bool statusAttack, bool statusDeath, bool statusDeathRun, Texture2D *textureRun, Texture2D *textureAttack, Texture2D *textureDeath, Rectangle *recRun, Rectangle *recAttack, Rectangle *recDeath, Rectangle *recRunDest, Rectangle *recAttackDest, Rectangle *recDeathDest, Vector2 *origin, int rotation);
void attackAndDeath(Rectangle *sourceRectAD ,Rectangle *recDestAD, Rectangle *recDestRun, int *frameCounter, int *currentFrame, int *frameSpeed, int textAnimation, int *measureFrame, bool *status);

#endif
