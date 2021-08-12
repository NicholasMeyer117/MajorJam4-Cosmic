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
    int level = 1;
    int screenWidth;
    int screenHeight;
    sf::Text source;
    sf::Font gameFont;
    int redScore = 0;
    int blueScore = 0;
    //Character *character = new Character;
    std::vector<State*> stateList; //0=mainMenu, 1=Hub, 2=game, 3=Shop, 4=Settings)
    //std::array<Texture, 2> bulletTextureList;
    
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
        cout << "Red Scores!";
        redScore+=points;
    }
    
    void blueGetsPoints(int points) 
    {
        cout << "Blue Scores!" + to_string(points);
        blueScore+=points;
    }
    
    
    

};
