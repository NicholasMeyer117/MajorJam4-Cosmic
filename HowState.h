class HowState: public State
{
    public:
    int screenW;
    int screenH;
    sf::Font gameFont;
    sf::Font spaceFont;
    sf::Text source;
    sf::Text titleText;
    std::vector<Button*> buttonList;
    
    void createState(Game *game)
    {
        screenW = game->screenWidth;
        screenH = game->screenHeight;
        source = game->source;
        spaceFont.loadFromFile("futura.ttf");
        gameFont = game->gameFont;
        
    }
    
    int Run(sf::RenderWindow &app)
    {
        titleText.setFont(spaceFont);
        titleText.setString("How To Play");
        titleText.setCharacterSize(70);
        titleText.setFillColor(sf::Color::Black);
        sf::FloatRect textRect = titleText.getLocalBounds();
        titleText.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
        titleText.setPosition(screenW/2, screenH/8);
        
        /*Button *startButton = new Button;
        startButton->createButton(screenW/2, 350, 400, 100, &gameFont, "START", 20); 
        buttonList.push_back(startButton);
        
        Button *settingsButton = new Button;
        settingsButton->createButton(screenW/2, 500, 400, 100, &gameFont, "SETTINGS", 20); 
        buttonList.push_back(settingsButton);
        
        Button *creditsButton = new Button;
        creditsButton->createButton(screenW/2, 650, 400, 100, &gameFont, "CREDITS", 20); 
        buttonList.push_back(creditsButton);*/
        
        Button *backButton = new Button;
        backButton->createButton(screenW/2, 800, 400, 100, &gameFont, "BACK", 20); 
        buttonList.push_back(backButton);
        
        while (app.isOpen())
        {
            Event event;
            while (app.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    app.close();
                    
                else if (event.type == sf::Event::MouseButtonPressed) 
                {
                 
                    std::cout << "Mouse Position on Screen: " + to_string(Mouse::getPosition(app).x) + " , " + to_string(Mouse::getPosition(app).y) << std::endl;
                    for (auto i:buttonList)
                    {
                        if (i -> visible == true and i->rect.contains(Mouse::getPosition(app).x, Mouse::getPosition(app).y) == true)
                        {
                            i->clicked = true;
                            cout << "click!";
                        }
                    }   
                }
            }
            
            if (backButton->clicked == true)
            {
                backButton->clicked = false;
                return 0;
            
            }

            //draw
            app.clear(Color(255,255,255,255));
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
