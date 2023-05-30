#ifndef ENEMY_H_   
#define ENEMY_H_

#include<raylib.h>
#include<stdbool.h>

#define maxNumOfEnemies 25

typedef struct{
    float x, y;
    short int width, height;
    short int speedY, speedX;
    short int hp;
    unsigned short int clock;
    Texture2D texture;
}Enemy;

void updateEnemy(Enemy*);
void setEnemy(Enemy *, const char *, bool);
void deleteEnemy(Enemy*, unsigned short int, unsigned short int*);

#endif //ENEMY_H_