#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <list>
#include <math.h>
#include <cstring>
#include "Entity.h"
#include "Ball.h"
#define PI 3.14159265

//An Entity that moves and acts on in dynamic ways
class Actor: public Entity
{
    public:
    bool myTeam;
    bool isPlayer;
    int balls = 0;
    vector<Ball*> ballList;
    Vector2f coords;
    
    Actor(bool MyTeam, bool IsPlayer, Vector2f Coords)
    {
        myTeam = MyTeam;
        isPlayer = IsPlayer;
        coords = Coords;
    }
    
    void dropBalls()
    {
        balls = 0;
    }
    
    void grabBall()
    {
        balls++;
    }

};
