#pragma once
#include "Controllers/Editor/Widgets/IWidgetController.hpp"
#include "Views/Editor/Widgets/Character/CharacterCreator/CharacterCreatorView.hpp"
#include "Models/Character/CharacterModel.hpp"
#include "Models/Campaign/Campaign.hpp"
#include "Models/Rulesets/IRuleSet.hpp" // Include the ruleset interface

#include "iostream"

class CharacterCreatorController : public IWidgetController
{
public:
    CharacterCreatorController(Campaign &currentCampaign);

    void update(std::shared_ptr<GLFWwindow> window) override;

    void toggleVisibility();
    // Getters for the view
    CharacterModel &getModel() { return _model; }

private:
    friend class CharacterCreatorView;
    Campaign &_currentCampaign;
    CharacterModel _model;
    std::shared_ptr<CharacterCreatorView> _view;

    void saveCharacter()
    {
        _currentCampaign.characters.push_back(_model);
    };
};
