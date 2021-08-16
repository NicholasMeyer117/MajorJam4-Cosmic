class CreditsState: public State
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
    
    void drawText( const sf::String &str, const int Size, const float xposition, const float yposition, sf::RenderWindow& window)
    {
        source.setString(str);
        source.setCharacterSize(Size); //only the lower cased word size is reserved. A capital S fixes that.
        source.setPosition(xposition,yposition);
        source.setFillColor(Color::Black);
        window.draw(source);
    }
    
    int Run(sf::RenderWindow &app)
    {
        titleText.setFont(spaceFont);
        titleText.setString("Credits");
        titleText.setCharacterSize(70);
        titleText.setFillColor(sf::Color::Black);
        sf::FloatRect textRect = titleText.getLocalBounds();
        titleText.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
        titleText.setPosition(screenW/2, screenH/8);
        
        Button *backButton = new Button;
        backButton->createButton(screenW/2, screenH - screenH/16, 400, 100, &gameFont, "BACK", 20); 
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
            drawText("This is you:\n\nThese are your teammates:\n\nThese are enemy players:\n\n"
            "These are your teams balls:\n\nThese are the enemy teams balls:", 25, 0 + screenW/32, 0 + screenH/5, app);
            drawText("Welcome to Cosmoball! The game of the future!\n\n"
            "The objective of the game is to score more points than the other team by gathering balls\n\n"
            "and bringing them back to your team's goals. Each teams goals are located on their side\n\n"
            "of the field. Balls are located in various areas between each side. Each player is only\n\n"
            "allowed to carry ONE BALL. Carrying more than one ball is CHEATING! so make sure to\n\n"
            "NEVER carry more than one. If an enemy player spots you (in their line of sight),\n\n" 
            "you will be disqualified. The game is turn based and the team that makes it to the\n\n"
            "specified score first wins the match. Good luck and DON'T CHEAT", 25, 0 + screenW/3, 0 + screenH/5, app);
            app.draw(titleText);
            app.display();
        }
    
    
        return 0;
    }
};
