#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <list>
#include <math.h>
#include <cstring>
#define PI 3.14159265

using namespace sf;
using namespace std;

//Base class for physical objects in the game
class Entity
{
   public:
   //x,y refer to current pixel position in window, while xPos and yPos are positons relative to origin
   float x,y,xPos,yPos,w,h,dx,dy,R,angle;
   float absAngle;
   bool life = 1;
   std::string name;
   Sprite sprite;
   sf::IntRect rect;
   sf::RectangleShape rectangle;
   
   //sets up an object
   void settings(Sprite &a,float X,float Y, float W, float H, float Angle=0,int radius=1);
   
   //In case the object has no sprite and instead uses mathmatical graphics such as rectangle
   void noSpriteSettings(float X,float Y, float W, float H,  Color color, float Angle=0,int radius=1);
   
   //sets x and y
   void setPosition(float X, float Y);
   
   //self explanatory
   float getAngle();
   
   //checks if entity overlaps with Entity a
   bool isCollideRec(Entity *a);
   
   virtual void update();

   //displays to RenderWindow
   void draw(RenderWindow &app);

   virtual ~Entity();
};
