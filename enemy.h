#ifndef ENEMY_H_   
#define ENEMY_H_

#include<raylib.h>

typedef struct{
    float x, y;
    int widht, height;
    int speed;
    unsigned short int hp;
    Texture2D texture;
}Enemy;

void updateEnemiesPosition(Enemy*);
void setEnemy(Enemy *, const char *);
void deleteEnemy(Enemy**, unsigned short int, unsigned short int*);

#endif //ENEMY_H_