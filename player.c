#include<raylib.h>
#include<math.h>
#include<stdio.h>

typedef struct{
    double x,y;
    int speed, fallSpeed;
    double angle;
    unsigned int widht, height;
    bool megadeth;
    unsigned short int hp;
    Texture2D texture;
}Player;

void updatePosition(Player*);
void setPlayer(Player*, const char*);



void updatePosition(Player* player){
    if(IsKeyDown(KEY_D)){ player->angle-=2*PI*GetFrameTime(); }
    if(IsKeyDown(KEY_A)){ player->angle+=2*PI*GetFrameTime(); }
    if(IsKeyDown(KEY_W) && player->y-player->height>0){    
        player->speed=500;
        player->fallSpeed=0;    
    }
    else{   
        if(player->speed>0) player->speed-=3;
        if(player->fallSpeed<300) player->fallSpeed+=15;   
    }

    if(player->x-player->widht>GetScreenWidth()){
        player->x=0;
    }
    if(player->x+player->widht<0){
        player->x=GetScreenWidth();
    }
    if(player->y>GetScreenHeight()){
        player->megadeth=true;
        player->speed=0;
    }
    
    player->y+=( (player->speed*sin(player->angle+PI)) + player->fallSpeed )*GetFrameTime();
    player->x+=( (player->speed*cos(player->angle)) + cos(player->angle) )*GetFrameTime();

}

void setPlayer(Player* player, const char* imgFilename){
    player->y=GetScreenHeight()/2;
    player->x=GetScreenWidth()/2;
    player->angle=PI/2;
    player->fallSpeed=0;
    player->height=35;
    player->widht=35;
    player->speed=0;
    player->hp=100;
    player->megadeth=false;

    Image playerImg;

    playerImg= LoadImage(imgFilename);
    ImageResize(&playerImg, player->widht, player->height);
    player->texture= LoadTextureFromImage(playerImg);
    UnloadImage(playerImg);
}

