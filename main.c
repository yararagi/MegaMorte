#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<raylib.h>
#include<time.h>
#include"player.h"
#include"enemy.h"

unsigned int displayX;
unsigned int displayY;

void initWindow(void);
void setBackground(Texture2D*, const char*);
void setTitle(Texture2D*, const char*);

int main(void){
    Texture2D background, backgroundMenu, logo, deathText;
    Font megaFont;
    Player player;
    unsigned short int nEnemies=25;
    Enemy *enemies= (Enemy*)malloc(nEnemies*sizeof(Enemy));
    short int menu=0;
    unsigned short int scelta=0;
    
    initWindow();
    setBackground(&background, "img/backgroundSea.png");
    setBackground(&backgroundMenu, "img/backgroundMenu.png");
    setTitle(&logo, "img/logo.png");
    setTitle(&deathText, "img/endgame.png");
    megaFont=LoadFont("font/Megadeth.ttf");
    setPlayer(&player,"img/player.png");
    for(int i=0; i<nEnemies; i++){ setEnemy(enemies+i, "img/enemy.png"); }


    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(RAYWHITE);
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
                DrawTexture(background, 0, 0, WHITE);
                updatePlayerPosition(&player);
                DrawTexturePro(
                    player.texture,
                    (Rectangle){0,0,player.widht,player.height},
                    (Rectangle){player.x,player.y,player.widht,player.height},
                    (Vector2){player.widht/2,player.height/2},
                    (player.angle*-180/PI)+90,
                    WHITE
                );

                if(player.megadeth){
                    
                    DrawTexture(deathText, displayX/2 -175, displayY/2 -38, WHITE);

                    if(IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W) ){ menu--; }
                    if(IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S) ){ menu++; }
                    if(menu<0){ menu=1; }
                    if(menu>1){ menu=0; }
                    
                    DrawTextEx(megaFont, "GIOCA ANCORA", (Vector2){(displayX/2)-(MeasureText("GIOCA ANCORA",35)/2), displayY/2+100}, 35, 0,menu==0 ? (Color){164, 22, 26, 150} : (Color){35, 35, 35, 250} );
                    DrawTextEx(megaFont, "EXIT", (Vector2){ (displayX/2)-(MeasureText("EXIT",35)/2), displayY/2 +200}, 35, 0, menu==1 ? (Color){164, 22, 26, 150} : (Color){35, 35, 35, 250} );
                    if(IsKeyPressed(KEY_ENTER)){ 
                        if(menu==0){
                            scelta=1;
                        }else{
                            menu=0;
                            scelta=0;
                        }
                        setPlayer(&player,"img/player.png");
                    }
                }
            }else if(scelta==2){
                DrawTexture(backgroundMenu, 0, 0, WHITE);
		        DrawTextEx(megaFont, "CREDITI", (Vector2){(displayX/2)-(MeasureText("CREDITI",45)/2), displayY/4}, 45, 0, (Color){35, 35, 35, 250} );
                DrawTextEx(megaFont, "PROGRAMMATORE/DESIGNER/COORDINATORE:", (Vector2){(displayX/2)-(MeasureText("PROGRAMMATORE/DESIGNER/COORDINATORE:",35)/2), displayY/2-50}, 35, 0, (Color){213, 189, 175, 250} );
                DrawTextEx(megaFont, "MONTANARO YARI", (Vector2){(displayX/2)-(MeasureText("MONTANARO YARI",35)/2), displayY/2}, 35, 0, RAYWHITE ); 
                DrawTextEx(megaFont, "PROGRAMMATORE/DESIGNER/MUSIC DESIGNEER:", (Vector2){(displayX/2)-(MeasureText("PROGRAMMATORE/DESIGNER/MUSIC DESIGNEER:",35)/2), displayY/2+50}, 35, 0, (Color){213, 189, 175, 250} ); 
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
    free(enemies);

    UnloadTexture(player.texture);
    UnloadTexture(background);
    UnloadTexture(backgroundMenu);
    UnloadTexture(logo);
    UnloadTexture(deathText);
    UnloadFont(megaFont);

    CloseWindow();

    return 0;
}

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