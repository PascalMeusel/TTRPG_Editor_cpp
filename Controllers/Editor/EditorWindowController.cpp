#include <iostream>
#include "EditorWindowController.hpp"
#include "Views/Editor/EditorWindowView.hpp"

EditorWindowController::EditorWindowController()
{
    view = std::make_unique<EditorWindowView>(*this);
}

EditorWindowController::~EditorWindowController() = default;

void EditorWindowController::update(std::shared_ptr<GLFWwindow> window)
{
    if (!view->isVisible)
        return;
    view->update(window);
    if (_characterCreator->isOpen())
        _characterCreator->update(window);
    if (_characterSheet->isOpen())
        _characterSheet->update(window);
}

WindowTypes EditorWindowController::getWindowType()
{
    return WindowTypes::EditorWindow;
}
bool EditorWindowController::getWindowActive()
{
    return view->isVisible;
}
void EditorWindowController::setCurrentCampaign(Campaign currentCampaign)
{
    _currentCampaign = std::move(currentCampaign);
    _characterCreator = std::make_unique<CharacterCreatorController>(_currentCampaign);
    _characterSheet = std::make_unique<CharacterSheetController>(_currentCampaign);
}
void EditorWindowController::toggleCharacterCreator()
{
    _characterCreator->toggleVisibility();
}
void EditorWindowController::toggleCharacterSheet()
{
    _characterSheet->toggleVisibility();
}
void EditorWindowController::setWindowOpacity(bool showView)
{
    view->isVisible = showView;
};
