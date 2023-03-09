#include "menu.h"
#include <raylib.h>

void IniciarMenu (){
    const int screenWidth = 1600;
    const int screenHeight = 800;

    Image menu_background = LoadImage("./Assets/Computers1.png");

    Texture2D  menu_backgroundT = LoadTextureFromImage(menu_background);

    UnloadImage (menu_background);

    Texture2D menu_foguinho = LoadTexture ("./Assets/fogo.png");
    Texture2D menu_enter = LoadTexture ("./Assets/enter.png");

    Vector2 position = { (float)(screenWidth/2 - menu_background.width/2), (float)(screenHeight/2 - menu_background.height/2 - 20) };

    SetTargetFPS(60);               
    
    while (IsKeyUp(KEY_ENTER)){
        BeginDrawing();
                
            DrawTextureV(menu_backgroundT, position, WHITE);

            DrawTextureV(menu_foguinho, (Vector2) {660,200}, WHITE);

            DrawTextureEx(menu_enter, (Vector2) {650,520}, 0, 2, WHITE); 

                //DrawTextureV(menu_enter, (Vector2) {690, 520}, WHITE);
                
            DrawText("HellCIN", 670, 100, 70, WHITE);

            DrawText("welcome to:", 710, 60, 30, ORANGE);

        EndDrawing();
    }

    UnloadTexture (menu_foguinho);
    UnloadTexture (menu_enter);
    
    return;     
}