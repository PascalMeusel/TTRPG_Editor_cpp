#pragma once

#include "../IWindowController.hpp"
#include "Models/Campaign/Campaign.hpp"

class MainMenuWindowView;

class MainMenuWindowController : public IWindowController
{
public:
    MainMenuWindowController();
    ~MainMenuWindowController();

    virtual void update(std::shared_ptr<GLFWwindow> window) override;

    virtual void setWindowOpacity(bool showView) override;

    virtual WindowTypes getWindowType() override;
    virtual bool getWindowActive() override;
private:
    friend class MainMenuWindowView;
    std::unique_ptr<MainMenuWindowView> view;

    void handleNewGame(Campaign campaign);
    void handleLoadGame(Campaign campaign);
};
