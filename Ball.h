#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

class Ball: public Entity
{
    public:
    bool myTeam;
    bool pickedUp;
    sf::CircleShape circle;
    Vector2i ballLoc = Vector2i(0,0); 
    
    Ball(bool MyTeam, Vector2i loc)
    {
        myTeam = MyTeam;
        ballLoc = loc;
        pickedUp = false;
        
        circle.setRadius(10);
        circle.setPointCount(100);
        if (myTeam)
            circle.setFillColor(sf::Color::Blue);
        else
            circle.setFillColor(sf::Color::Red);
        circle.setOutlineColor(sf::Color::Black);
        circle.setOutlineThickness(1);
    }

    


};
