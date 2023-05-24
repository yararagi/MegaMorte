#ifndef ENEMY_H_   
#define ENEMY_H_

#include<raylib.h>
#include<stdbool.h>

typedef struct{
    bool alive;
    float x, y;
    int widht, height;
    int speed;
    unsigned short int hp;
    Texture2D texture;
}Enemy;

void updateEnemiesPosition(Enemy*);
void setEnemy(Enemy *, const char *);

#endif //ENEMY_H_