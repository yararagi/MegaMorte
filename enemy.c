#include"enemy.h"

#include<stdlib.h>
#include<raylib.h>
#include<stdbool.h>
#include<string.h>
#include<math.h>

#include<stdio.h>

void setEnemy(Enemy * enemy, const char * imgFilename, bool setTexture){
    Image enemyImg;

    enemy->speed=200;
    enemy->nLasers=0;
    enemy->hp=100;
    enemy->width=45;
    enemy->height=45;
    enemy->clock=rand()%200;
    switch(rand()%3){
        case 0:
            enemy->x=0;
            enemy->y=rand()%GetScreenHeight();
            break;
        case 1:
            enemy->x=rand()%GetScreenWidth();
            enemy->y=0;
            break;
        case 2:
            enemy->x=GetScreenWidth();
            enemy->y=rand()%GetScreenHeight();
            break;
        default:
            break;
    }
    if(setTexture){
        enemyImg= LoadImage(imgFilename);
        ImageResize(&enemyImg, enemy->width, enemy->height);
        enemy->texture= LoadTextureFromImage(enemyImg);
        UnloadImage(enemyImg);
    }
}

void deleteEnemy(Enemy* enemies, unsigned short int posDel, unsigned short int* nEnemies){
    for(int i=posDel; i<*nEnemies-1;i++){
        enemies[i]=enemies[i+1];
    }
    setEnemy(&(enemies[*nEnemies]),"img/enemy.png" ,false);
    *nEnemies-=1;
}

void updateEnemy(Enemy *enemy, Vector2 playerPos){
    double ipotenusa, catetoX, catetoY;

    catetoX=playerPos.x-enemy->x;
    catetoY=playerPos.y-enemy->y;
    ipotenusa=sqrt(catetoX*catetoX + catetoY*catetoY);

    catetoX/=ipotenusa;
    catetoY/=ipotenusa;

    enemy->x+=GetFrameTime()*enemy->speed*catetoX;
    enemy->y+=GetFrameTime()*enemy->speed*catetoY;

    if(enemy->x>GetScreenWidth()){
        enemy->x=0;
    }else if(enemy->x<0){
        enemy->x=GetScreenWidth();
    }

    if(enemy->clock<=0){
        shootEnemyLaser(enemy, playerPos.y, catetoX);
        enemy->clock=100;
    }else{
        enemy->clock-=1;
    }
    
    updateEnemyLaser(enemy);
}

void shootEnemyLaser(Enemy *enemy, float playerY, float asseX){
    if(enemy->nLasers<maxNumOfEnemyLasers){    
        enemy->lasers[enemy->nLasers].x=enemy->x;
        enemy->lasers[enemy->nLasers].y=enemy->y;
        enemy->lasers[enemy->nLasers].angle=acos(asseX);
        if(enemy->y>playerY){ enemy->lasers[enemy->nLasers].angle*=-1; }
        enemy->nLasers+=1;
    }
}

void updateEnemyLaser(Enemy* enemy){
    for(unsigned short int i=0; i<enemy->nLasers; i++){
        enemy->lasers[i].x+=cos(enemy->lasers[i].angle)*enemy->lasers[i].speed*GetFrameTime();
        enemy->lasers[i].y+=sin(enemy->lasers[i].angle)*enemy->lasers[i].speed*GetFrameTime();

        if(enemy->lasers[i].x>GetScreenWidth() || enemy->lasers[i].x<0 || enemy->lasers[i].y>GetScreenHeight() || enemy->lasers[i].y<0){
            deleteLaser(enemy->lasers, &(enemy->nLasers), i);
        }
    }
}
