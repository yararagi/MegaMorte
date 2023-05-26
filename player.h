#ifndef PLAYER_H_   
#define PLAYER_H_

#include<raylib.h>
#include<stdbool.h>

typedef struct{
    short int widht, height;
    float x, y;
    short int speed, fallSpeed;
    double angle;
    short int hp;
    bool megadeth;
    Texture2D texture;
}Player;

void updatePlayerPosition(Player*);
void setPlayer(Player*, const char*);

#endif //PLAYER_H_
