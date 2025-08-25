#include <iostream>
#include "EditorWindowController.hpp"
#include "Views/Editor/EditorWindowView.hpp"

EditorWindowController::EditorWindowController()
{
    view = std::make_unique<EditorWindowView>(*this);
    m_characterCreator = std::make_shared<CharacterCreatorController>();
}

EditorWindowController::~EditorWindowController() = default;

void EditorWindowController::update(std::shared_ptr<GLFWwindow> window)
{
    if (!view->isVisible)
        return;
    view->update(window);
    if(m_characterCreator->isOpen())
    {
        std::cout << "showing creator" << "\n";
        m_characterCreator->update(window);
    }
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
    std::shared_ptr<IRuleSet> ruleSet = _currentCampaign.ruleSet;
    if (!ruleSet) {
        std::cerr << "Cannot open Character Creator: Active campaign has no ruleset." << std::endl;
        return;
    }

    // Configure the widget with the ruleset BEFORE showing it
    m_characterCreator->configure(ruleSet);
    m_characterCreator->show();
}