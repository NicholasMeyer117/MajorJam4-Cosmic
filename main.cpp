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
//#include "Character.h"
//#include "Enemy.h"
//#include "DarkFighter.h"
//#include "Bullets.h"
#include "Game.h"
#include "State.h"
#include "MenuState.h"
//#include "HubState.h"
//#include "PlayState.h"
//#include "ShopState.h"
//#include "Attachment.h"

using namespace sf;
using namespace std;
float DEGTORAD = 0.017453f;
const int screenW = 1920;
const int screenH = 1080;
    
sf::Text source;
sf::Font mainGameFont;

int main() {

    srand(time(NULL));
    std::vector<State*> stateList;
    Game *game = new Game;
    int state = 0;
    
    RenderWindow app(VideoMode(screenW, screenH), "Starknight!");
    app.setFramerateLimit(60);
    mainGameFont.loadFromFile("futura.ttf");
    source.setFont(mainGameFont);
    
    game->startGame(screenW, screenH, source, mainGameFont);
    
    MenuState *menuState = new MenuState;
    menuState -> createState(game);
    stateList.push_back(menuState);

    /*PlayState *playState = new PlayState;
    playState -> createState(game);
    stateList.push_back(playState);*/

    game->stateList = stateList;
    
    /*sf::Music music;
    if (!music.openFromFile("sounds/starknightTheme.wav"))
        return -1; // error
    music.play();
    music.setPlayingOffset(sf::seconds(.2f));
    music.setLoop(true);*/
    
    while (state >= 0)
    {
        state = stateList[state]->Run(app);
        //music.stop();
    }

    return 0;
}