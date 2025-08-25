#include "MainMenuWindowController.hpp"
#include "Views/MainMenu/MainMenuWindowView.hpp"

MainMenuWindowController::MainMenuWindowController()
{
    view = std::make_unique<MainMenuWindowView>(*this);
}

MainMenuWindowController::~MainMenuWindowController() = default;

void MainMenuWindowController::update(std::shared_ptr<GLFWwindow> window)
{
    if(!view->isVisible)
        return;
    view->update(window);
};

void MainMenuWindowController::setWindowOpacity(bool showView) 
{ 
    view->isVisible = showView;
}

WindowTypes MainMenuWindowController::getWindowType()
{
    return WindowTypes::MainMenuWindow;
}

bool MainMenuWindowController::getWindowActive()
{
    return view->isVisible;
}

void MainMenuWindowController::handleNewGame(Campaign campaign)
{
    DatabaseManager::getInstance()->saveCampaign(campaign);
    handleLoadGame(campaign);
}

void MainMenuWindowController::handleLoadGame(Campaign campaign)
{
    auto chosenCampaign = DatabaseManager::getInstance()->loadCampaign(campaign.name);
    view->isVisible = false;
}
