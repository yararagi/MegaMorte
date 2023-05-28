#ifndef PLAYER_H_   
#define PLAYER_H_

#include<raylib.h>
#include<stdbool.h>

#define maxNumOfLasers 50

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

typedef struct{
    short int rad;
    float x, y;
    short int speed;
    double angle;
    Texture2D texture;
}PlayerLaser;

void updatePlayerPosition(Player*);
void setPlayer(Player*, const char*, bool);

void updatePlayerLaser(PlayerLaser*, unsigned short int*, Player*);
void deletePlayerLaser(PlayerLaser*, unsigned short int* , unsigned short int);
void setPlayerLasers(PlayerLaser*, unsigned short int, const char*);
void shootPlayerLaser(PlayerLaser*, Player*);

#endif //PLAYER_H_
