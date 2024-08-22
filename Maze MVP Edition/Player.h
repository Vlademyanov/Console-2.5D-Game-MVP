#ifndef _PLAYER_H
#define _PLAYER_H
#pragma once
#include "Point.h"
#define _USE_MATH_DEFINES
#include <math.h>


class Player {
public:
    Player();
    void setPosition(Point position) ;
    void setPositionX(double position) ;
    void setPositionY(double position) ;
    Point getPosition() ;

    void setDirectionView(float directionView) ;
    float getDirectionView() ;

    void setFOV(float FOV) ;
    float getFOV() ;

    void setDepthDisplay(float depthDisplay) ;
    float getDepthDisplay() ;

    void setCameraSpeed(float cameraSpeed) ;
    float getCameraSpeed() ;

    void setSpeed(float speed) ;
    float getSpeed() ;

    void setJump(float jump) ;
    float getJump() ;

    void setJumpFringle(float jumpFringle);
    float getJumpFringle();

private:
    int health;
    int attack;
    int currentHealth;
    float speed;
    Point position;
    float directionView;
    float FOV;
    float depthDisplay;
    float cameraSpeed;
    float jumpSize;
    float jumpFringleSize;
};


#endif // _PLAYER_H