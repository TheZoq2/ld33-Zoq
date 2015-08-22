#include "leveleditor.h"

const std::string LevelEditor::SELECT_BUTTON_NAME = "SelectToolButton";
const std::string LevelEditor::MOVE_BUTTON_NAME = "MoveToolButton";
const std::string LevelEditor::ROTATE_BUTTON_NAME = "RotateToolButton";
const std::string LevelEditor::SCALE_BUTTON_NAME = "ScaleToolButton";
const std::string LevelEditor::ENTITYSEL_BUTTON_NAME = "EntitySelectButton";
const std::string LevelEditor::ENTITYSEL_LIST_NAME = "EntitySelectList";

LevelEditor::LevelEditor()
{
    this->worldView.setSize(1920, 1080);
    this->ghostEntity = NULL;
    this->movingCamera = false;
}

void LevelEditor::setupUI()
{
    mainWindow.create(Vec2f(0,0), Vec2f(300, 1080), sf::Color(255,255,255, 150));

    //Creating buttons
    zui::TextButton::ButtonColor buttonColor;
    buttonColor.defaultColor = sf::Color(0,0,255);
    buttonColor.hoverColor = sf::Color(200,200,255);
    buttonColor.pressColor = sf::Color(100,100,255);

    Vec2f defaultButtonSize = Vec2f(280, 40);

    entitySelButton = new zui::TextButton(ENTITYSEL_BUTTON_NAME,
            Vec2f(10,10),
            defaultButtonSize,
            buttonColor,
            "Select entity");
    
    entityList = new zui::ImgList(Vec2f(300, 0), Vec2f(1620,1080), ENTITYSEL_LIST_NAME);
    mainWindow.addChildComponent(entityList);
            
    //Create all the mode buttons
    Vec2f modeSize = Vec2f(40, 40);

    float modeButtonStart = 100;

    zui::TextButton* selButton = new zui::TextButton(SELECT_BUTTON_NAME,
            Vec2f(10,modeButtonStart),
            modeSize,
            buttonColor,
            "Sel");
    modeButtons.push_back(selButton);
    
    zui::TextButton* moveButton = new zui::TextButton(MOVE_BUTTON_NAME,
            Vec2f(60, modeButtonStart),
            modeSize,
            buttonColor,
            "Mov");
    modeButtons.push_back(moveButton);
            
    zui::TextButton* scaleButton = new zui::TextButton(SCALE_BUTTON_NAME,
            Vec2f(110, modeButtonStart),
            modeSize,
            buttonColor,
            "Scl");
    modeButtons.push_back(scaleButton);

    zui::TextButton* rotateButton = new zui::TextButton(ROTATE_BUTTON_NAME,
            Vec2f(160, modeButtonStart),
            modeSize,
            buttonColor,
            "Rot");
    modeButtons.push_back(rotateButton);

    for(auto it : modeButtons)
    {
        mainWindow.addChildComponent(it);
    }
    mainWindow.addChildComponent(entitySelButton);

    mainWindow.addUIValueListener(this, SELECT_BUTTON_NAME);
    mainWindow.addUIValueListener(this, ROTATE_BUTTON_NAME);
    mainWindow.addUIValueListener(this, MOVE_BUTTON_NAME);
    mainWindow.addUIValueListener(this, SCALE_BUTTON_NAME);
    mainWindow.addUIValueListener(this, ENTITYSEL_BUTTON_NAME);
    mainWindow.addUIValueListener(this, ENTITYSEL_LIST_NAME);
}

void LevelEditor::draw(sf::RenderWindow* window)
{
    window->setView(worldView);
    
    //Draw the entityGroup that is being edited
    editedGroup.draw(window);

    if(ghostEntity != NULL)
    {
        ghostEntity->draw(window);
    }
}
void LevelEditor::drawUI(sf::RenderWindow* window)
{
    mainWindow.draw(window, Vec2f(0,0));
}

void LevelEditor::onUIChange(zui::InputComponent* component)
{
    std::string componentName = component->getName();

    if(componentName == ENTITYSEL_BUTTON_NAME)
    {
        if(component->boolValue() == true)
        {
            generateEntityList();
            entityList->setActive(true);
        }
    }
    else if(componentName == ENTITYSEL_LIST_NAME)
    {
        entityList->setActive(false);
        this->newEntityName = component->stringValue();

        //editingMode = EditingMode::CREATE;
        changeMode(EditingMode::CREATE);
    }
    else if(componentName == SELECT_BUTTON_NAME)
    {
        changeMode(EditingMode::SELECT);
    }
}


zui::Window* LevelEditor::getMainWindow()
{
    return &this->mainWindow;
}

void LevelEditor::onMouseMove(MouseData mouseData, sf::RenderWindow* window)
{
    //Converting the position to world coordinates
    Vec2f worldPos = window->mapPixelToCoords(mouseData.position, worldView);
    //Vec2f worldMove = window->mapPixelToCoords(mouseData.moved, worldView);
    
    //Calculating the movement in the world this 'frame'
    Vec2f oldMousePos = mouseData.position - mouseData.moved;
    Vec2f oldWorldPos = window->mapPixelToCoords(oldMousePos, worldView);
    
    Vec2f worldMove = worldPos - oldWorldPos;

    if(movingCamera)
    {
        worldView.move(-worldMove);
    }
    else
    {
        if(editingMode == EditingMode::CREATE)
        {
            if(this->ghostEntity != NULL)
            {
                this->ghostEntity->setPosition(worldPos);
            }
        }
    }
}
void LevelEditor::onMouseButtonChange(sf::Mouse::Button button, Vec2f position, bool pressed, sf::RenderWindow* window)
{
    //Converting the position to world coordinates
    Vec2f worldPos = window->mapPixelToCoords((sf::Vector2i) position, worldView);

    bool mouseIsOnUI = mainWindow.posIsOnUI(position, Vec2f(0,0));

    if(button == sf::Mouse::Middle)
    {
        movingCamera = pressed;
    }

    if(movingCamera == false)
    {
        switch(editingMode)
        {
            case SELECT:
            {
                break;
            }
            case MOVE:
            {
                break;
            }
            case SCALE:
            {
                break;
            }
            case ROTATE:
            {
                break;
            }
            case CREATE:
            {
                if(button == sf::Mouse::Left && pressed == true && mouseIsOnUI == false)
                {
                    editedGroup.addEntity(ghostEntity->clone());
                }
                break;
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
//                           Private functions
/////////////////////////////////////////////////////////////////////////////
void LevelEditor::generateEntityList()
{
    const std::string entityFolder = "../media/img/";

    //Generate a vector of images
    std::vector<std::pair<std::string, std::string> > imgElements;

    DIR* dir;
    struct dirent* ent;
    if((dir = opendir(entityFolder.data())) != NULL)
    {
        while((ent = readdir(dir)) != NULL)
        {
            std::string filename = ent->d_name;

            //If the file type is a .png
            if(filename.find_last_not_of(".png") != filename.length() -1 && filename.find(".png") != std::string::npos)
            {
                imgElements.push_back(std::pair<std::string, std::string>(entityFolder + filename, entityFolder + filename));
            }
        }
        closedir(dir);
    }

    entityList->setElements(imgElements);
}

void LevelEditor::createGhostEntity(Vec2f worldPos)
{
    if(newEntityName != "")
    {
        std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
        texture->loadFromFile(newEntityName);

        SpriteEntity* newEntity = new SpriteEntity();
        newEntity->create(texture);
        newEntity->setOrigin(Vec2f(0.5, 0.5));

        ghostEntity = newEntity;
        ghostEntity->setPosition(worldPos);

        std::cout << texture.use_count() << std::endl;
    }
}

void LevelEditor::changeMode(LevelEditor::EditingMode newMode)
{
    exitMode();
    switch(newMode)
    {
        case SELECT:
        {

            break;
        }
        case MOVE:
        {
            break;
        }
        case SCALE:
        {
            break;
        }
        case ROTATE:
        {
            break;
        }
        case CREATE:
        {
            createGhostEntity(Vec2f(0,0));
            break;
        }
    }

    this->editingMode = newMode;
}
void LevelEditor::exitMode()
{
    switch(editingMode)
    {
        case SELECT:
        {

            break;
        }
        case MOVE:
        {
            break;
        }
        case SCALE:
        {
            break;
        }
        case ROTATE:
        {
            break;
        }
        case CREATE:
        {
            break;
        }
    }
}
