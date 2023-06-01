#ifndef ENEMY_H_   
#define ENEMY_H_

#include<raylib.h>
#include<stdbool.h>
#include"laser.h"

#define maxNumOfEnemies 25

typedef struct{
    float x, y;
    short int width, height;
    short int speed;
    short int hp;
    unsigned short int clock;
    unsigned short int nLasers;
    Laser lasers[maxNumOfEnemyLasers];
    Texture2D texture;
}Enemy;

void updateEnemy(Enemy*, Vector2);
void setEnemy(Enemy *, const char *, bool);
void deleteEnemy(Enemy*, unsigned short int, unsigned short int*);

void shootEnemyLaser(Enemy*, float, float);
void updateEnemyLaser(Enemy*);

#endif //ENEMY_H_