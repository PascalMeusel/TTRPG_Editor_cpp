#include "CharacterCreatorController.hpp"
#include <iostream>

CharacterCreatorController::CharacterCreatorController()
{
    m_view = std::make_unique<CharacterCreatorView>(*this);
}

void CharacterCreatorController::configure(std::shared_ptr<IRuleSet> ruleSet)
{
    if (!ruleSet) {
        std::cerr << "Error: Cannot configure CharacterCreator with a null ruleset." << std::endl;
        return;
    }

    activeRuleset = ruleSet;
    
    // --- Initialize the model based on the ruleset ---
    m_model.attributes.clear();
    const auto& attributeNames = activeRuleset->getAttributes();
    for (const auto& name : attributeNames) {
        m_model.attributes[name] = 10; // Set a default value
    }

    // Set default selections
    if (!activeRuleset->getClasses().empty()) {
        m_model.selectedClass = activeRuleset->getClasses().front();
    }
    if (!activeRuleset->getRaces().empty()) {
        m_model.selectedRace = activeRuleset->getRaces().front();
    }
}

void CharacterCreatorController::update(std::shared_ptr<GLFWwindow> window)
{
    // Don't render if not open OR if it hasn't been configured
    if (!m_isOpen || !activeRuleset)
    {
        return;
    }

    m_view->update(&m_isOpen);
}