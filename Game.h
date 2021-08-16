#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <list>
#include <math.h>
#include <cstring>
//#include "Character.h"
#include "Entity.h"
#include "Actor.h"
//#include "Enemy.h"
#include "State.h"
#define PI 3.14159265

class Game
{

    public:
    RenderWindow app;
    enum gameState {mainMenu, hub, game, shop, settings};
    int level = 0;
    int screenWidth;
    int screenHeight;
    sf::Text source;
    sf::Font gameFont;
    int redScore = 0;
    int blueScore = 0;
    int winScore = 0;
    std::vector<State*> stateList; //0=mainMenu, 1=Hub, 2=game, 3=Shop, 4=Settings)
    
    void resizeWindow();
    
    void startGame(int W, int H, sf::Text Source, sf::Font font)
    {
        source = Source;
        gameFont = font;
        screenWidth = W;
        screenHeight = H;
    }
    
    void changeState();
    
    void beginLevel()
    {
        redScore = 0;
        blueScore = 0;
    }
    
    void redGetsPoints(int points)
    {
        redScore+=points;
    }
    
    void blueGetsPoints(int points) 
    {
        blueScore+=points;
    }
    
    
    

};
