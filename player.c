#include<raylib.h>
#include<math.h>
#include<stdio.h>

typedef struct{
    double x,y;
    int ySpeed, xSpeed, fallSpeed;
    double angle;
    unsigned int widht, height;
    Texture2D texture;
}Player;

void updatePosition(Player*);
void setPlayer(Player*, unsigned int, unsigned int);



void updatePosition(Player* player){
    if(IsKeyDown(KEY_D)){ player->angle-=0.06; }
    if(IsKeyDown(KEY_A)){ player->angle+=0.06; }
    if(IsKeyDown(KEY_W)){    
        player->ySpeed=500;
        player->xSpeed=500;
        player->fallSpeed=0;    
    }
    else{   
        player->ySpeed=0;
        player->xSpeed-=1;
        if(player->fallSpeed<250) player->fallSpeed+=10;   
    }
    
    player->y+=((player->ySpeed*sin(player->angle+180))+player->fallSpeed)*GetFrameTime();
    player->x+=(player->xSpeed*cos(player->angle))*GetFrameTime();

    //DA MIGLIORARE E AGGIUNGERE I LIMITI DELLO SCHERMO
    //quando W non è premuta la rotta deve rimanere invariata ma l'angolo cambiare
            printf("\n\n%lf-%lf-%lf-%lf\n\n",player->x,player->y,cos(player->angle),sin(180+player->angle));
}

void setPlayer(Player* player, unsigned int displayX, unsigned int displayY){
    player->y=displayY/2;
    player->x=displayX/2;
    player->angle=90;
    player->fallSpeed=0;
    player->height=30;
    player->widht=30;
    player->ySpeed=0;
    player->xSpeed=0;
    //TODO TEXTURE
}