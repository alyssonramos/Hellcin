#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "animations.h"
#include "menu.h"
#include "collision.h"

typedef struct Ataque{

    int attackNumber;
    float attackDamage;
    int attackLevel;

}Ataque;

typedef struct Protagonista{

    float sanityLevel;
    Rectangle sourceRec;
    Rectangle destRec;
    Ataque attacks[3];
    int healItemnumber;
    long int abstractions;

}Protagonista;

typedef struct Enemies{

    float hp;
    Rectangle destRec;
    Ataque attack[2];
    int weakness;
    bool death;

}Enemies;

int main(void){
    //Definição de variaveis de tela e jogo
    const int screenWidth = 1600;
    const int screenHeight = 800;

    bool beginFlag = false;
    bool flagFirstFase = false;
    bool flagSecondFase = false;
    bool flagFinal = false;
    bool flagEndGame = false;

    InitWindow(screenWidth, screenHeight, "HellCIN");
    InitAudioDevice();
    
    Image tela2_background = LoadImage("./Assets/Grid.png");
    Texture2D  tela2_backgroundT = LoadTextureFromImage(tela2_background);
    UnloadImage (tela2_background);
    Vector2 position = { (float)(screenWidth/2 - tela2_background.width/2), (float)(screenHeight/2 - tela2_background.height/2 - 20)};

    Sound initialSound = LoadSound("./Assets/Sounds/soundInitial.wav");
    Texture2D firstFase = LoadTexture("./Assets/Maps/Mapa.png");
    Texture2D endgame = LoadTexture("./Assets/Computers II.png");
    Texture2D telafinal = LoadTexture("./Assets/Office I.png");
    Texture2D secondFase = LoadTexture("./Assets/Maps/mapa2.png");
    Vector2 positionMaps = { (float)(screenWidth/2 - firstFase.width/2), (float)(screenHeight/2 - firstFase.height/2) };
    Vector2 origin = {0.0f, 0.0f};
    
    //Definição da textura de inimigos/protagonista
    Texture2D mudRun = LoadTexture("./Assets/Mud Guard/Run.png");
    Texture2D mudAttack1 = LoadTexture("./Assets/Mud Guard/attack 1.png");
    Texture2D mudAttack2 = LoadTexture("./Assets/Mud Guard/attack 2.png");
    Texture2D mudDeath = LoadTexture("./Assets/Mud Guard/damaged and death.png");

    Texture2D stormheadRun = LoadTexture("./Assets/stormhead/run3.png");
    Texture2D stormheadAttack = LoadTexture("./Assets/stormhead/attack.png");

    Texture2D wheelRun = LoadTexture("./Assets/Bot Wheel/move with FX.png");
    Texture2D wheelCharge = LoadTexture("./Assets/Bot Wheel/charge.png");
    Texture2D wheelAttack = LoadTexture("./Assets/Bot Wheel/shoot with FX.png");
    Texture2D wheelGas = LoadTexture("./Assets/Bot Wheel/GAS dash with FX.png");
    Texture2D wheelDeath = LoadTexture("./Assets/Bot Wheel/death.png");
    
    Texture2D barlife = LoadTexture("./Assets/BarLife/VIDA_10.png");
    
    Sound musicaF1 = LoadSound ("Assets/Sounds/musicaF1.mp3");
    Sound musicahist = LoadSound ("Assets/Sounds/musicahist.mp3");
    PlaySound (musicahist);

    Vector2 enemiesVector[8] = {0};
    Vector2 enemiesVector2[8] = {0};

    for(int cnt2 = 0; cnt2 < 8; cnt2++)
        enemiesVector[cnt2] = randomVector(0,1400,0,700);

    for(int cnt2 = 0; cnt2 < 8; cnt2++)
        enemiesVector2[cnt2] = randomVector(0,1400,0,700);




    //Variaveis de animação para inimigos/protagonista
    int mudRun_nSprites = 6;
    int mudRun_Width = mudRun.width;
    int mudRun_Heigth = mudRun.height/mudRun_nSprites;
    /**
    int mudAttack1_nSprites = 7;
    int mudAttack1_Width = mudAttack1.width;
    int mudAttack1_Heigth = mudAttack1.height/mudAttack1_nSprites;

    int mudAttack2_nSprites = 7;
    int mudAttack2_Width = mudAttack2.width;
    int mudAttack2_Heigth = mudAttack2.height/mudAttack2_nSprites;

    int mudDeath_nSprites = 8;
    int mudDeath_Width = mudDeath.width;
    int mudDeath_Heigth = mudDeath.height/mudDeath_nSprites;
    */
    int barlife_Width = barlife.width;
    int barlife_Heigth = barlife.height;
    
    Rectangle mudRun_sourceRect = {0.0f, 0.0f, (float)mudRun_Width, (float)mudRun_Heigth};
    Enemies mudEnemy[8];

    for(int cnt1 = 0; cnt1 < 8; cnt1++){

        //Dados base inimigos finais
        mudEnemy[cnt1].hp = 500.0f;
        mudEnemy[cnt1].weakness = 3;
        mudEnemy[cnt1].death = false;

        //Ataques inimigos finais
        mudEnemy[cnt1].attack[0].attackNumber = 1;
        mudEnemy[cnt1].attack[0].attackLevel = 12;
        mudEnemy[cnt1].attack[0].attackDamage = ((mudEnemy[cnt1].attack[0].attackNumber * mudEnemy[cnt1].attack[0].attackLevel * 10) + GetRandomValue(1,50)) / 2.0f;

        //Posição inimigos iniciais
        mudEnemy[cnt1].destRec.x =  enemiesVector2[cnt1].x;
        mudEnemy[cnt1].destRec.y =  enemiesVector2[cnt1].y;
        mudEnemy[cnt1].destRec.width = mudRun_Width*2.0f;
        mudEnemy[cnt1].destRec.height =  mudRun_Heigth*2.0f;
    }

    /*
    Rectangle mudAttack1_sourceRect = {0.0f, 0.0f, (float)mudAttack1_Width, (float)mudAttack1_Heigth};
    Rectangle mudAttack1_destRect = {screenWidth/2.0f - 82, screenHeight/2.0f - 46, mudAttack1_Width*2.0f, mudAttack1_Heigth*2.0f };

    Rectangle mudAttack2_sourceRect = {0.0f, 0.0f, (float)mudAttack2_Width, (float)mudAttack2_Heigth};
    Rectangle mudAttack2_destRect = {screenWidth/2.0f - 82, screenHeight/2.0f - 46, mudAttack2_Width*2.0f, mudAttack2_Heigth*2.0f };

    Rectangle mudDeath_sourceRect = {0.0f, 0.0f, (float)mudDeath_Width, (float)mudDeath_Heigth};
    Rectangle mudDeath_destRect = {screenWidth/2.0f - 82, screenHeight/2.0f - 46, mudDeath_Width*2.0f, mudDeath_Heigth*2.0f };
    */

    int rotation = 0;
    int mudRun_framecounter = 0;
    int mudRun_framespeed = 8;
    int mudRun_currentframe = 0;

    /*
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
    */

    int wheelRun_nSprites = 8;
    int wheelRun_Width = wheelRun.width;
    int wheelRun_Heigth = wheelRun.height/wheelRun_nSprites;

    /*
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
    */

   //Inimigos Primeira fase
    Rectangle wheelRun_sourceRect = {0.0f, 0.0f, (float)wheelRun_Width, (float)wheelRun_Heigth};
    Enemies wheelEnemy[8];

    for(int cnt1 = 0; cnt1 < 8; cnt1++){

        //Dados base inimigos iniciais
        wheelEnemy[cnt1].hp = 250.0f;
        wheelEnemy[cnt1].weakness = 1;
        wheelEnemy[cnt1].death = false;

        //Ataques inimigos iniciais
        wheelEnemy[cnt1].attack[0].attackNumber = 1;
        wheelEnemy[cnt1].attack[0].attackLevel = 5;
        wheelEnemy[cnt1].attack[0].attackDamage = ((wheelEnemy[cnt1].attack[0].attackNumber * wheelEnemy[cnt1].attack[0].attackLevel * 10) + GetRandomValue(1,50)) / 2.0f;

        //Posição inimigos iniciais
        wheelEnemy[cnt1].destRec.x =  enemiesVector[cnt1].x;
        wheelEnemy[cnt1].destRec.y =  enemiesVector[cnt1].y;
        wheelEnemy[cnt1].destRec.width = wheelRun_Width*2.0f;
        wheelEnemy[cnt1].destRec.height =  wheelRun_Heigth*2.0f;
    }

    /*
    Rectangle wheelCharge_sourceRect = {0.0f, 0.0f, (float)wheelCharge_Width, (float)wheelCharge_Heigth};
    Rectangle wheelCharge_destRect = {screenWidth/2.0f - 82, screenHeight/2.0f - 46, wheelRun_Width*2.0f, wheelRun_Heigth*2.0f };


    Rectangle wheelAttack_sourceRect = {0.0f, 0.0f, (float)wheelAttack_Width, (float)wheelAttack_Heigth};
    Rectangle wheelAttack_destRect = {screenWidth/2.0f - 82, screenHeight/2.0f - 46, wheelAttack_Width*2.0f, wheelAttack_Heigth*2.0f };

    Rectangle wheelGas_sourceRect = {0.0f, 0.0f, (float)wheelGas_Width, (float)wheelGas_Heigth};
    Rectangle wheelGas_destRect = {screenWidth/2.0f - 82, screenHeight/2.0f - 46, wheelGas_Width*2.0f, wheelGas_Heigth*2.0f };

    Rectangle wheelDeath_sourceRect = {0.0f, 0.0f, (float)wheelDeath_Width, (float)wheelDeath_Heigth};
    Rectangle wheelDeath_destRect = {screenWidth/2.0f - 82, screenHeight/2.0f - 46, wheelDeath_Width*2.0f, wheelDeath_Heigth*2.0f };
    */

    int wheelRun_framecounter = 0;
    int wheelRun_framespeed = 8;
    int wheelRun_currentframe = 0;
    /*
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
    */

    int stormheadRun_nSprites = 10;
    int stormheadRun_Width = stormheadRun.width - 80;
    int stormheadRun_Heigth = stormheadRun.height/stormheadRun_nSprites;

    int stormheadAttack_nSprites = 21;
    
    /*
    int stormheadAttack_Width = stormheadAttack.width;
    int stormheadAttack_Heigth = stormheadAttack.height/stormheadAttack_nSprites;
    */
    
    //Dados base do nosso protagonista
    Protagonista personagemPrincipal;

    personagemPrincipal.sanityLevel = 100.0f;
    personagemPrincipal.healItemnumber = 0;
    personagemPrincipal.abstractions = 0;

    Rectangle sourceRec = {40.0f, 0.0f, (float)stormheadRun_Width, (float)stormheadRun_Heigth};
    personagemPrincipal.sourceRec = sourceRec;
    Rectangle destRec = {screenWidth/2.0f, screenHeight/2.0f, stormheadRun_Width*1.0f, stormheadRun_Heigth*1.0f };
    personagemPrincipal.destRec = destRec;

    
    //Ataques iniciais do protagonista
    personagemPrincipal.attacks[0].attackNumber = 1;
    personagemPrincipal.attacks[0].attackLevel = 1;
    int attackOneRng = GetRandomValue(1,10);
    personagemPrincipal.attacks[0].attackDamage = ((personagemPrincipal.attacks[0].attackNumber * personagemPrincipal.attacks[0].attackLevel * 10) + attackOneRng) / 5.0f;

    personagemPrincipal.attacks[1].attackNumber = 2;
    personagemPrincipal.attacks[1].attackLevel = 1;
    int attackTwoRng = GetRandomValue(1,10);
    personagemPrincipal.attacks[1].attackDamage = ((personagemPrincipal.attacks[1].attackNumber * personagemPrincipal.attacks[1].attackLevel * 10) + attackTwoRng) / 5.0f;

    personagemPrincipal.attacks[2].attackNumber = 3;
    personagemPrincipal.attacks[2].attackLevel = 1;
    int attackThreeRng = GetRandomValue(1,10);
    personagemPrincipal.attacks[2].attackDamage = ((personagemPrincipal.attacks[2].attackNumber * personagemPrincipal.attacks[2].attackLevel * 10) + attackThreeRng) / 5.0f;
    
    /*
    Rectangle stormheadAttack_sourceRect = {0.0f, 0.0f, (float)stormheadAttack_Width, (float)stormheadAttack_Heigth};
    Rectangle stormheadAttack_destRect = {screenWidth/2.0f - 82, screenHeight/2.0f - 46, stormheadAttack_Width*2.0f, stormheadAttack_Heigth*2.0f };
    */
    Camera2D cameraPersonagem = {0};
    cameraPersonagem.target = (Vector2){personagemPrincipal.destRec.x + 55.0f, personagemPrincipal.destRec.y + 25.0f};
    cameraPersonagem.offset = (Vector2){screenWidth/2.0f,screenHeight/2.0f};
    cameraPersonagem.rotation = 0.0f;
    cameraPersonagem.zoom = 1.0f;    

    int stormheadRun_framecounter = 0;
    int stormheadRun_framespeed = 8;
    int stormheadRun_currentframe = 0;

    /*
    int stormheadAttack_framecounter = 0;
    int stormheadAttack_framespeed = 8;
    int stormheadAttack_currentframe = 0;
    bool stormheadAttack_active = false;
    int stormheadAttack_count = 0;
    */

    Rectangle barlife_sourceRect = {0.0f, 0.0f, (float)barlife_Width, (float)barlife_Heigth};
    Rectangle barlife_destRect[8];

    for(int cnt4 = 0; cnt4 < 8; cnt4++){
        barlife_destRect[cnt4].x = wheelEnemy[cnt4].destRec.x - 30.0f;
        barlife_destRect[cnt4].y =  wheelEnemy[cnt4].destRec.y - 20.0f;
        barlife_destRect[cnt4].width = barlife_Width/4;
        barlife_destRect[cnt4].height = barlife_Heigth/4;
    }


    Rectangle retanguloPaulo = {1394.0f, 38.0f, 38.0f, 126.0f};
    Rectangle retanguloPauloConversa = {1344.0f, 38.0f, 100.0f, 140.0f};
    Rectangle dialogoPaulo = {personagemPrincipal.destRec.x, personagemPrincipal.destRec.y + 25.0f, 450.0f, 60.0f};

    bool flagDialogo = false, flagLoja = false, flagLoja2 = false;
    int escolhaUpgrade = 0, contadorMovimentacao = 0;
    long long int contadorTempo = 0;    

    SetTargetFPS(60);

    //Inicio do jogo somente se o dispositivo de som e audio tiverem sido iniciados
    if(IsAudioDeviceReady() == true && IsWindowReady() == true){
        while(!WindowShouldClose()){

            //Teclas iniciais(as de fase serão tiradas na versão final)
            if(IsKeyDown(KEY_ENTER)){

                    beginFlag = true;

            }else if(IsKeyDown(KEY_F11)){

                    ToggleFullscreen();

            }else if(IsKeyDown(KEY_ESCAPE)){
                UnloadSound(initialSound);
                UnloadTexture(mudAttack1);
                UnloadTexture(mudAttack2);
                UnloadTexture(mudDeath);
                UnloadTexture(mudRun);
                UnloadTexture(stormheadAttack);
                UnloadTexture(stormheadRun);
                UnloadTexture(wheelAttack);
                UnloadTexture(wheelCharge);
                UnloadTexture(wheelDeath);
                UnloadTexture(wheelGas);
                UnloadTexture(wheelRun);
                UnloadTexture(firstFase);
                UnloadTexture(secondFase);
                UnloadTexture (tela2_backgroundT);
                UnloadSound (musicaF1);
                UnloadSound (musicahist);
                CloseWindow();
                exit(1);
            }else if(IsKeyDown(KEY_I) && flagFirstFase == false){
                flagFirstFase = true;
                PlaySound(initialSound);
            }else if(IsKeyDown(KEY_A)){
                flagSecondFase = true;
                PlaySound(initialSound);
            }else if(IsKeyDown(KEY_KP_0)){
                flagFinal = true;
                PlaySound(initialSound);
            }else if(IsKeyDown(KEY_K)){
                flagEndGame = true;
                PlaySound(initialSound);
            }


            stormheadRun_framecounter++;
            //stormheadAttack_framecounter++;

            contadorTempo++;


           //Teclas de movimentação 
            if(IsKeyDown(KEY_RIGHT)){
                personagemPrincipal.destRec.x +=4;      

                if(personagemPrincipal.sourceRec.width < 0){
                    personagemPrincipal.sourceRec.width = -1 * personagemPrincipal.sourceRec.width;
                    personagemPrincipal.sourceRec.width = -1 * personagemPrincipal.sourceRec.width;
                }

                personagemPrincipal.sourceRec.y = runningAnimations(&stormheadRun_framecounter, &stormheadRun_framespeed, &stormheadRun_currentframe, personagemPrincipal.sourceRec.y, stormheadRun_Heigth, stormheadRun_nSprites);
            }
            if(IsKeyDown(KEY_LEFT)){
                personagemPrincipal.destRec.x -=4;

                if(personagemPrincipal.sourceRec.width > 0){
                    personagemPrincipal.sourceRec.width = -1 * personagemPrincipal.sourceRec.width;
                    personagemPrincipal.sourceRec.width = -1 * personagemPrincipal.sourceRec.width;
                }

                personagemPrincipal.sourceRec.y = runningAnimations(&stormheadRun_framecounter, &stormheadRun_framespeed, &stormheadRun_currentframe, personagemPrincipal.sourceRec.y, stormheadRun_Heigth, stormheadRun_nSprites);
            }
            if(IsKeyDown(KEY_DOWN)){
                personagemPrincipal.destRec.y +=4;

                personagemPrincipal.sourceRec.y = runningAnimations(&stormheadRun_framecounter, &stormheadRun_framespeed, &stormheadRun_currentframe, personagemPrincipal.sourceRec.y, stormheadRun_Heigth, stormheadRun_nSprites);
            }
            if(IsKeyDown(KEY_UP)){
                personagemPrincipal.destRec.y -=4;

                personagemPrincipal.sourceRec.y = runningAnimations(&stormheadRun_framecounter, &stormheadRun_framespeed, &stormheadRun_currentframe, personagemPrincipal.sourceRec.y, stormheadRun_Heigth, stormheadRun_nSprites);
            }


            structureCollision(&personagemPrincipal.destRec,&retanguloPaulo);

            for(int cnt5 = 0; cnt5 < 8; cnt5++){
                if(CheckCollisionRecs(personagemPrincipal.destRec,wheelEnemy[cnt5].destRec)){
                    //Muda pra tela de batalha
                    DrawText("HEY LISTEN", ((int) personagemPrincipal.destRec.x - 30.0f), ((int) personagemPrincipal.destRec.y + 50.0f), 8, WHITE);
                }
            }

            //Centralização da camera
            cameraPersonagem.target = (Vector2) {personagemPrincipal.destRec.x + 25.0f, personagemPrincipal.destRec.y + 25.0f};

            dialogoPaulo.x = personagemPrincipal.destRec.x - 200.0f;
            dialogoPaulo.y = personagemPrincipal.destRec.y + 75.0f;


            if(beginFlag){

                    if(!flagFirstFase){

                        //Prólogo da historia
                        BeginDrawing();
                            PlaySound (musicaF1);
                            DrawTextureV(tela2_backgroundT, position, WHITE);
                            DrawText("Após passar pelo ENEM você, 'estudante', agora se botou numa enrascada ainda maior", 100, 300, 30, WHITE);
                            DrawText("o HELLCIN, será que você irá superar estes novos desafios? Ou ficará no caminho como", 100, 340, 30, WHITE);
                            DrawText("muitos outros antes de você, que perderam a sanidade frente aos novos desafios?", 100, 380, 30, WHITE);
                            DrawText("bem, veremos...", 100, 420, 30, WHITE);
                            DrawText("Pressione I para sofrer", 100, 500, 30, WHITE);
                        EndDrawing();

                    }else if(flagFirstFase == true && flagSecondFase == false && flagFinal == false && flagEndGame == false){
                        
                        //Primeira fase

                        BeginDrawing();
                        
                            StopSound (musicahist);

                            //Definição de bordas do mapa
                            mapBorders(&personagemPrincipal.destRec.x,&personagemPrincipal.destRec.y,personagemPrincipal.destRec.width,personagemPrincipal.destRec.height, 38, 38, 1562, 755);
                            //for(int cnt3 = 0; cnt3 < 8; cnt3++){ Tentei fazer funcionar e n deu rip dms ~~Rodrigo :(
                                //mapBorders(&wheelRun_destRect[cnt3].x,&wheelRun_destRect[cnt3].y,wheelRun_destRect[cnt3].width,wheelRun_destRect[cnt3].height, 38, 38, 1562, 755);
                            //}

                            //Inicio da camera
                            BeginMode2D(cameraPersonagem);

                                //Desenho do background, fase e protagonista
                                ClearBackground(BLACK);
                                DrawTextureV(firstFase, positionMaps, WHITE);                                   
                                DrawTexturePro(stormheadRun, personagemPrincipal.sourceRec, personagemPrincipal.destRec, origin, rotation, RAYWHITE);

                                //Movimentação dos inimigos
                                wheelRun_framecounter++;
                                if(contadorTempo >=0 && contadorTempo <= 50){

                                    for(contadorMovimentacao = 0; contadorMovimentacao < 8; contadorMovimentacao++)
                                        wheelEnemy[contadorMovimentacao].destRec.x += 2;
                                    

                                    if(wheelRun_sourceRect.width < 0){
                                        wheelRun_sourceRect.width = -1 * wheelRun_sourceRect.width;
                                    }

                                    wheelRun_sourceRect.y = runningAnimations(&wheelRun_framecounter, &wheelRun_framespeed, &wheelRun_currentframe, wheelRun_sourceRect.y, wheelRun_Heigth, wheelRun_nSprites);

                                }else if(contadorTempo > 50 && contadorTempo <= 100){
                                    for(contadorMovimentacao = 0; contadorMovimentacao < 8; contadorMovimentacao++)
                                        wheelEnemy[contadorMovimentacao].destRec.x -= 2;

                                    if(wheelRun_sourceRect.width > 0){
                                        wheelRun_sourceRect.width = -1 * wheelRun_sourceRect.width;
                                    }

                                        wheelRun_sourceRect.y = runningAnimations(&wheelRun_framecounter, &wheelRun_framespeed, &wheelRun_currentframe, wheelRun_sourceRect.y, wheelRun_Heigth, wheelRun_nSprites);
                                    
                                }else if(contadorTempo > 100 && contadorTempo <=150){
                                    for(contadorMovimentacao = 0; contadorMovimentacao < 8; contadorMovimentacao++){
                                        wheelEnemy[contadorMovimentacao].destRec.y += 2;
                                    }
                                    wheelRun_sourceRect.y = runningAnimations(&wheelRun_framecounter, &wheelRun_framespeed, &wheelRun_currentframe, wheelRun_sourceRect.y, wheelRun_Heigth, wheelRun_nSprites);
                                }else if(contadorTempo > 150 && contadorTempo <= 200){
                                    for(contadorMovimentacao = 0; contadorMovimentacao < 8; contadorMovimentacao++){
                                        wheelEnemy[contadorMovimentacao].destRec.y -= 2;

                                    }
                                    if(contadorTempo == 200){
                                            contadorTempo = 0;
                                        }
                                    wheelRun_sourceRect.y = runningAnimations(&wheelRun_framecounter, &wheelRun_framespeed, &wheelRun_currentframe, wheelRun_sourceRect.y, wheelRun_Heigth, wheelRun_nSprites);
                                    
                                }

                                //Colisão com os inimigos
                                for(int cnt5 = 0; cnt5 < 8; cnt5++){
                                    if(CheckCollisionRecs(personagemPrincipal.destRec,wheelEnemy[cnt5].destRec)){
                                        //Muda pra tela de batalha
                                        DrawText("HEY LISTEN", ((int) personagemPrincipal.destRec.x - 30.0f), ((int) personagemPrincipal.destRec.y + 50.0f), 8, WHITE);
                                    }
                                }

                                //Desenho dos inimigos
                                for(int cnt3 = 0; cnt3 < 8; cnt3++){

                                    DrawTexturePro(wheelRun, wheelRun_sourceRect, wheelEnemy[cnt3].destRec, origin, rotation, RAYWHITE);
                                }

                                //Desenho da barra de vida(fase de testes)
                                Rectangle barlife_sourceRect = {0.0f, 0.0f, (float)barlife_Width, (float)barlife_Heigth};
                                
                                for(int cnt4 = 0; cnt4 < 8; cnt4++){
                                    Rectangle barlife_destRect = {wheelEnemy[contadorMovimentacao].destRec.x - 30.0f, wheelEnemy[contadorMovimentacao].destRec.y - 20.0f, barlife_Width/4, barlife_Heigth/4};
                                    DrawTexturePro(barlife, barlife_sourceRect, barlife_destRect, enemiesVector[cnt4], rotation, WHITE); 
                                    //structureCollision(&personagemPrincipal.destRec,&wheelRun_destRect[cnt4]);
                                }
 
                                //Interação historia / lojinha
                                if(CheckCollisionRecs(personagemPrincipal.destRec,retanguloPauloConversa)){
                                    
                                    //Logica do botão de inicio de interação(tem um bug q n consigo resolver mas fds ~~ Rodrigo)
                                    DrawText("Pressione E para falar", ((int) personagemPrincipal.destRec.x - 30.0f), ((int) personagemPrincipal.destRec.y + 50.0f), 8, WHITE);
                                    if(IsKeyDown(KEY_E) && flagDialogo == false){
                                        flagDialogo = true;
                                    }else if(IsKeyDown(KEY_E) && flagDialogo == true){
                                        flagDialogo = false;
                                    }else if(flagDialogo == true){
                                        DrawRectangleRec(dialogoPaulo,GRAY);
                                    }

                                    //Interação historia no primeiro if, e no else if interação loja
                                    if(flagDialogo == true && flagLoja == false){
                                        DrawText("Você, me acordou...Meu nome é Paulo Salgado, sou o professor de AVLC,", dialogoPaulo.x,dialogoPaulo.y, 8, BLACK); 
                                        DrawText("mas não sou mal como os outros, estou aqui para lhe ajudar, se você conseguir",dialogoPaulo.x,dialogoPaulo.y + 8, 8, BLACK);
                                        DrawText("passar dos desafios das cadeiras, conseguirá sair desse inferno, os inimigos",dialogoPaulo.x,dialogoPaulo.y + 16, 8, BLACK);
                                        DrawText("daram abstrações, dê elas para mim que lhe deixarei mais forte",dialogoPaulo.x,dialogoPaulo.y + 24, 8, BLACK);
                                        DrawText("- Pressione L para acessar a loja",dialogoPaulo.x,dialogoPaulo.y + 32, 8, BLACK);

                                        if(IsKeyDown(KEY_L)){
                                            flagLoja = true;
                                        }
                                        
                                    }else if(flagDialogo == true && flagLoja == true){
                                        DrawText("Aqui estão seus upgrades e itens: ",dialogoPaulo.x,dialogoPaulo.y, 8, BLACK);
                                        DrawText("UPGRADEPLACEHOLDER1", dialogoPaulo.x,dialogoPaulo.y + 8, 8, BLACK); 
                                        DrawText("UPGRADEPLACEHOLDER2",dialogoPaulo.x,dialogoPaulo.y + 16, 8, BLACK);
                                        DrawText("UPGRADEPLACEHOLDER3",dialogoPaulo.x,dialogoPaulo.y + 24, 8, BLACK);
                                        DrawText("4. Antidepressivos :3 - 100",dialogoPaulo.x,dialogoPaulo.y + 32, 8, BLACK);

                                        //Escolha item da loja(upgrades e item de cura)
                                        if(IsKeyDown(KEY_KP_1)){
                                            escolhaUpgrade = 1;
                                        }else if(IsKeyDown(KEY_KP_2)){
                                            escolhaUpgrade = 2;
                                        }else if(IsKeyDown(KEY_KP_3)){
                                            escolhaUpgrade = 3;
                                        }else if(IsKeyDown(KEY_KP_4)){
                                            escolhaUpgrade = 4;
                                        }

                                        //Logica de compra da loja
                                        switch(escolhaUpgrade){
                                        case 1:                                       
                                            break;
                                        case 2:
                                            break;
                                        case 3:
                                            break;
                                        case 4:
                                            if(personagemPrincipal.abstractions < 100){
                                                DrawText("Abstraia mais um pouco",dialogoPaulo.x,dialogoPaulo.y + 40, 8, BLACK);
                                            }else{
                                                personagemPrincipal.healItemnumber++;
                                                personagemPrincipal.abstractions -= 100;
                                            }
                                            break;
                                        default:
                                            break;
                                        }
                                        escolhaUpgrade = 0;
                                    }
                        
                                }else{
                                    flagDialogo = false;
                                }
                                
                                
                            EndMode2D();
                        EndDrawing();
                    }else if(flagFirstFase == true && flagSecondFase == true && flagFinal == false && flagEndGame == false){

                        retanguloPaulo.x = 1490.0f;
                        retanguloPauloConversa.x = 1440.0f;
                        escolhaUpgrade = 0;

                        //Segunda fase

                        BeginDrawing();

                            mapBorders(&personagemPrincipal.destRec.x,&personagemPrincipal.destRec.y,personagemPrincipal.destRec.width,personagemPrincipal.destRec.height, 38, 38, 1562, 755);

                            //Inicio da camera
                            BeginMode2D(cameraPersonagem);

                                 //Desenho do background, fase e protagonista
                                ClearBackground(BLACK);                               
                                DrawTextureV(secondFase, positionMaps, WHITE);                                   
                                DrawTexturePro(stormheadRun, personagemPrincipal.sourceRec, personagemPrincipal.destRec, origin, rotation, RAYWHITE);

                                //Movimentação dos inimigos
                                mudRun_framecounter++;
                                if(contadorTempo >=0 && contadorTempo <= 50){

                                    for(contadorMovimentacao = 0; contadorMovimentacao < 8; contadorMovimentacao++)
                                        mudEnemy[contadorMovimentacao].destRec.x += 2;
                                    

                                    if(mudRun_sourceRect.width < 0){
                                        mudRun_sourceRect.width = -1 * mudRun_sourceRect.width;
                                    }

                                    mudRun_sourceRect.y = runningAnimations(&mudRun_framecounter, &mudRun_framespeed, &mudRun_currentframe, mudRun_sourceRect.y, mudRun_Heigth, mudRun_nSprites);

                                }else if(contadorTempo > 50 && contadorTempo <= 100){
                                    for(contadorMovimentacao = 0; contadorMovimentacao < 8; contadorMovimentacao++)
                                        mudEnemy[contadorMovimentacao].destRec.x -= 2;

                                    if(mudRun_sourceRect.width > 0){
                                        mudRun_sourceRect.width = -1 * mudRun_sourceRect.width;
                                    }

                                        mudRun_sourceRect.y = runningAnimations(&mudRun_framecounter, &mudRun_framespeed, &mudRun_currentframe, mudRun_sourceRect.y, mudRun_Heigth, mudRun_nSprites);
                                    
                                }else if(contadorTempo > 100 && contadorTempo <=150){
                                    for(contadorMovimentacao = 0; contadorMovimentacao < 8; contadorMovimentacao++){
                                        mudEnemy[contadorMovimentacao].destRec.y += 2;
                                    }
                                    mudRun_sourceRect.y = runningAnimations(&mudRun_framecounter, &mudRun_framespeed, &mudRun_currentframe, mudRun_sourceRect.y, mudRun_Heigth, mudRun_nSprites);
                                }else if(contadorTempo > 150 && contadorTempo <= 200){
                                    for(contadorMovimentacao = 0; contadorMovimentacao < 8; contadorMovimentacao++){
                                        mudEnemy[contadorMovimentacao].destRec.y -= 2;

                                    }
                                    if(contadorTempo == 200){
                                            contadorTempo = 0;
                                        }
                                    mudRun_sourceRect.y = runningAnimations(&mudRun_framecounter, &mudRun_framespeed, &mudRun_currentframe, mudRun_sourceRect.y, mudRun_Heigth, mudRun_nSprites);
                                    
                                }

                                //Colisão com os inimigos
                                for(int cnt5 = 0; cnt5 < 8; cnt5++){
                                    if(CheckCollisionRecs(personagemPrincipal.destRec,mudEnemy[cnt5].destRec)){
                                        //Muda pra tela de batalha
                                        DrawText("HEY LISTEN", ((int) personagemPrincipal.destRec.x - 30.0f), ((int) personagemPrincipal.destRec.y + 50.0f), 8, WHITE);
                                    }
                                }

                                //Desenho dos inimigos
                                for(int cnt3 = 0; cnt3 < 8; cnt3++){
                                    DrawTexturePro(mudRun, mudRun_sourceRect, mudEnemy[cnt3].destRec, origin, rotation, RAYWHITE);
                                }

                                //Interação historia / lojinha
                                if(CheckCollisionRecs(personagemPrincipal.destRec,retanguloPauloConversa)){
                                    
                                    //Logica do botão de inicio de interação(Nada mudou por aqui, por que olhar mais? ~~ Rodrigo)
                                    DrawText("Pressione E para falar", ((int) personagemPrincipal.destRec.x - 30.0f), ((int) personagemPrincipal.destRec.y + 50.0f), 8, WHITE);
                                    if(IsKeyDown(KEY_E) && flagDialogo == false){
                                        flagDialogo = true;
                                    }else if(IsKeyDown(KEY_E) && flagDialogo == true){
                                        flagDialogo = false;
                                    }else if(flagDialogo == true){
                                        DrawRectangleRec(dialogoPaulo,GRAY);
                                    }
                                
                                    //Interação historia no primeiro if, e no else if interação loja
                                    if(flagDialogo == true && flagLoja2 == false){
                                        DrawText("Uau! São poucos os que passam de [PLACEHOLDERNAME] sem ficar insanos, talvez", dialogoPaulo.x,dialogoPaulo.y, 8, BLACK); 
                                        DrawText("você realmente seja quem irá superar todos os desafios?! Não, não devemos nos pre",dialogoPaulo.x,dialogoPaulo.y + 8, 8, BLACK);
                                        DrawText("-cipitar ainda, você ainda tem mais desafios pela frente, e eu lhe ajudarei no que",dialogoPaulo.x,dialogoPaulo.y + 16, 8, BLACK);
                                        DrawText("puder, agora vá meu fiel aluno, e supere mais um obstáculo em sua jornada",dialogoPaulo.x,dialogoPaulo.y + 24, 8, BLACK);
                                        DrawText("- Pressione L para acessar a loja",dialogoPaulo.x,dialogoPaulo.y + 32, 8, BLACK);

                                        if(IsKeyDown(KEY_L)){
                                            flagLoja2 = true;
                                        }
                                        
                                    }else if(flagDialogo == true && flagLoja2 == true){
                                        DrawText("Aqui estão seus upgrades: ",dialogoPaulo.x,dialogoPaulo.y, 8, BLACK);
                                        DrawText("UPGRADEPLACEHOLDER1", dialogoPaulo.x,dialogoPaulo.y + 8, 8, BLACK); 
                                        DrawText("UPGRADEPLACEHOLDER2",dialogoPaulo.x,dialogoPaulo.y + 16, 8, BLACK);
                                        DrawText("UPGRADEPLACEHOLDER3",dialogoPaulo.x,dialogoPaulo.y + 24, 8, BLACK);
                                        DrawText("4. Antidepressivos :3 - 100",dialogoPaulo.x,dialogoPaulo.y + 32, 8, BLACK);

                                        //Escolha item da loja(upgrades e item de cura)
                                        if(IsKeyDown(KEY_KP_1)){
                                            escolhaUpgrade = 1;
                                        }else if(IsKeyDown(KEY_KP_2)){
                                            escolhaUpgrade = 2;
                                        }else if(IsKeyDown(KEY_KP_3)){
                                            escolhaUpgrade = 3;
                                        }else if(IsKeyDown(KEY_KP_4)){
                                            escolhaUpgrade = 4;
                                        }
                                    
                                        //Logica de compra da loja
                                        switch(escolhaUpgrade){
                                        case 1:                                       
                                            break;
                                        case 2:
                                            break;
                                        case 3:
                                            break;
                                        case 4:
                                            if(personagemPrincipal.abstractions < 100){
                                                DrawText("Abstraia mais um pouco",dialogoPaulo.x,dialogoPaulo.y + 40, 8, BLACK);
                                            }else{
                                                personagemPrincipal.healItemnumber++;
                                                personagemPrincipal.abstractions -= 100;
                                            }
                                            break;
                                        default:
                                            break;
                                        }
                                        escolhaUpgrade = 0;
                                    }
                        
                                }else{
                                    flagDialogo = false;
                                }
                                
                                
                            EndMode2D();
                        EndDrawing();
                    }else if(flagFirstFase == true && flagSecondFase == true && flagFinal == true && flagEndGame == false){
                        BeginDrawing();
                            PlaySound (musicaF1);
                            DrawTextureV(telafinal, position, WHITE);
                            DrawText("Você conseguiu!", 100, 300, 30, WHITE);
                            DrawText("o HELLCIN, será que você irá superar estes novos desafios? Ou ficará no caminho como", 100, 340, 30, WHITE);
                            DrawText("muitos outros antes de você, que perderam a sanidade frente aos novos desafios?", 100, 380, 30, WHITE);
                            DrawText("bem, veremos...", 100, 420, 30, WHITE);
                            DrawText("Pressione I para sofrer", 100, 500, 30, WHITE);
                        EndDrawing();
                    }else if(flagFirstFase == true && flagSecondFase == true && flagFinal == false && flagEndGame == true){
                        BeginDrawing();
                            PlaySound (musicaF1);
                            DrawTextureV(endgame, position, WHITE);
                            DrawText("Você perdeu!", 100, 300, 30, WHITE);
                            DrawText("o HELLCIN, será que você irá superar estes novos desafios? Ou ficará no caminho como", 100, 340, 30, WHITE);
                            DrawText("muitos outros antes de você, que perderam a sanidade frente aos novos desafios?", 100, 380, 30, WHITE);
                            DrawText("bem, veremos...", 100, 420, 30, WHITE);
                            DrawText("Pressione I para sofrer", 100, 500, 30, WHITE);
                        EndDrawing();
                    }
            }else{
                IniciarMenu();
            }

        }
    }
}