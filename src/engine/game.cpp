#include "game.h"


void Game::setup()
{
    this->window = new sf::RenderWindow(sf::VideoMode(1920,1080), "Test");
    done = false;
    worldView = window->getDefaultView();
    
    EntityGroup* mainGroup = this->world.getMainGroup();

    Platform* groundPlatform = new Platform();
    groundPlatform->addPoint(Vec2f(0,0));
    groundPlatform->addPoint(Vec2f(300,100));
    groundPlatform->addPoint(Vec2f(700,100));
    groundPlatform->addPoint(Vec2f(- 700,100));

    movingPlatform.addPoint(0,0);
    movingPlatform.addPoint(100,0);
    movingPlatform.addPoint(200,0);
    movingPlatform.setPosition(Vec2f(700, 100));

    mainGroup->addPlatform(groundPlatform);
    mainGroup->addPlatform(&movingPlatform);

    player = new Player(Vec2f(30,100));
    player->setPosition(Vec2f(5, -100));
    mainGroup->addEntity(player);

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
    


    if(moveDir)
    {
        movingPos += 30 * frameTime;

        if(movingPos > 300)
        {
            moveDir = false;
        }
    }
    else
    {
        movingPos -= 30 * frameTime;

        if(movingPos < -200)
        {
            moveDir = true;
        }

    }

    movingPlatform.setPosition(Vec2f(100, movingPos));

    window->setView(worldView);
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

EntityGroup* Game::generateForestBackground()
{
    EntityGroup* group = new EntityGroup();

    std::vector<std::string> images;
    images.push_back("../media/img/fir1.png");
    images.push_back("../media/img/fir2.png");
    //images.push_back("../media/img/fir3.png");

    std::vector< std::shared_ptr< sf::Texture > > textures;

    for(unsigned int i = 0; i < images.size(); i++)
    {
        textures.push_back(std::make_shared<sf::Texture>());
        textures.back()->loadFromFile(images.at(i));
    }
    
    const int size = 4000;
    const int objectDistance = 200;
    const float maxOffset = objectDistance / 4;
    const float minScale = 0.5;
    const float maxScale = 1.5;

    for(int i = 1; i < size / objectDistance; i++)
    {
        float posX = i * objectDistance + ((maxOffset * 2) * (rand() % 1000) / 1000.0) / 2;
        float posY = 100;

        float scale = minScale + (maxScale - minScale) * (rand() % 1000) / 1000.0;

        //Create a sprite entity 
        SpriteEntity* entity = new SpriteEntity();

        entity->create(textures.at(rand() % textures.size()));

        entity->setOrigin(Vec2f(0.5, 1));
        entity->setPosition(Vec2f(posX, posY));
        entity->setScale(Vec2f(scale, scale));
        entity->setDepth(rand() % 5);

        group->addEntity(entity);
    }

    return group;
}
