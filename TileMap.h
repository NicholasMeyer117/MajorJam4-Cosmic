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
//#include "TileMap.h"
#define PI 3.14159265

using namespace sf;
using namespace std;

class TileMap
{
    public:
    std::string tilemap;
    sf::RectangleShape rectangle;
    sf::CircleShape playerIcon;
    std::vector<RectangleShape> tileRectangles;
    vector<Ball> balls;
    enum direction {up, down, left, right};
    vector<vector<int>> map;
    int TileDim;
    Vector2f playerLoc = Vector2f(0,0); 
    
    
    void createMinimap(vector<vector<int>> Map, float mapDim, float xPos, float yPos);
    
    void addTile(int xTile, int yTile, int dim, int num, int mapDim, int tilePiece, int xCoord, int yCoord);
    
    int getTileElement(Vector2f coord);
    
    bool checkCanMove(Vector2f coord);
    
    bool isCollideBall(Vector2f coords, Ball ball);
    
    void updateMinimap(direction pDirection);
};
