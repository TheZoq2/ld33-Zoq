#include "game.h"

void Game::setup()
{
    //Setting the random seed
    srand(time(NULL));
    this->window = new sf::RenderWindow(sf::VideoMode(1920,1080), "Test");
    done = false;
    worldView = window->getDefaultView();
    worldView.zoom(1.3);

    generateMap();
    
    EntityGroup* mainGroup = world.getMainGroup();

    player = new Player(Vec2f(40, 100));
    player->setPosition(Vec2f(10000, getWorldHeight(10000) - 100));
    mainGroup->addEntity(player);

    swordTexture = std::make_shared<sf::Texture>();

    swordTexture->loadFromFile("../media/img/sword.png");
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
    window->clear(sf::Color(135,206,235));
    

    window->setView(worldView);
    worldView.setCenter(player->getPosition());
    updateWorld();
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

void Game::updateWorld()
{
    const float despawnDistance = 1500;
    const float spawnDistance = 1000;
    const int maxCivs = 20;
    const int maxSoldiers = 10;

    EntityGroup* mainGroup = world.getMainGroup();
    //Count how many people are in the world
    std::vector<Entity*> entities = mainGroup->getEntities();

    //std::cout << "Entity amount " << entities.size() << std::endl;


    if(gameClock.getElapsedTime() - lastWave > sf::seconds(5))
    {
        lastWave = gameClock.getElapsedTime();
        int civAmount = 0;
        int soldierAmount = 0;

        for(auto it : entities)
        {
            float playerDistance = it->getPosition().x - player->getPosition().x;

            Civilian* civilian = dynamic_cast<Civilian*>(it);
            if(civilian != nullptr)
            {
                if(std::abs(playerDistance) > despawnDistance)
                {
                    civilian->setDone(true);

                    //std::cout << it->getPosition().x << "    " << player->getPosition().x << std::endl;
                }
                else
                {
                    civAmount++;
                }
            }

            Soldier* soldier = dynamic_cast<Soldier*>(it);
            if(soldier != nullptr)
            {
                if(std::abs(playerDistance) > despawnDistance)
                {
                    soldier->setDone(true);
                }
                else
                {
                    soldierAmount++;
                }
            }
        }

        if(civAmount < maxCivs)
        {
            //Spawn some new civilians
            for(int i = 0; i < maxCivs - civAmount; i++)
            {
                Civilian* civilian = new Civilian(Vec2f(30,90), player);

                float xPos = player->getPosition().x + spawnDistance;
                if(rand() % 2 == 1)
                {
                    xPos = player->getPosition().x - spawnDistance;
                }
                civilian->setPosition(Vec2f(xPos, getWorldHeight(xPos) - 200));
                mainGroup->addEntity(civilian);
            }
        }
        if(soldierAmount < maxSoldiers)
        {
            //Spawn some new civilians
            for(int i = 0; i < maxSoldiers - soldierAmount; i++)
            {
                Soldier* soldier = new Soldier(Vec2f(30,90), player);

                float xPos = player->getPosition().x + spawnDistance;
                if(rand() % 2 == 1)
                {
                    xPos = player->getPosition().x - spawnDistance;
                }
                soldier->setPosition(Vec2f(xPos, getWorldHeight(xPos) - 200));
                soldier->setSwordTexture(swordTexture);
                mainGroup->addEntity(soldier);
            }
        }
    } //End waves
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

    unsigned int worldSize = 1000;
    

    addMapTexture("../media/img/pi6grassTile.png");
    addMapTexture("../media/img/pi12grassTile.png");
    addMapTexture("../media/img/grassTile.png");
    addMapTexture("../media/img/grassTile.png");
    addMapTexture("../media/img/mpi12grassTile.png");
    addMapTexture("../media/img/mpi6grassTile.png");

    std::shared_ptr<sf::Texture> dirtTexture = std::make_shared<sf::Texture>();
    dirtTexture->loadFromFile("../media/img/dirtPillar.png");

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

        SpriteEntity* dirtPillar = new SpriteEntity();
        dirtPillar->create(dirtTexture);
        dirtPillar->setScale(Vec2f(4,4));
        dirtPillar->setPosition(Vec2f(newPos.x - platformStep, newPos.y - platformStep - newHeight + platformStep * 2));
        mainGroup->addEntity(dirtPillar);


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

float Game::getWorldHeight(float xPos)
{
    EntityGroup* mainGroup = world.getMainGroup();

    Line testLine(Vec2f(xPos, -100000), Vec2f(xPos, 100000));

    return mainGroup->getPlatformCollision(Vec2f(0, 0), &testLine).intResult.pos.y;
}
