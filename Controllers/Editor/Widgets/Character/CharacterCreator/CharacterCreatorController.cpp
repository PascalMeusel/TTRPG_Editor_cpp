#include "CharacterCreatorController.hpp"
#include <iostream>
#include <algorithm>

CharacterCreatorController::CharacterCreatorController(Campaign &currentCampaign) : _currentCampaign(currentCampaign)
{
    _view = std::make_shared<CharacterCreatorView>(*this);
    widget = _view;
}

void CharacterCreatorController::update(std::shared_ptr<GLFWwindow> window)
{
    _view->update();
}

void CharacterCreatorController::toggleVisibility()
{
    widget->toggleVisibility();
    if (widget->isVisible())
    {
        // --- Initialize the model based on the ruleset ---
        _model.attributes.clear();
        const auto &attributeNames = _currentCampaign.ruleSet->getAttributes();
        for (const auto &name : attributeNames)
            _model.attributes[name] = 10; // Set a default value

        // Set default selections
        if (!_currentCampaign.ruleSet->getClasses().empty())
            _model.selectedClass = _currentCampaign.ruleSet->getClasses().front();
        if (!_currentCampaign.ruleSet->getRaces().empty())
            _model.selectedRace = _currentCampaign.ruleSet->getRaces().front();
    }
}

void CharacterCreatorController::saveCharacter()
{
    auto &chars = _currentCampaign.characters;
    auto it = std::find_if(chars.begin(), chars.end(),
                           [&](const CharacterModel &characterInVector)
                           {
                               return characterInVector.name == _model.name;
                           });

    if (it != chars.end())
        *it = _model;
    else
        chars.push_back(_model);
}