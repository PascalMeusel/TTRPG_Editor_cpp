#include <iostream>
#include "EditorWindowController.hpp"
#include "Views/Editor/EditorWindowView.hpp"

EditorWindowController::EditorWindowController()
{
    view = std::make_unique<EditorWindowView>(*this);
    _characterCreator = std::make_shared<CharacterCreatorController>(_currentCampaign);
}

EditorWindowController::~EditorWindowController() = default;

void EditorWindowController::update(std::shared_ptr<GLFWwindow> window)
{
    if (!view->isVisible)
        return;
    view->update(window);
    if(_characterCreator->isOpen())
        _characterCreator->update(window);
}

WindowTypes EditorWindowController::getWindowType()
{
    return WindowTypes::EditorWindow;
}
bool EditorWindowController::getWindowActive()
{
    return view->isVisible;
}
void EditorWindowController::setWindowOpacity(bool showView)
{
    view->isVisible = showView;
};

void EditorWindowController::showCharacterCreator()
{
    _characterCreator->configure();
    _characterCreator->show();
}
