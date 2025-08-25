#pragma once
#include "Controllers/Editor/Widgets/IWidgetController.hpp"
#include "Views/Editor/Widgets/Character/CharacterCreator/CharacterCreatorView.hpp"
#include "Models/Character/CharacterModel.hpp"
#include "Models/Campaign/Campaign.hpp"
#include "Models/Rulesets/IRuleSet.hpp" // Include the ruleset interface

class CharacterCreatorController : public IWidgetController
{
public:
    CharacterCreatorController(Campaign &currentCampaign);

    void update(std::shared_ptr<GLFWwindow> window) override;

    // New method to configure the widget with the active ruleset
    void configure();

    // Getters for the view
    CharacterModel &getModel() { return m_model; }
private:
    friend class CharacterCreatorView;
    CharacterModel m_model;
    std::unique_ptr<CharacterCreatorView> m_view;
    Campaign &_currentCampaign; 

    void saveCharacter() {_currentCampaign.characters.push_back(m_model);};
};