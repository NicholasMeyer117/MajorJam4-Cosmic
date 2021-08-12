#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <list>
#include <stdlib.h> 
#include <math.h>
#include <cstring>
#include "Entity.h"
#include "Button.h"
#include "Actor.h"
#include "unistd.h"
//#include "Character.h"
//#include "Enemy.h"
//#include "DarkFighter.h"
//#include "Bullets.h"
//#include "EnemySpawner.h"
#include "Game.h"
#include "State.h"
#include "MenuState.h"
#include "TileMap.h"
//#include "HubState.h"
//#include "Attachment.h"
//#include "EnergyShield.h"
//#include "ProgressBar.h"
//#include "ParticleSystem.h"

class PlayState: public State
{
    public:
    std::vector<Button*> buttonList;
    std::vector<Entity*> entities;
    std::vector<Actor*> bluePlayers;
    std::vector<Actor*> redPlayers;
    std::vector<Actor*> allPlayers;
    
    Game *curGame;
    int screenW;
    int screenH;
    sf::Font gameFont;
    sf::Text source;
    
    void createState(Game *game)
    {
        screenW = game->screenWidth;
        screenH = game->screenHeight;
        source = game->source;
        gameFont = game->gameFont;
        curGame = game;
    
    }
    
    void emptyState()
    {
        /*buttonList.clear();
        entities.clear();
        collidableEntities.clear();
        creditList.clear();
        listButtons.clear();
        enemyList.clear();
        bulletList.clear();
        enemyBulletList.clear();
        enemySpriteList.clear();
        bulletSpriteList.clear();*/
    
    }

    void drawText( const sf::String &str, const int Size, const float xposition, const float yposition, sf::RenderWindow& window)
    {
        source.setString(str);
        source.setCharacterSize(Size); //only the lower cased word size is reserved. A capital S fixes that.
        source.setPosition(xposition,yposition);
        source.setFillColor(Color::White);
        window.draw(source);
    }
    
    void takeTurn ()
    {
    
    }
    
    void updatePlayers(TileMap *map)
    {
        for (auto i:redPlayers)
        {
            map->checkActor(i);
            if (map->isReturnBalls(i))
            {
                cout << "bitch";
                curGame->redGetsPoints(i->balls);
                map->resetBalls(i);
                i->dropBalls();
            }
        }
    }
    
    
    int Run(sf::RenderWindow &app)
    {
	/*Texture p1,p2,p3,p4,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12;
        p1.loadFromFile("images/triShip.png");*/
        
        //Sprite background(t2);
        /*Sprite warhorse(p1);
        playerShipSpriteList.push_back(warhorse);*/
    
        bool performTurn = false;
        bool waiting = false;
        int tick = 0;
        int playerScore = 0;
        int enemyScore = 0;
        TileMap::direction pDirection;
        
        vector<vector<int>> level =
        {
            {1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 5, 0, 0, 0, 0, 0, 4, 1},
            {1, 0, 1, 1, 0, 1, 1, 0, 1},
            {1, 0, 1, 2, 0, 3, 1, 0, 1},
            {1, 5, 0, 0, 1, 0, 0, 4, 1},
            {1, 0, 1, 2, 0, 3, 1, 0, 1},
            {1, 0, 1, 1, 0, 1, 1, 0, 1},
            {1, 5, 0, 0, 0, 0, 0, 4, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1},

        };
        
        Actor player(true, true, Vector2f(7, 4));
        redPlayers.push_back(&player);
        allPlayers.push_back(&player);
        
        Actor blue1(false, false, Vector2f(1, 4));
        bluePlayers.push_back(&blue1);
        allPlayers.push_back(&blue1);
        
        TileMap *map = new TileMap();
        map -> createMinimap(level,screenW/4,screenW/2, screenH/2, allPlayers);

        while (app.isOpen())
        {

            Event event;
            while (app.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    app.close();
                
                /*if (event.type == Event::KeyPressed)
                {
                     if (event.key.code == Keyboard::Space)
                     {
                   
                     }
             
                 }*/
            }
        
            //Player Movement
	         
	     //Quit Game
	     if (Keyboard::isKeyPressed(Keyboard::Q))
	         return -1;
	   
	     if (Keyboard::isKeyPressed(Keyboard::W) and !waiting)
	     {
	         cout<<"\nPlayerLoc: " + to_string(player.coords.x) + ", " + to_string(player.coords.y) + "\n";
	         cout<<"\nPlayerLoc: " + to_string(player.coords.x) + ", " + to_string(player.coords.y - 1) + "\n\n";
	         if(map->checkCanMove(Vector2f(player.coords.x, player.coords.y - 1)))
	         {
	             performTurn = true;
	             pDirection = TileMap::direction::up; 
	             player.coords = Vector2f(player.coords.x, player.coords.y - 1);
	         }
	     }   
	     else if (Keyboard::isKeyPressed(Keyboard::S) and !waiting)
	     {
	         cout<<"\nPlayerLoc: " + to_string(map->playerLoc.x) + ", " + to_string(map->playerLoc.y) + "\n";
	         cout<<"\nPlayerLoc: " + to_string(map->playerLoc.x) + ", " + to_string(map->playerLoc.y + 1) + "\n\n";
	         if(map->checkCanMove(Vector2f(player.coords.x, player.coords.y + 1)))
	         {
	             performTurn = true;
	             pDirection = TileMap::direction::down; 
	             player.coords = Vector2f(player.coords.x, player.coords.y + 1);
	         }            
	     }   
	     else if (Keyboard::isKeyPressed(Keyboard::A) and !waiting)
	     {
	         cout<<"\nPlayerLoc: " + to_string(map->playerLoc.x) + ", " + to_string(map->playerLoc.y) + "\n";
	         cout<<"\nPlayerLoc: " + to_string(map->playerLoc.x - 1) + ", " + to_string(map->playerLoc.y) + "\n\n";
	         if(map->checkCanMove(Vector2f(player.coords.x - 1, player.coords.y)))
	         {
	             performTurn = true;
	             pDirection = TileMap::direction::left; 
	             player.coords = Vector2f(player.coords.x - 1, player.coords.y);
	         }            
	     }     
	     else if (Keyboard::isKeyPressed(Keyboard::D) and !waiting)
	     {
	         cout<<"\nPlayerLoc: " + to_string(map->playerLoc.x) + ", " + to_string(map->playerLoc.y) + "\n";
	         cout<<"\nPlayerLoc: " + to_string(map->playerLoc.x + 1) + ", " + to_string(map->playerLoc.y) + "\n\n";
	         if(map->checkCanMove(Vector2f(player.coords.x + 1, player.coords.y)))
	         {
	             performTurn = true;
	             pDirection = TileMap::direction::right; 
	             player.coords = Vector2f(player.coords.x + 1, player.coords.y);
	         }          
	     }  
         
             if (performTurn and !waiting)
             {
                 performTurn = false;
                 waiting = true;
                 tick = 0;
                 takeTurn();
                 map->updateMinimap(pDirection);
                 updatePlayers(map);
                 
                 
             }
             
             if(waiting)
             {
                 tick++;
                 if (tick == 15)
                     waiting = false;
             }
             

            //map->updateMinimap(*m, *p);
            app.draw(map -> rectangle);
            for(auto i:(map -> tileRectangles)) app.draw(i);
            for(auto i:map->balls)
            {
                if (i.pickedUp == false)
                    app.draw(i.circle);
            }
            for(auto i:(map -> playerIcons)) app.draw(i);
            
            drawText("Red Team: " + std::to_string(curGame->redScore), 40, screenW - screenW/3, screenH/8, app);
            drawText("Blue Team: " + std::to_string(curGame->blueScore), 40, screenW/5, screenH/8, app);
            app.display();
            app.clear(Color::Black);
        }
    
    
    
        return -1;
    }

    
    
};
