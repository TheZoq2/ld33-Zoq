#include "game.h"


void Game::setup()
{
    this->window = new sf::RenderWindow(sf::VideoMode(1920,1080), "Test");
    done = false;
    worldView = window->getDefaultView();
    
    EntityGroup* mainGroup = world.getMainGroup();

    player = new Player(Vec2f(40, 100));
    player->setPosition(Vec2f(256, -256));
    mainGroup->addEntity(player);

    generateMap();
}

void Game::loop()
{
    float frameTime = (gameClock.getElapsedTime() - lastFrame).asSeconds();
    lastFrame = gameClock.getElapsedTime();


    //Handle window events
    sf::Event event;
    while(window->pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            window->close();
        }

        if(event.type == sf::Event::Resized)
        {
            //window->setSize(sf::Vector2<unsigned int>(width, height));
            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            sf::View view(visibleArea);
            uiView.reset(visibleArea);
            //view.setViewport(sf::FloatRect(0,0,1,1));
            //view.setSize(event.size.width, event.size.height);
            //window->setView(view);
        }
        if(event.type == sf::Event::MouseMoved)
        {
            mouseHandler.handleMoveEvent(&event);
        }
        if(event.type == sf::Event::MouseButtonPressed)
        {
            mouseHandler.handleMousePressed(&event);
        }
        if(event.type == sf::Event::MouseButtonReleased)
        {
            mouseHandler.handleMouseReleased(&event);
        }
    }

    //Redraw stuff
    window->clear(sf::Color::Black);
    

    window->setView(worldView);
    worldView.setCenter(player->getPosition());
    world.update(frameTime);
    world.draw(window, Vec2f(player->getPosition()));

    //sf::View view = window->getView();

    window->setView(uiView);
    uiView.setCenter(uiView.getSize().x / 2, uiView.getSize().y / 2);
    mainUIWindow.draw(window, Vec2f(0, 0));

    window->display();

    //Exit if the window has been closed
    if(window->isOpen() == false)
    {
        this->done = true;
        return;
    }
}
void Game::cleanup()
{
    delete window;
}

bool Game::isDone()
{
    return this->done;
}

////////////////////////////////////////////////////////////////////////////////
//                      Private methods
////////////////////////////////////////////////////////////////////////////////

void Game::generateMap()
{
    EntityGroup* mainGroup = this->world.getMainGroup();
    
    Platform* mainPlatform = new Platform();
    
    float platformStep = 128;

    unsigned int worldSize = 2000;
    

    float possibleAngles[] = {-M_PI/6, -M_PI/12, 0, M_PI / 12, M_PI / 6};
    int angleAmount = 5;
    int currentAngle = 3;
    Vec2f oldPos = Vec2f(0,0);

    for(unsigned int i = 0; i < worldSize; i++)
    {
        //seelecting a random angle
        float addedAngle = rand() % 3 - 1;
        currentAngle += addedAngle;
        
        if(currentAngle >= angleAmount)
        {
            currentAngle = 4;
        }
        else if(currentAngle < 0)
        {
            currentAngle = 1;
        }

        float angleResult = possibleAngles[currentAngle];

        float newHeight = platformStep * tan(angleResult);

        Vec2f newPos(oldPos.x + platformStep, oldPos.y + newHeight);

        mainPlatform->addPoint(newPos);

        oldPos = newPos;
    }
    
    mainGroup->addPlatform(mainPlatform);
}

