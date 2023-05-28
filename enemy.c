#include"enemy.h"

#include<stdlib.h>
#include<time.h>
#include<raylib.h>
#include<string.h>

void setEnemy(Enemy * enemy){
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

    
}

void setEnemiesTexture(Enemy *enemies, const char* imgFilename, int nEnemies){
    Image enemyImg;
    for(unsigned short int i=0; i<nEnemies; i++){
        enemyImg= LoadImage(imgFilename);
        ImageResize(&enemyImg, enemies[i].widht, enemies[i].height);
        enemies[i].texture= LoadTextureFromImage(enemyImg);
        UnloadImage(enemyImg);
    }
}

void deleteEnemy(Enemy** enemies, unsigned short int posDel, unsigned short int* nEnemies){
    //memmove( ((*enemies)+posDel), ((*enemies)+posDel+1), sizeof(Enemy)*((*nEnemies)-posDel));
    for(unsigned short int i=posDel; i<*nEnemies-1;i++){
        (*enemies)[i]=(*enemies)[i+1];
    }
    *nEnemies-=1;
    *enemies=(Enemy*)realloc(*enemies, (*nEnemies)*(sizeof(Enemy)));
}