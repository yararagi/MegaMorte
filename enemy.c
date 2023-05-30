#include"enemy.h"

#include<stdlib.h>
#include<raylib.h>
#include<stdbool.h>
#include<string.h>
#include<math.h>

void setEnemy(Enemy * enemy, const char * imgFilename, bool setTexture){
    Image enemyImg;

    enemy->speedY=0;
    enemy->speedX=0;
    enemy->hp=150;
    enemy->width=45;
    enemy->height=45;
    enemy->clock=0;
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
    *nEnemies-=1;
}

void updateEnemy(Enemy *enemy){
    if(enemy->clock>10){

        if(enemy->clock==15){
                if(rand()%2==0){
                enemy->speedX=400;
            }else{
                enemy->speedX=-400;
            }

            if(rand()%2==0){
                enemy->speedY=400;
            }else{
                enemy->speedY=-400;
            }
        }

        enemy->x+=GetFrameTime()*enemy->speedX;
        enemy->y+=GetFrameTime()*enemy->speedY;
        
        if(enemy->y>GetScreenHeight()-100){
            enemy->speedY=-400;
        }else if(enemy->y<0){
            enemy->speedY=400;
        }

        if(enemy->x>GetScreenWidth()){
            enemy->x=0;
        }else if(enemy->x<0){
            enemy->x=GetScreenWidth();
        }

        
    }

    

    if(enemy->clock<=0){
        //fn shoot
        enemy->clock=30;
    }else{
        enemy->clock-=1;
    }
}