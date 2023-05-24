#ifndef PLAYER_H_   
#define PLAYER_H_

#include<raylib.h>
#include<stdbool.h>

typedef struct{
    float x, y;
    int speed, fallSpeed;
    double angle;
    unsigned int widht, height;
    bool megadeth;
    unsigned short int hp;
    Texture2D texture;
}Player;

void updatePlayerPosition(Player*);
void setPlayer(Player*, const char*);

#endif //PLAYER_H_
