#ifndef LASER_H_   
#define LASER_H_

#include<raylib.h>

#define maxNumOfPlayerLasers 50
#define maxNumOfEnemyLasers 15

typedef struct{
    short int rad;
    float x, y;
    short int speed;
    double angle;
    Texture2D texture;
}Laser;

void setLasers(Laser*, unsigned short int, const char*);
void deleteLaser(Laser*, unsigned short int*, unsigned short int);

#endif //LASER_H_