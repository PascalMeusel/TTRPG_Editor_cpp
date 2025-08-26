#pragma once

#include "Models/Campaign/Campaign.hpp"
#include "Controllers/Editor/Widgets/IWidgetController.hpp"
#include "Views/Editor/Widgets/Character/CharacterSheet/CharacterSheetView.hpp"
#include "Models/DataBaseManager.hpp"

class CharacterSheetView;
class CharacterSheetController : public IWidgetController
{
public:
CharacterSheetController(Campaign &currentCampaign);

void loadCharacter(std::string characterName);
void saveCharacter();

virtual void toggleVisibility() override;

virtual void update(std::shared_ptr<GLFWwindow> window) override;
private:
    friend class CharacterSheetView;
    std::shared_ptr<CharacterSheetView> view;
    Campaign &_currentCampaign;
    std::vector<std::string> _existingCharacters;
    CharacterModel _selectedCharacterModel;
    CharacterModel noCharacter{
        .name = "-"
    };
};