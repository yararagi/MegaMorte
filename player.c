#include<raylib.h>
#include<math.h>
#include<stdio.h>

typedef struct{
    double x,y;
    int speed, fallSpeed;
    double angle;
    unsigned int widht, height;
    Texture2D texture;
}Player;

void updatePosition(Player*);
void setPlayer(Player*, unsigned int, unsigned int);



void updatePosition(Player* player){
    if(IsKeyDown(KEY_D)){ player->angle-=2*PI*GetFrameTime(); }
    if(IsKeyDown(KEY_A)){ player->angle+=2*PI*GetFrameTime(); }
    if(IsKeyDown(KEY_W)){    
        player->speed=500;
        player->fallSpeed=0;    
    }
    else{   
        if(player->speed>0) player->speed-=3;
        if(player->fallSpeed<300) player->fallSpeed+=15;   
    }
    
    player->y+=( (player->speed*sin(player->angle+PI)) + player->fallSpeed )*GetFrameTime();
    player->x+=( (player->speed*cos(player->angle)) + cos(player->angle) )*GetFrameTime();

    // AGGIUNGERE I LIMITI DELLO SCHERMO
            printf("\n\n%lf-%lf-%lf-%lf\n\n",player->x,player->y,cos(player->angle),sin(180+player->angle));
}

void setPlayer(Player* player, unsigned int displayX, unsigned int displayY){
    player->y=displayY/2;
    player->x=displayX/2;
    player->angle=PI/2;
    player->fallSpeed=0;
    player->height=15;
    player->widht=15;
    player->speed=0;
    //TODO TEXTURE
}