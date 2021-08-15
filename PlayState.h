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
#include "Game.h"
#include "State.h"
#include "MenuState.h"
#include "TileMap.h"
#include "ParticleSystem.h"

class PlayState: public State
{
    public:
    std::vector<Button*> buttonList;
    std::vector<Entity*> entities;
    std::vector<Actor*> bluePlayers;
    std::vector<Actor*> redPlayers;
    std::vector<Actor*> allPlayers;
    vector<vector<vector<int>>> levels;
    Actor player;
    
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
    
    bool levelComplete (int level)
    {
        switch(level)
        {
            case 0:
                if (curGame->blueScore >= 5)
                    return true;
                else if (curGame->redScore  >= 5)
                    return true;
                else
                    break;
            case 1:
                if (curGame->blueScore >= 10)
                    return true;
                else if (curGame->redScore  >= 10)
                    return true;
                else
                    break; 
            case 2:
                if (curGame->blueScore >= 20)
                    return true;
                else if (curGame->redScore  >= 20)
                    return true;
                else
                    break;   
        
        }
        return false;
    }
    
    void createLevel(TileMap *map)
    {
        redPlayers.clear();
        bluePlayers.clear();
        allPlayers.clear();
        player.balls = 0;
    
        switch (curGame->level)
        {
            case 0:
            {
                curGame->redScore = 0;
                curGame->blueScore = 0;
        
                player.coords = Vector2i(7, 4);
                redPlayers.push_back(&player);
                allPlayers.push_back(&player);
                
                Actor *blue1 = new Actor;
                blue1->createActor(false, false, Vector2i(1, 4));
                bluePlayers.push_back(blue1);
                allPlayers.push_back(blue1);
                break;
            }
            case 1:
            {
                curGame->redScore = 0;
                curGame->blueScore = 0;
                
                player.coords = Vector2i(11, 1);
                redPlayers.push_back(&player);
                allPlayers.push_back(&player);
                
                Actor *red1 = new Actor;
                red1->createActor(true, false, Vector2i(11, 11));
                redPlayers.push_back(red1);
                allPlayers.push_back(red1);
                
                Actor *blue1 = new Actor;
                blue1->createActor(false, false, Vector2i(1, 11));
                bluePlayers.push_back(blue1);
                allPlayers.push_back(blue1);
                
                Actor *blue2 = new Actor;
                blue2->createActor(false, false, Vector2i(1, 1));
                bluePlayers.push_back(blue2);
                allPlayers.push_back(blue2);
                break;
            }
            case 2:
            {
                curGame->redScore = 5;
                curGame->blueScore = 0;
                
                player.coords = Vector2i(11, 1);
                redPlayers.push_back(&player);
                allPlayers.push_back(&player);
                
                Actor *red1 = new Actor;
                red1->createActor(true, false, Vector2i(11, 11));
                redPlayers.push_back(red1);
                allPlayers.push_back(red1);
                
                Actor *blue1 = new Actor;
                blue1->createActor(false, false, Vector2i(1, 1));
                bluePlayers.push_back(blue1);
                allPlayers.push_back(blue1);
                
                Actor *blue2 = new Actor;
                blue2->createActor(false, false, Vector2i(1, 6));
                bluePlayers.push_back(blue2);
                allPlayers.push_back(blue2);
                
                Actor *blue3 = new Actor;
                blue3->createActor(false, false, Vector2i(1, 11));
                bluePlayers.push_back(blue3);
                allPlayers.push_back(blue3);
                
                break;
            }
        }
        
        
        
        int mapDim = screenW/36 * levels[curGame->level].size();
        map -> createMinimap(levels[curGame->level],mapDim,screenW/2, screenH/2, allPlayers);
    }
    
    bool updatePlayers(TileMap *map)
    {
        for (int i = 1; i < allPlayers.size(); i++)
        {
            TileMap::direction dir = map->nextMove(allPlayers[i]);
            map->updateMinimap(dir, i);
        }
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
        for (auto i:bluePlayers)
        {
            map->checkActor(i);
            if (map->checkLineOfSight(i->coords, i->dir))
                if (player.balls > 1)
                {
                    cout<<"Player Caught!";
                    return true;
                }
            if (map->isReturnBalls(i))
            {
                cout << "bitch";
                curGame->blueGetsPoints(i->balls);
                map->resetBalls(i);
                i->dropBalls();
            }
        }
        return false;
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
        bool caught = false;
        int tick = 0;
        int playerScore = 0;
        int enemyScore = 0;
        TileMap::direction pDirection;
        
        ParticleSystem backParticles1(400, 20000, 10, 100, 4, Color::White, 0, screenH/8, screenH, screenW, 0);
        ParticleSystem backParticles2(800, 20000, 10, 150, 4, Color::White, 0, screenH/8, screenH, screenW, 0, 200);
        ParticleSystem backParticles3(400, 20000, 10, 200, 4, Color::White, 0, screenH/8, screenH, screenW, 0, 100);
        sf::Clock clock;
        
        vector<vector<int>> level1 =
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
        levels.push_back(level1);
        
        vector<vector<int>> level2 =
        {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 1},
            {1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1},
            {1, 0, 1, 2, 1, 0, 1, 0, 1, 3, 1, 0, 1},
            {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
            {1, 0, 0, 0, 0, 1, 3, 1, 0, 0, 0, 0, 1},
            {1, 5, 0, 0, 0, 1, 1, 1, 0, 0, 0, 4, 1},
            {1, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 1},
            {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
            {1, 0, 1, 2, 1, 0, 1, 0, 1, 3, 1, 0, 1},
            {1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1},
            {1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},

        };
        levels.push_back(level2);
        
        vector<vector<int>> level3 =
        {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 5, 0, 2, 1, 0, 0, 0, 1, 3, 0, 4, 1},
            {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
            {1, 0, 0, 1, 0, 2, 1, 3, 0, 1, 0, 0, 1},
            {1, 5, 0, 0, 0, 1, 1, 1, 0, 0, 0, 4, 1},
            {1, 0, 0, 1, 0, 2, 1, 3, 0, 1, 0, 0, 1},
            {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
            {1, 5, 0, 2, 1, 0, 0, 0, 1, 3, 0, 4, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        };
        levels.push_back(level3);
        
       // player = Player(true, true, Vector2i(7, 4));
        
         player.createActor(true, true, Vector2i(7, 4));
        
        TileMap *map = new TileMap();
        createLevel(map);
        //map -> createMinimap(levels[curGame->level],screenW/4,screenW/2, screenH/2, allPlayers);

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
	   
	     if (Keyboard::isKeyPressed(Keyboard::W) and !waiting and !caught)
	     {
	         //cout<<"\nPlayerLoc: " + to_string(player.coords.x) + ", " + to_string(player.coords.y) + "\n";
	         //cout<<"\nPlayerLoc: " + to_string(player.coords.x) + ", " + to_string(player.coords.y - 1) + "\n\n";
	         if(map->checkCanMove(Vector2i(player.coords.x, player.coords.y - 1)))
	         {
	             performTurn = true;
	             pDirection = TileMap::direction::up; 
	             player.coords = Vector2i(player.coords.x, player.coords.y - 1);
	         }
	     }   
	     else if (Keyboard::isKeyPressed(Keyboard::S) and !waiting and !caught)
	     {
	         //cout<<"\nPlayerLoc: " + to_string(map->playerLoc.x) + ", " + to_string(map->playerLoc.y) + "\n";
	         //cout<<"\nPlayerLoc: " + to_string(map->playerLoc.x) + ", " + to_string(map->playerLoc.y + 1) + "\n\n";
	         if(map->checkCanMove(Vector2i(player.coords.x, player.coords.y + 1)))
	         {
	             performTurn = true;
	             pDirection = TileMap::direction::down; 
	             player.coords = Vector2i(player.coords.x, player.coords.y + 1);
	         }            
	     }   
	     else if (Keyboard::isKeyPressed(Keyboard::A) and !waiting and !caught)
	     {
	         //cout<<"\nPlayerLoc: " + to_string(map->playerLoc.x) + ", " + to_string(map->playerLoc.y) + "\n";
	         //cout<<"\nPlayerLoc: " + to_string(map->playerLoc.x - 1) + ", " + to_string(map->playerLoc.y) + "\n\n";
	         if(map->checkCanMove(Vector2i(player.coords.x - 1, player.coords.y)))
	         {
	             performTurn = true;
	             pDirection = TileMap::direction::left; 
	             player.coords = Vector2i(player.coords.x - 1, player.coords.y);
	         }            
	     }     
	     else if (Keyboard::isKeyPressed(Keyboard::D) and !waiting and !caught)
	     {
	         //cout<<"\nPlayerLoc: " + to_string(map->playerLoc.x) + ", " + to_string(map->playerLoc.y) + "\n";
	         //cout<<"\nPlayerLoc: " + to_string(map->playerLoc.x + 1) + ", " + to_string(map->playerLoc.y) + "\n\n";
	         if(map->checkCanMove(Vector2i(player.coords.x + 1, player.coords.y)))
	         {
	             performTurn = true;
	             pDirection = TileMap::direction::right; 
	             player.coords = Vector2i(player.coords.x + 1, player.coords.y);
	         }          
	     } 
	     else if (Keyboard::isKeyPressed(Keyboard::Space) and !waiting and !caught)
	     {
	         performTurn = true;
	         pDirection = TileMap::direction::hold;
	     }
         
             if (performTurn and !waiting)
             {
                 performTurn = false;
                 waiting = true;
                 tick = 0;
                 map->playerLoc = player.coords;
                 map->updateMinimap(pDirection, 0);
                 caught = updatePlayers(map);
                 if (levelComplete(curGame->level) and curGame->blueScore < curGame->redScore)
                 {
                     curGame->level++;
                     createLevel(map);
                 }
                 
                 
             }
             
             if(waiting)
             {
                 tick++;
                 if (tick == 15)
                     waiting = false;
             }
             
             sf::Time elapsed = clock.restart();
             backParticles1.update(elapsed);
             backParticles2.update(elapsed);
             backParticles3.update(elapsed);
             

            //map->updateMinimap(*m, *p);
            app.draw(backParticles3);
            app.draw(backParticles2);
            app.draw(backParticles1);
            
            app.draw(map -> rectangle);
            for(auto i:(map -> tileRectangles)) app.draw(i);
            for(auto i:map->balls)
            {
                if (i.pickedUp == false)
                    app.draw(i.circle);
            }
            for(auto i:(map -> playerIcons)) app.draw(i);
            
            drawText("Red Team: " + std::to_string(curGame->redScore), 40, screenW - screenW/5, screenH/8, app);
            drawText("Blue Team: " + std::to_string(curGame->blueScore), 40, screenW/10, screenH/8, app);
            if (curGame->level == 0)
            {
                drawText("Level: " + std::to_string(curGame->level) + "\n  1 v 1", 40, screenW/2 - screenW/20, 0, app);
            }
            else if (curGame->level == 1)
            {
                drawText("Level: " + std::to_string(curGame->level) + "\n  2 v 2", 40, screenW/2 - screenW/20, 0, app);
            }
            else if (curGame->level == 2)
            {
                drawText("Level: " + std::to_string(curGame->level) + "\n  3 v 2\n Red +5", 40, screenW/2 - screenW/20, 0, app);
            }
            if (caught)
            {
                
                Button restartButton;
                restartButton.createButton(screenW/2, screenH/6, 450, 100, &gameFont, "        CAUGHT!\nClick to restart level", 20); 
                restartButton.rectangle.setOutlineColor(Color::Blue);
                restartButton.rectangle.setOutlineThickness(10);
                app.draw(restartButton.rectangle);
                app.draw(restartButton.buttonText);
                
                if (event.type == sf::Event::MouseButtonPressed and restartButton.rect.contains(Mouse::getPosition(app).x, Mouse::getPosition(app).y))
                {
                    caught = false;
                    createLevel(map);
                }
            }
            app.display();
            app.clear(Color::Black);
        }
    
    
    
        return -1;
    }

    
    
};
