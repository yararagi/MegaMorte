#include"enemy.h"

#include<stdlib.h>
#include<time.h>
#include<raylib.h>
#include<stdbool.h>
#include<string.h>

void setEnemy(Enemy * enemy, const char * imgFilename, bool setTexture){
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
    if(setTexture){
        enemyImg= LoadImage(imgFilename);
        ImageResize(&enemyImg, enemy->widht, enemy->height);
        enemy->texture= LoadTextureFromImage(enemyImg);
        UnloadImage(enemyImg);
    }
}

void deleteEnemy(Enemy** enemies, unsigned short int posDel, unsigned short int* nEnemies){
    //memmove( ((*enemies)+posDel), ((*enemies)+posDel+1), sizeof(Enemy)*((*nEnemies)-posDel));
    for(int i=posDel; i<*nEnemies-1;i++){
        (*enemies)[i]=(*enemies)[i+1];
    }
    *nEnemies-=1;
    *enemies=(Enemy*)realloc(*enemies, (*nEnemies)*(sizeof(Enemy)));
}