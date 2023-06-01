#ifndef PLAYER_H_   
#define PLAYER_H_

#include<raylib.h>
#include<stdbool.h>
#include"laser.h"

typedef struct{
    short int width, height;
    float x, y;
    short int speed, fallSpeed;
    double angle;
    short int hp;
    unsigned short int fireRate;
    bool megadeth;
    Texture2D texture;
}Player;

void updatePlayerPosition(Player*);
void setPlayer(Player*, const char*, bool);

void updatePlayerLaser(Laser*, unsigned short int*, Player*);
void shootPlayerLaser(Laser*, Player*);

#endif //PLAYER_H_
