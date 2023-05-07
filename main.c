#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<raylib.h>
#include<time.h>
#include"player.c"

unsigned int displayX;
unsigned int displayY;

void initWindow(void);
void setBackground(Texture2D*, const char*);

int main(void){
    Texture2D background;
    Player player;
    
    initWindow();
    setBackground(&background, "img/background_sea.png");
    setPlayer(&player,"img/player.png",displayX,displayY);

    while(!WindowShouldClose()){
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawTexture(background, 0, 0, WHITE);
            updatePosition(&player);
            DrawTexturePro(
                player.texture,
                (Rectangle){0,0,player.widht,player.height},
                (Rectangle){player.x,player.y,player.widht,player.height},
                (Vector2){player.widht/2,player.height/2},
                (player.angle*-180/PI)+90,
                WHITE
            );

        EndDrawing();
    }
    UnloadTexture(player.texture);
    UnloadTexture(background);

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
