#pragma once

#include "../../Models/Campaign/Campaign.hpp"
#include "../IWindowController.hpp"
#include "WindowTypes.hpp"
#include "Controllers/Editor/Widgets/Character/CharacterCreator/CharacterCreatorController.hpp"
#include "Controllers/Editor/Widgets/Character/CharacterSheet/CharacterSheetController.hpp"
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
    void setCurrentCampaign(Campaign currentCampaign);
    Campaign inline &getCurrentCampaign() const { return const_cast<Campaign&>(_currentCampaign); }

    bool characterCreatorVisible() {return _characterCreator->isOpen();}
    void toggleCharacterCreator();
    bool characterSheetVisible() {return _characterSheet->isOpen();}
    void toggleCharacterSheet();

private:
    friend class EditorWindowView;
    std::unique_ptr<CharacterCreatorController> _characterCreator;
    std::unique_ptr<CharacterSheetController> _characterSheet;
    
    Campaign _currentCampaign;
    std::unique_ptr<EditorWindowView> view;
};
