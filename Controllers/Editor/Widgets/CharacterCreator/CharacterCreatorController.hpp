#pragma once
#include "Controllers/Editor/Widgets/IWidgetController.hpp"
#include "Views/Editor/Widgets/Character/CharacterCreator/CharacterCreatorView.hpp"
#include "Models/Character/CharacterModel.hpp"
#include "Models/Rulesets/IRuleSet.hpp" // Include the ruleset interface

class CharacterCreatorController : public IWidgetController
{
private:
    CharacterModel m_model;
    std::unique_ptr<CharacterCreatorView> m_view;
    std::shared_ptr<IRuleSet> activeRuleset = nullptr; // Pointer to the current ruleset

public:
    CharacterCreatorController();

    void update(std::shared_ptr<GLFWwindow> window) override;

    // New method to configure the widget with the active ruleset
    void configure(std::shared_ptr<IRuleSet> ruleSet);

    // Getters for the view
    CharacterModel &getModel() { return m_model; }
    std::shared_ptr<IRuleSet> getRuleSet() const { return activeRuleset; }
};