#include"laser.h"


void setLasers(Laser* lasers, unsigned short int nLaser, const char* imgFilename){
    Image lasersImg;
    lasersImg= LoadImage(imgFilename);
    ImageResize(&lasersImg, 12, 12);
    
    for(unsigned short int i=0; i<nLaser; i++){
        lasers[i].texture= LoadTextureFromImage(lasersImg);
        lasers[i].rad=12;
        lasers[i].speed=900;
    }
    
    UnloadImage(lasersImg);
}

void deleteLaser(Laser* laser, unsigned short int* nLaser, unsigned short int posDel){
    for(int i=posDel; i<*nLaser-1;i++){
        laser[i]=laser[i+1];
    }
    *nLaser-=1;
}