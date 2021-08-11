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
#define PI 3.14159265

using namespace sf;
using namespace std;

class TileMap : public sf::Drawable, public sf::Transformable
{
   public:
   bool thrust, collision, firstCollide= false;
   bool backThrust = false;
   bool beganThrust = false;
   float xVel,yVel,dx,dy, xDir, yDir, xPos, yPos, xSpeed, ySpeed, R,angle, maxSpeed, curSpeed, accelerationRate;
   int tileArray[400];

   void resetMap();

   bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, 
   unsigned int height, Entity ship, std::vector<Entity*> collidableEntities, bool movementLocked);
   
   private:

   virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
   sf::VertexArray m_vertices;
   sf::Texture m_tileset;

};
