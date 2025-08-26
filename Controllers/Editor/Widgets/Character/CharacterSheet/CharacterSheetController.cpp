#include "CharacterSheetController.hpp"
#include <algorithm>

CharacterSheetController::CharacterSheetController(Campaign &currentCampaign) : _currentCampaign(currentCampaign)
{
    view = std::make_shared<CharacterSheetView>(*this);
    widget = view;
    _selectedCharacterModel = noCharacter;
}

void CharacterSheetController::loadCharacter(std::string characterName)
{
    for (auto character : _currentCampaign.characters)
    {
        if (character.name == characterName)
        {
            _selectedCharacterModel = character;
            return;
        }
    }
    // Maybe throw an exception here
}

void CharacterSheetController::saveCharacter()
{
    auto &chars = _currentCampaign.characters;
    auto it = std::find_if(chars.begin(), chars.end(),
                           [&](const CharacterModel &characterInVector)
                           {
                               return characterInVector.name == _selectedCharacterModel.name;
                           });

    if (it != chars.end())
        *it = _selectedCharacterModel;
    else
        chars.push_back(_selectedCharacterModel);
    DatabaseManager::getInstance()->saveCampaign(_currentCampaign);
}

void CharacterSheetController::toggleVisibility()
{
    view->toggleVisibility();
    if (widget->isVisible())
    {
        _existingCharacters.clear();
        for (auto character : _currentCampaign.characters)
            _existingCharacters.push_back(character.name);
    }
}

void CharacterSheetController::update(std::shared_ptr<GLFWwindow> window)
{
    view->update();
}
