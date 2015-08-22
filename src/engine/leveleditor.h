#ifndef H_LEVELEDITOR
#define H_LEVELEDITOR

#include <SFML/Graphics.hpp>
#include <dirent.h>
#include <memory>

#include "zui/window.h"
#include "zui/textbutton.h"
#include "zui/imglist.h"
#include "zui/uicomponent.h"
#include "zui/inputcomponent.h"
#include "entity.h"
#include "spriteentity.h"
#include "entitygroup.h"


class LevelEditor : public MouseListener, zui::UIValueListener
{
public:
    LevelEditor();

    void setupUI();

    void draw(sf::RenderWindow* window);
    void drawUI(sf::RenderWindow* window);

    void onUIChange(zui::InputComponent* changedComponent);

    zui::Window* getMainWindow();

    void onMouseMove(MouseData moveData, sf::RenderWindow* window);
    void onMouseButtonChange(sf::Mouse::Button button, Vec2f position, bool pressed, sf::RenderWindow* window);
private:
    enum EditingMode
    {
        SELECT,
        MOVE,
        SCALE,
        ROTATE,
        CREATE,
    };

    void generateEntityList();

    void createGhostEntity(Vec2f worldPos);

    void changeMode(EditingMode newMode);
    void exitMode(); //Exit the current mode and clean up everything
    void addGhostEntity();

    EditingMode editingMode;

    sf::View worldView;

    Entity* ghostEntity;
    std::string newEntityName;

    EntityGroup editedGroup;

    //UI stuff
    const static std::string SELECT_BUTTON_NAME;
    const static std::string MOVE_BUTTON_NAME;
    const static std::string SCALE_BUTTON_NAME;
    const static std::string ROTATE_BUTTON_NAME;
    const static std::string ENTITYSEL_BUTTON_NAME;
    const static std::string ENTITYSEL_LIST_NAME;

    zui::Window mainWindow;

    std::vector< zui::TextButton* > modeButtons;
    zui::TextButton* entitySelButton;
    zui::ImgList* entityList;

    bool movingCamera;
};
#endif
