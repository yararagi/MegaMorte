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
    unsigned short int nLasers;
    Laser lasers[maxNumOfPlayerLasers];
    Texture2D texture;
}Player;

void updatePlayerPos(Player* player, Sound soundDeathByDrowning);
void setPlayer(Player* player, const char* imgFilename, bool setTexture);

void updatePlayerLaser(Laser* lasers, Player *player, Sound laserSound);
void shootPlayerLaser(Laser* laser, Player *player);

#endif //PLAYER_H_
