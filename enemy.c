#include"enemy.h"

#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#include<raylib.h>
#include<math.h>

void setEnemy(Enemy * enemy, const char * imgFilename){
    Image enemyImg;

    srand(time(NULL));

    enemy->speed=400;
    enemy->hp=150;
    enemy->widht=20;
    enemy->height=20;
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

void deleteEnemy(Enemy** enemies, unsigned short int posDel, unsigned short int* nEnemies){
    for(int i=posDel; i<*nEnemies;i++){
        enemies[i]->x=enemies[i+1]->x;
        enemies[i]->y=enemies[i+1]->y;
        enemies[i]->height=enemies[i+1]->height;
        enemies[i]->widht=enemies[i+1]->widht;
        enemies[i]->speed=enemies[i+1]->speed;
        enemies[i]->hp=enemies[i+1]->hp;
        enemies[i]->texture=enemies[i+1]->texture;
    }
    *nEnemies-=1;

    *enemies=(Enemy*)realloc(*enemies, (*nEnemies)*(sizeof(Enemy)));
}