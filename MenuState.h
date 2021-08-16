#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <list>
#include <stdlib.h> 
#include <math.h>
#include <cstring>
#include "Game.h"
#include "State.h"
#include "Button.h"
#include "ParticleSystem.h"

class MenuState: public State
{
    public:
    std::vector<Button*> buttonList;
    int screenW;
    int screenH;
    sf::Font gameFont;
    sf::Font spaceFont;
    sf::Text source;
    sf::Text titleText;
    
    void createState(Game *game)
    {
        screenW = game->screenWidth;
        screenH = game->screenHeight;
        source = game->source;
        spaceFont.loadFromFile("pirulen.ttf");
        gameFont = game->gameFont;
        
    }
    
    int Run(sf::RenderWindow &app)
    {
        titleText.setFont(spaceFont);
        titleText.setString("Cosmoball");
        titleText.setCharacterSize(70);
        titleText.setFillColor(sf::Color::White);
        sf::FloatRect textRect = titleText.getLocalBounds();
        titleText.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
        titleText.setPosition(screenW/2, screenH/8);
        
        Button *startButton = new Button;
        startButton->createButton(screenW/2, 350, 400, 100, &gameFont, "START", 20); 
        buttonList.push_back(startButton);
        
        Button *settingsButton = new Button;
        settingsButton->createButton(screenW/2, 500, 400, 100, &gameFont, "HOW TO PLAY", 20); 
        buttonList.push_back(settingsButton);
        
        Button *creditsButton = new Button;
        creditsButton->createButton(screenW/2, 650, 400, 100, &gameFont, "CREDITS", 20); 
        buttonList.push_back(creditsButton);
        
        Button *quitButton = new Button;
        quitButton->createButton(screenW/2, 800, 400, 100, &gameFont, "QUIT", 20); 
        buttonList.push_back(quitButton);
        
        ParticleSystem backParticles1(400, 20000, 10, 100, 4, Color::White, 0, screenH/8, screenH, screenW, 0);
        ParticleSystem backParticles2(800, 20000, 10, 150, 4, Color::White, 0, screenH/8, screenH, screenW, 0, 200);
        ParticleSystem backParticles3(400, 20000, 10, 200, 4, Color::White, 0, screenH/8, screenH, screenW, 0, 100);
        sf::Clock clock;
        
        while (app.isOpen())
        {
            Event event;
            while (app.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    app.close();
                    
                else if (event.type == sf::Event::MouseButtonPressed) 
                {
                 
                    for (auto i:buttonList)
                    {
                        if (i -> visible == true and i->rect.contains(Mouse::getPosition(app).x, Mouse::getPosition(app).y) == true)
                        {
                            i->clicked = true;
                        }
                    }   
                }
            }
            
            if (buttonList[0]->clicked == true)
            {
                buttonList[0]->clicked = false;
                return 1;
            
            }
            else if (buttonList[1]->clicked == true)
            {
                buttonList[1]->clicked = false;
                return 2;
            
            }
            else if (buttonList[2]->clicked == true)
            {
                buttonList[2]->clicked = false;
                return 3;
            
            }
            else if (buttonList[3]->clicked == true)
            {
                buttonList[3]->clicked = false;
                return -1;
            
            }

            //draw
            app.clear(Color::Black);
            sf::Time elapsed = clock.restart();
            backParticles1.update(elapsed);
            backParticles2.update(elapsed);
            backParticles3.update(elapsed);
             
            app.draw(backParticles3);
            app.draw(backParticles2);
            app.draw(backParticles1);
            for(auto i:buttonList)
            {
                app.draw(i->rectangle);
                app.draw(i->buttonText);
            }
            app.draw(titleText);
            app.display();
        }
    
    
        return 0;
    }
};
