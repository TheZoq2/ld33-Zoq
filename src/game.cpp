#include "game.h"


void Game::setup()
{
    //Setting the random seed
    srand(time(NULL));
    this->window = new sf::RenderWindow(sf::VideoMode(1920,1080), "Test");
    done = false;
    worldView = window->getDefaultView();
    worldView.zoom(1.3);
    
    EntityGroup* mainGroup = world.getMainGroup();

    player = new Player(Vec2f(40, 100));
    player->setPosition(Vec2f(256, -256));
    mainGroup->addEntity(player);

    //Adding a couple of test civilians
    Civilian* testCiv1 = new Civilian(Vec2f(30, 90), player);
    testCiv1->setPosition(Vec2f(1000, -300));
    Civilian* testCiv2 = new Civilian(Vec2f(30, 90), player);
    testCiv2->setPosition(Vec2f(1000, -300));
    Civilian* testCiv3 = new Civilian(Vec2f(30, 90), player);
    testCiv3->setPosition(Vec2f(1000, -300));
    Civilian* testCiv4 = new Civilian(Vec2f(30, 90), player);
    testCiv4->setPosition(Vec2f(1000, -300));

    mainGroup->addEntity(testCiv1);
    mainGroup->addEntity(testCiv2);
    mainGroup->addEntity(testCiv3);
    mainGroup->addEntity(testCiv4);

    Soldier* testSoldier = new Soldier(Vec2f(30,80), player);
    testSoldier->setPosition(Vec2f(1000, -200));

    mainGroup->addEntity(testSoldier);

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
    createTemplateHidingSpots();
    EntityGroup* mainGroup = this->world.getMainGroup();
    
    Platform* mainPlatform = new Platform();
    
    float platformStep = 128;

    unsigned int worldSize = 2000;
    

    addMapTexture("../media/img/pi6grassTile.png");
    addMapTexture("../media/img/pi12grassTile.png");
    addMapTexture("../media/img/grassTile.png");
    addMapTexture("../media/img/grassTile.png");
    addMapTexture("../media/img/mpi12grassTile.png");
    addMapTexture("../media/img/mpi6grassTile.png");

    float possibleAngles[] = {-M_PI/6, -M_PI/12, 0, 0, M_PI / 12, M_PI / 6};
    int angleAmount = 6;
    int currentAngle = 3;
    Vec2f oldPos = Vec2f(0,0);

    int hidingSpotOdds = 10;
    int hidingSpotAmount = 2;

    mainPlatform->addPoint(oldPos);

    for(unsigned int i = 0; i < worldSize; i++)
    {
        //seelecting a random angle
        float addedAngle = rand() % 3 - 1;
        currentAngle += addedAngle;
        
        if(currentAngle >= angleAmount)
        {
            currentAngle = angleAmount - 1;
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

        //Creating the tile entities.
        SpriteEntity* newSprite = new SpriteEntity();
        newSprite->create(mapTextures[currentAngle]);
        newSprite->setScale(Vec2f(4, 4));
        newSprite->setPosition(Vec2f(newPos.x - platformStep, newPos.y - platformStep - newHeight));
        newSprite->setDepth(1);
        mainGroup->addEntity(newSprite);

        if(rand()%100 < hidingSpotOdds)
        {
            HidingSpotTemplate templateSpot = templateHidingSpots[rand() % hidingSpotAmount];
            HidingSpot* newSpot = new HidingSpot();
            newSpot->create(templateSpot.defaultTexture, templateSpot.hiddenTexture);
            newSpot->setScale(templateSpot.scale);
            newSpot->setOrigin(templateSpot.origin);

            newSpot->setPosition(newPos);

            mainGroup->addEntity(newSpot);
        }
    }
    
    mainGroup->addPlatform(mainPlatform);
    

}

void Game::addMapTexture(std::string path)
{
    sf::Texture* newTexture = new sf::Texture;

    newTexture->loadFromFile(path);

    mapTextures.push_back(std::shared_ptr<sf::Texture>(newTexture));
}

void Game::createTemplateHidingSpots()
{
    templateHidingSpots.push_back(HidingSpotTemplate(
                "../media/img/pine1.png",
                "../media/img/pine1_hidden.png",
                Vec2f(0.5, 0.9),
                Vec2f(4,4)
                ));
    templateHidingSpots.push_back(HidingSpotTemplate(
                "../media/img/well.png",
                "../media/img/well_hidden.png",
                Vec2f(0.5, 0.75),
                Vec2f(4,4)
                ));
}
