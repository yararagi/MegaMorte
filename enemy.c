#include"enemy.h"

#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#include<raylib.h>
#include<math.h>

void setEnemy(Enemy * enemy, const char * imgFilename){
    Image enemyImg;

    srand(time(NULL));

    enemy->alive=false;
    enemy->speed=400;
    enemy->hp=150;
    switch(rand()%3){
        case 0:
            enemy->x=rand()%(GetScreenWidth()/2)-(GetScreenWidth()/2);
            enemy->y=rand()%GetScreenHeight();
            break;
        case 1:
            enemy->x=rand()%GetScreenWidth();
            enemy->y=rand()%(GetScreenHeight()/2)-(GetScreenHeight()/2);
            break;
        case 2:
            enemy->x=rand()%(GetScreenWidth()/2)+GetScreenWidth();
            enemy->y=rand()%GetScreenHeight();
            break;
        default:
            break;
    }

    enemyImg= LoadImage(imgFilename);
    ImageResize(&enemyImg, enemy->widht, enemy->height);
    enemy->texture= LoadTextureFromImage(enemyImg);
    UnloadImage(enemyImg);
}