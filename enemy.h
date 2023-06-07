#ifndef ENEMY_H_   
#define ENEMY_H_

#include<raylib.h>
#include<stdbool.h>
#include"laser.h"

#define maxNumOfEnemies 30

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

void setEnemy(Enemy * enemy, const char * imgFilename, bool setTexture);
void deleteEnemy(Enemy* enemies, unsigned short int posDel, unsigned short int* nEnemies);
void updateEnemy(Enemy *enemy, Vector2 playerPos);

void shootEnemyLaser(Enemy *enemy, float playerY, float asseX);
void updateEnemyLaser(Enemy *enemy);

#endif //ENEMY_H_