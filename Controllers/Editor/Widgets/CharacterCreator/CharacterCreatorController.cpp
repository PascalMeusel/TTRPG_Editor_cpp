#include "CharacterCreatorController.hpp"
#include <iostream>

CharacterCreatorController::CharacterCreatorController(Campaign &currentCampaign) : _currentCampaign(currentCampaign)
{
    _view = std::make_unique<CharacterCreatorView>(*this);
}

void CharacterCreatorController::configure()
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

void CharacterCreatorController::update(std::shared_ptr<GLFWwindow> window)
{
    if (!m_isOpen)
        return;

    _view->update();
}
