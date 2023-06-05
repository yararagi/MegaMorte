#include<stdio.h>
#include<stdlib.h>
#include<raylib.h>
#include<time.h>
#include"player.h"
#include"enemy.h"
#include"laser.h"

unsigned int displayX;
unsigned int displayY;

void initWindow(void);
void setBackground(Texture2D*, const char*);
void setTitle(Texture2D*, const char*);

int main(void){
    Texture2D background, backgroundMenu, logo, deathText;
    Font megaFont;
    float gameTime=0;
    unsigned short int kill=0;
    bool pause=false;
    
    Player player;

    unsigned short int nEnemies=3;
    Enemy enemies[maxNumOfEnemies];
    
    short int menu=0;
    unsigned short int scelta=0;
    
    float spawnRate=1;
    unsigned short int spawnTiming=0;


    initWindow();
    setBackground(&background, "img/backgroundSea.png");
    setBackground(&backgroundMenu, "img/backgroundMenu.png");
    setTitle(&logo, "img/logo.png");
    setTitle(&deathText, "img/endgame.png");
    megaFont=LoadFont("font/Megadeth.ttf");
    setPlayer(&player,"img/player.png", true);
    setLasers(player.lasers, maxNumOfPlayerLasers, "img/laser.png");
    Music soundtrack;
    soundtrack = LoadMusicStream("song/Tornado Of Souls.mp3");

    for(unsigned short int i=0; i<maxNumOfEnemies; i++){ 
        setEnemy(&(enemies[i]), "img/enemy.png", true);
        setLasers(enemies[i].lasers, maxNumOfEnemyLasers, "img/laser.png");
    }

    srand(time(NULL));

    while(1){
        BeginDrawing();

            if(scelta==0){
                if(IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)){ menu--; }
                if(IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)){ menu++; }
                if(menu<0){ menu=2; }
                if(menu>2){ menu=0; }
                if(IsKeyPressed(KEY_ENTER)){ scelta=menu+1; menu=0; }
                
                DrawTexture(backgroundMenu, 0, 0, WHITE);
                DrawTexture(logo, displayX/2 -227, displayY/4, WHITE);
                DrawTextEx(megaFont, "GIOCA", (Vector2){(displayX/2)-(MeasureText("GIOCA",35)/2), displayY/2}, 35, 0, menu==0 ? (Color){164, 22, 26, 150} : (Color){35, 35, 35, 250} );
                DrawTextEx(megaFont, "CREDITI", (Vector2){(displayX/2)-(MeasureText("CREDITI",35)/2), displayY/2 +50}, 35, 0, menu==1 ? (Color){164, 22, 26, 150} : (Color){35, 35, 35, 250} );
                DrawTextEx(megaFont, "EXIT", (Vector2){(displayX/2)-(MeasureText("EXIT",35)/2), displayY/2 +100}, 35, 0, menu==2 ? (Color){164, 22, 26, 150} : (Color){35, 35, 35, 250} );

            }else if(scelta==1){
                if(!(player.megadeth) && !(pause)){
                    DrawTexture(background, 0, 0, WHITE);
                    if (!IsMusicStreamPlaying(soundtrack)){ PlayMusicStream(soundtrack); }
                    UpdateMusicStream(soundtrack);

                    gameTime+=GetFrameTime();

                    updatePlayerPosition(&player);
                    updatePlayerLaser(player.lasers, &player);

                    for(unsigned short int i=0; i<player.nLasers; i++){
                        DrawTexture(player.lasers[i].texture, player.lasers[i].x, player.lasers[i].y, WHITE);
                    }

                    spawnTiming+=1;
                    if(spawnTiming>300*spawnRate && nEnemies<maxNumOfEnemies-1){
                        for(unsigned short int i=0; i<rand()%2+1; i++){
                            setEnemy(&(enemies[nEnemies]),"yeyy" , false);
                            nEnemies+=1;
                        }
                        spawnTiming=0;
                        spawnRate-=0.03;
                    }
                    

                    for(unsigned short int i=0; i<nEnemies; i++){
                        DrawTexture(enemies[i].texture, enemies[i].x, enemies[i].y ,WHITE);
                        for(unsigned short int j=0; j<player.nLasers; j++){
                            if(CheckCollisionCircleRec((Vector2){player.lasers[j].x, player.lasers[j].y}, player.lasers[j].rad, (Rectangle){enemies[i].x, enemies[i].y, enemies[i].width, enemies[i].height})){
                                deleteLaser(player.lasers, &(player.nLasers), j);
                                enemies[i].hp-=50;
                            }
                        }
                        for(unsigned short int j=0; j<enemies[i].nLasers; j++){
                            DrawTexture(enemies[i].lasers[j].texture, enemies[i].lasers[j].x, enemies[i].lasers[j].y, RED);
                            if(CheckCollisionCircleRec((Vector2){enemies[i].lasers[j].x, enemies[i].lasers[j].y}, enemies[i].lasers[j].rad, (Rectangle){player.x, player.y, player.width, player.height} )){
                                player.hp-=30;
                                deleteLaser(&(enemies[i].lasers[j]), &(enemies[i].nLasers), j);
                            }
                        }
                        if(enemies[i].hp<1){
                            deleteEnemy(enemies, i, &nEnemies);
                            kill+=1;
                        }
                    
                        updateEnemy(&(enemies[i]), (Vector2){player.x, player.y});
                    }

                    DrawTexturePro(
                        player.texture,
                        (Rectangle){0,0,player.width,player.height},
                        (Rectangle){player.x,player.y,player.width,player.height},
                        (Vector2){player.width/2,player.height/2},
                        (player.angle*-180/PI)+90,
                        WHITE
                    );

                    DrawTextEx(megaFont, TextFormat("HP: %d", player.hp), (Vector2){35,35},30,0,BLACK);
                    DrawTextEx(megaFont, TextFormat("KILL: %d", kill), (Vector2){35,75},30,0,BLACK);
                    DrawTextEx(megaFont, TextFormat("%02d:%02d",(int)gameTime/60, (int)gameTime%60 ), (Vector2){displayX-35-MeasureText("XX:XX",30),35},30,0,BLACK);

                    if(IsKeyPressed(KEY_ESCAPE)){ pause=true; }
            
                }else if(pause){
                    DrawTextEx(megaFont, "PAUSE", (Vector2){displayX/2-MeasureText("PAUSE",50)/2, displayY/3}, 50, 0, BLACK);
                    DrawTextEx(megaFont, "CONTINUE", (Vector2){(displayX/2)-(MeasureText("CONTINUE",35)/2), displayY/2+100}, 35, 0,menu==0 ? (Color){164, 22, 26, 150} : (Color){35, 35, 35, 250} );
                    DrawTextEx(megaFont, "EXIT", (Vector2){ (displayX/2)-(MeasureText("EXIT",35)/2), displayY/2 +200}, 35, 0, menu==1 ? (Color){164, 22, 26, 150} : (Color){35, 35, 35, 250} );

                    if(IsKeyPressed(KEY_UP)){ menu--; }
                    if(IsKeyPressed(KEY_DOWN)){ menu++; }
                    if(menu<0){ menu=1; }
                    if(menu>1){ menu=0; }
  
                    if(IsKeyPressed(KEY_ENTER)){ 
                        if(menu==1){
                            menu=0;
                            scelta=0;
                            setPlayer(&player,"img/player.png", false);
                            player.nLasers=0;
                            nEnemies=3;
                            for(unsigned short int i=0; i<nEnemies; i++){ 
                                setEnemy(&(enemies[i]), "img/enemy.png", false); 
                                enemies[i].nLasers=0;
                            }
                            spawnRate=1;
                            gameTime=0;
                            kill=0;
                        }
                        pause=false;
                    }
                }else{ 

                    StopMusicStream(soundtrack);
                    DrawTexture(deathText, displayX/2 -175, displayY/2 -38, WHITE);

                    if(IsKeyPressed(KEY_UP)){ menu--; }
                    if(IsKeyPressed(KEY_DOWN)){ menu++; }
                    if(menu<0){ menu=1; }
                    if(menu>1){ menu=0; }
                    
                    DrawTextEx(megaFont, "PLAY AGAIN", (Vector2){(displayX/2)-(MeasureText("PLAY AGAIN",35)/2), displayY/2+100}, 35, 0,menu==0 ? (Color){164, 22, 26, 150} : (Color){35, 35, 35, 250} );
                    DrawTextEx(megaFont, "EXIT", (Vector2){ (displayX/2)-(MeasureText("EXIT",35)/2), displayY/2 +200}, 35, 0, menu==1 ? (Color){164, 22, 26, 150} : (Color){35, 35, 35, 250} );
                    if(IsKeyPressed(KEY_ENTER)){ 
                        if(menu==0){
                            scelta=1;
                        }else{
                            menu=0;
                            scelta=0;
                        }
                        setPlayer(&player,"img/player.png", false);
                        player.nLasers=0;
                        nEnemies=3;
                        for(unsigned short int i=0; i<nEnemies; i++){ 
                            setEnemy(&(enemies[i]), "img/enemy.png", false); 
                            enemies[i].nLasers=0;
                        }
                        spawnRate=1;
                        gameTime=0;
                        kill=0;
                    }
                }

            }else if(scelta==2){
                DrawTexture(backgroundMenu, 0, 0, WHITE);
		        DrawTextEx(megaFont, "CREDITI", (Vector2){(displayX/2)-(MeasureText("CREDITI",45)/2), displayY/4}, 45, 0, (Color){35, 35, 35, 250} );
                DrawTextEx(megaFont, "PROGRAMMATORE/DESIGNER/COORDINATORE:", (Vector2){(displayX/2)-(MeasureText("PROGRAMMATORE/DESIGNER/COORDINATORE:",35)/2), displayY/2-50}, 35, 0,RAYWHITE /*(Color){213, 189, 175, 250}*/  );
                DrawTextEx(megaFont, "MONTANARO YARI", (Vector2){(displayX/2)-(MeasureText("MONTANARO YARI",35)/2), displayY/2}, 35, 0, RAYWHITE ); 
                DrawTextEx(megaFont, "PROGRAMMATORE/DESIGNER/MUSIC DESIGNEER:", (Vector2){(displayX/2)-(MeasureText("PROGRAMMATORE/DESIGNER/MUSIC DESIGNEER:",35)/2), displayY/2+50}, 35, 0, RAYWHITE ); 
                DrawTextEx(megaFont, "TIVERON SEBASTIANO", (Vector2){(displayX/2)-(MeasureText("TIVERON SEBASTIANO",35)/2), displayY/2+100}, 35, 0, RAYWHITE ); 
                DrawTextEx(megaFont, "TORNA AL MENU", (Vector2){(displayX/2)-(MeasureText("TORNA AL MENU",35)/2), displayY/2 +300}, 35, 0, (Color){164, 22, 26, 150} );

                if(IsKeyPressed(KEY_ENTER)){
                    scelta=0;
                }

            }else{
                break;
            }

        EndDrawing();
    }

    for(unsigned short int i=0; i<maxNumOfEnemies; i++){ UnloadTexture(enemies[i].texture); }
    UnloadTexture(player.texture);
    UnloadTexture(background);
    UnloadTexture(backgroundMenu);
    UnloadTexture(logo);
    UnloadTexture(deathText);
    UnloadMusicStream(soundtrack);
    UnloadFont(megaFont);
    
    CloseAudioDevice();
    CloseWindow();

    return 0;
}



/*-----------------------------------------FUNCTIONS-----------------------------------------*/

void initWindow(void){
    InitWindow(800, 450, "prj");

    int display = GetCurrentMonitor();
    displayX=GetMonitorWidth(display);
    displayY=GetMonitorHeight(display);

    SetWindowSize(displayX, displayY);
    SetWindowState(FLAG_VSYNC_HINT);
    SetWindowState(FLAG_FULLSCREEN_MODE);
    
    SetTargetFPS(60);
    HideCursor();

    InitAudioDevice();
}

void setBackground(Texture2D* texture, const char* imgFilename){
    Image backgroundImg;

    backgroundImg= LoadImage(imgFilename);
    ImageResize(&backgroundImg, displayX, displayY);
    *texture= LoadTextureFromImage(backgroundImg);
    UnloadImage(backgroundImg);
}

void setTitle(Texture2D* texture, const char* imgFilename){
    Image textImg;

    textImg= LoadImage(imgFilename);
    *texture= LoadTextureFromImage(textImg);
    UnloadImage(textImg);
}
