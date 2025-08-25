#include "CharacterCreatorController.hpp"
#include <iostream>

CharacterCreatorController::CharacterCreatorController(Campaign &currentCampaign) : _currentCampaign(currentCampaign)
{
    m_view = std::make_unique<CharacterCreatorView>(*this);
}

void CharacterCreatorController::configure()
{
    // --- Initialize the model based on the ruleset ---
    m_model.attributes.clear();
    const auto &attributeNames = _currentCampaign.ruleSet->getAttributes();
    for (const auto &name : attributeNames)
    {
        std::cout << "Adding attribute: " << name << std::endl;
        m_model.attributes[name] = 10; // Set a default value
    }

    // Set default selections
    if (!_currentCampaign.ruleSet->getClasses().empty())
    {
        m_model.selectedClass = _currentCampaign.ruleSet->getClasses().front();
    }
    if (!_currentCampaign.ruleSet->getRaces().empty())
    {
        m_model.selectedRace = _currentCampaign.ruleSet->getRaces().front();
    }
}

void CharacterCreatorController::update(std::shared_ptr<GLFWwindow> window)
{
    // Don't render if not open OR if it hasn't been configured
    if (!m_isOpen)
        return;

    m_view->update();
}