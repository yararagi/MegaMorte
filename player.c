#include"player.h"

#include<stdbool.h>
#include<raylib.h>
#include<math.h>

#include<stdio.h>

void updatePlayerPosition(Player* player){
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

    if(player->x-player->width>GetScreenWidth()){
        player->x=0;
    }
    if(player->x+player->width<0){
        player->x=GetScreenWidth();
    }
    if(player->hp<1){
        player->megadeth=true;
    }
    if(player->y>GetScreenHeight()){
        player->speed=0;
        player->hp=0;
    }
    
    if(player->fireRate>0){ 
        player->fireRate-=1;
    }
    
    player->y+=( (player->speed*sin(player->angle+PI)) + player->fallSpeed )*GetFrameTime();
    player->x+=( (player->speed*cos(player->angle)) + cos(player->angle) )*GetFrameTime();

}

void setPlayer(Player* player, const char* imgFilename, bool setTexture){
    player->y=GetScreenHeight()/2;
    player->x=GetScreenWidth()/2;
    player->angle=PI/2;
    player->fallSpeed=0;
    player->height=35;
    player->width=35;
    player->speed=0;
    player->hp=300;
    player->megadeth=false;
    player->fireRate=0;
    player->nLasers=0;

    Image playerImg;

    if(setTexture){
        playerImg= LoadImage(imgFilename);
        ImageResize(&playerImg, player->width, player->height);
        player->texture= LoadTextureFromImage(playerImg);
        UnloadImage(playerImg);
    }
}

void updatePlayerLaser(Laser* lasers, Player *player){
    if((IsKeyPressed(KEY_L) || (IsKeyDown(KEY_L) && player->fireRate==0) )&& player->nLasers<maxNumOfPlayerLasers){
        shootPlayerLaser(&(lasers[player->nLasers]), player);
        player->nLasers+=1;
    }
    for(unsigned short int i=0; i<player->nLasers; i++){
        lasers[i].x+=GetFrameTime()*(cos(lasers[i].angle+PI)*lasers[i].speed);
        lasers[i].y+=GetFrameTime()*(sin(lasers[i].angle)*lasers[i].speed);

        if(lasers[i].x>GetScreenWidth() || lasers[i].y>GetScreenHeight() || lasers[i].y<0 || lasers[i].x<0){
            deleteLaser(lasers, &(player->nLasers), i);
        }
    }
}

void shootPlayerLaser(Laser* laser, Player *player){
    laser->angle=player->angle;
    laser->x=player->x-(laser->rad/2);
    laser->y=player->y-(laser->rad/2);
    laser->speed=-1000;
    player->fireRate=10;
}