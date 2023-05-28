#ifndef ENEMY_H_   
#define ENEMY_H_

#include<raylib.h>
#include<stdbool.h>

#define maxNumOfEnemies 50

typedef struct{
    float x, y;
    short int width, height;
    short int speed;
    short int hp;
    // bool alive;
    Texture2D texture;
}Enemy;

void updateEnemiesPosition(Enemy*);
void setEnemy(Enemy *, const char *, bool);
void deleteEnemy(Enemy*, unsigned short int, unsigned short int*);

#endif //ENEMY_H_