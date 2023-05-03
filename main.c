#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<raylib.h>
#include<time.h>

unsigned int displayX;
unsigned int displayY;

void initWindow(void);

int main(void){

    initWindow();

    while(!WindowShouldClose()){
        BeginDrawing();
            
        EndDrawing();
    }
    CloseWindow();

    return 0;
}

void initWindow(void){
    InitWindow(800, 450, "prj");

    int display = GetCurrentMonitor();
    displayX=GetMonitorWidth(display);
    displayY=GetMonitorHeight(display);

    SetWindowSize(displayX, displayY);
    SetWindowState(FLAG_FULLSCREEN_MODE);
    
    SetTargetFPS(60);
    HideCursor();
}
