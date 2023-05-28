#ifndef ENEMY_H_   
#define ENEMY_H_

#include<raylib.h>
#include<stdbool.h>

typedef struct{
    float x, y;
    short int widht, height;
    short int speed;
    short int hp;
    Texture2D texture;
}Enemy;

void updateEnemiesPosition(Enemy*);
void setEnemy(Enemy *, const char *, bool);
void deleteEnemy(Enemy**, unsigned short int, unsigned short int*);

#endif //ENEMY_H_