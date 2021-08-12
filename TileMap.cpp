#include "TileMap.h"

void TileMap::createMinimap(vector<vector<int>> Map, float mapDim, float xPos, float yPos)
{
    map = Map;
    rectangle.setSize(sf::Vector2f(mapDim, mapDim));
    rectangle.setOutlineColor(sf::Color::Black);
    rectangle.setOutlineThickness(-5);
    rectangle.setOrigin(mapDim/2, mapDim/2);
    rectangle.setPosition(xPos, yPos);
    
    playerIcon.setRadius((mapDim/map.size())/4);
    playerIcon.setPointCount(100);
    playerIcon.setFillColor(sf::Color::Green);
    playerIcon.setOutlineColor(sf::Color::Black);
    playerIcon.setOutlineThickness(2);
    playerIcon.setOrigin(playerIcon.getRadius(),playerIcon.getRadius());
    playerIcon.setPosition(xPos + ((map.size()/2 - 1) * (mapDim/map.size())) , yPos);
    
    //cout<<"\n" + to_string(sqrt(map.size())) + "\n";
    
    int tileXPos = xPos - mapDim/2;
    int tileYPos = yPos - mapDim/2;
    
    int tileNum = 0;
    int tileDim = mapDim/map.size();
    TileDim = tileDim;
    playerLoc = Vector2f(map.size() - 2,((map.size() - 1)/2));
    cout << "\n" + to_string(playerLoc.x) + ", " + to_string(playerLoc.y) + "\n";
    for (auto i = 0; i < map.size(); i++)
        for (auto j = 0; j < map.size(); j++)
        {
            addTile((tileXPos + (i * tileDim)),(tileYPos + (j * tileDim)), tileDim, tileNum, mapDim, map[j][i], i, j); 
            tileNum++;
        }
}
    
    void TileMap::addTile(int xTile, int yTile, int dim, int num,int mapDim, int tilePiece, int xCoord, int yCoord)
    {
        sf::RectangleShape tileRectangle;
        tileRectangle.setSize(sf::Vector2f(dim, dim));
        if (tilePiece == 1)
            tileRectangle.setFillColor(sf::Color(100, 50, 100, 255));
        else if (tilePiece == 2 or tilePiece == 4)
        {
            tileRectangle.setFillColor(sf::Color(255, 0, 0, 100));
            if (tilePiece == 2)
            {
                Ball ball(true, Vector2f(xCoord, yCoord));
                ball.circle.setOrigin(ball.circle.getRadius(), ball.circle.getRadius());
                ball.circle.setPosition(xTile + dim/2, yTile + dim/2);
                balls.push_back(ball);
            }
        }
        else if (tilePiece == 3 or tilePiece == 5)
        {
            tileRectangle.setFillColor(sf::Color(0, 0, 255, 100));
            if (tilePiece == 3)
            {
                Ball ball(false, Vector2f(xCoord, yCoord));
                ball.circle.setOrigin(ball.circle.getRadius(), ball.circle.getRadius());
                ball.circle.setPosition(xTile + dim/2, yTile + dim/2);
                balls.push_back(ball);
            }
        }
        tileRectangle.setOutlineColor(sf::Color::Black);
        tileRectangle.setOutlineThickness(-2);
        //tileRectangle.setOrigin(dim, dim);
        tileRectangle.setPosition(xTile, yTile);
        tileRectangles.push_back(tileRectangle);
    }
    
    int TileMap::getTileElement(Vector2f coord)
    {
        return map[coord.x][coord.y];
    }
    
    bool TileMap::checkCanMove(Vector2f coord)
    {
        if (getTileElement(coord) != 1)
        {
            return true;
        }
        return false;
    }
    
    bool TileMap::isCollideBall(Vector2f coords, Ball ball)
    {
        if (coords == ball.ballLoc)
            return true;
        return false;
    }
    
    void TileMap::updateMinimap(direction pDirection)
    {
        if (pDirection == up)
            playerIcon.move(0, -TileDim);
        else if (pDirection == down)
            playerIcon.move(0, TileDim);
        else if (pDirection == left)
            playerIcon.move(-TileDim, 0);
        else if (pDirection == right)
            playerIcon.move(TileDim, 0);
           
        for (int i = 0; i < balls.size(); i++)
        {
            if (isCollideBall(playerLoc, balls[i]) and balls[i].pickedUp == false)
            {
                balls[i].pickedUp = true;
                cout << "pickedUp";
            }
        }
        
        
        //playerIcon.setRotation(ship.getAngle());
        //playerIcon.setPosition(600 + (tilemap.xVel*-.001), 400 + (tilemap.yVel*-.001));
    }
