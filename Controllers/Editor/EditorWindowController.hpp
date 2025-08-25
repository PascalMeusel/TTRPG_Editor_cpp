#pragma once

#include "../../Models/Campaign/Campaign.hpp"
#include "../IWindowController.hpp"
#include "WindowTypes.hpp"
#include "Controllers/Editor/Widgets/CharacterCreator/CharacterCreatorController.hpp"
#include <iostream>
class EditorWindowView;
class EditorWindowController : public IWindowController
{
public:
    EditorWindowController();
    ~EditorWindowController();

    virtual void update(std::shared_ptr<GLFWwindow> window) override;

    virtual void setWindowOpacity(bool showView) override;

    virtual WindowTypes getWindowType() override;
    virtual bool getWindowActive() override;
    void inline setCurrentCampaign(Campaign currentCampaign) { _currentCampaign = currentCampaign; }
    Campaign inline getCurrentCampaign() const { return _currentCampaign; }

    void showCharacterCreator();
private:
    friend class EditorWindowView;
    
    Campaign _currentCampaign;
    std::unique_ptr<EditorWindowView> view;
    std::shared_ptr<CharacterCreatorController> _characterCreator;
};