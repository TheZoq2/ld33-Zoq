#ifndef H_GAME
#define H_GAME

#include <vector>
#include <string>
#include <dirent.h>
#include <math.h>

#include <SFML/Graphics.hpp>

//#include "depend/dirent.h"

#include "engine/world.h"
#include "engine/spriteentity.h"
#include "engine/zui/window.h"
#include "engine/zui/textbutton.h"
#include "engine/zui/imglist.h"
#include "engine/mouseeventhandler.h"
#include "engine/line.h"
#include "engine/vec2f.h"
#include "engine/physicsentity.h"
#include "engine/ground.h"
#include "player.h"
#include "civilian.h"
#include "soldier.h"
#include "hidingspot.h"
#include "hidingspottemplate.h"

class Game
{
public:
    void setup();
    void loop();
    void cleanup();
    
    void updateWorld();
    
    bool isDone();

private:
    enum GameState
    {
    };
    bool done;

    sf::RenderWindow* window;

    World world;

    zui::Window mainUIWindow;
    MouseEventHandler mouseHandler;
    sf::View uiView;
    sf::View worldView;


    sf::Clock gameClock;
    sf::Time frameTime;
    sf::Time lastFrame;
    
    sf::Time lastWave;

    Player* player;

    void generateMap();
    void createTemplateHidingSpots();
    

    std::vector< std::shared_ptr<sf::Texture> > mapTextures;
    std::vector< HidingSpotTemplate > templateHidingSpots;

    void addMapTexture(std::string path);

    float getWorldHeight(float xPos);

    std::shared_ptr<sf::Texture> swordTexture;

    sf::Texture healthTexture;
    sf::Sprite healthSprite;
};

#endif
