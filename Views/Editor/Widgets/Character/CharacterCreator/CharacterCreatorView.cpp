#include "CharacterCreatorView.hpp"
#include "Controllers/Editor/Widgets/CharacterCreator/CharacterCreatorController.hpp"
#include "Models/Character/CharacterModel.hpp"
#include "Models/Rulesets/IRuleSet.hpp"
#include "imgui.h"
#include "misc/cpp/imgui_stdlib.h"

#include <iostream>

CharacterCreatorView::CharacterCreatorView(CharacterCreatorController &controller) : DockableWidget("CharacterCreator", 0), _controller(controller) {}

void CharacterCreatorView::draw()
{
    // Get the model and ruleset from the controller
    CharacterModel &model = _controller.getModel();

    ImGui::InputText("Name", &model.name);

    // --- Dynamically render UI elements ---

    // Render Level if it exists in the ruleset
    if (_controller._currentCampaign.ruleSet->levelsExist())
    {
        ImGui::InputInt("Level", &model.level);
    }

    ImGui::Separator();

    // Render Races
    RenderCombo("Race", _controller._currentCampaign.ruleSet->getRaces(), model.selectedRace);

    // Render Classes
    RenderCombo("Class", _controller._currentCampaign.ruleSet->getClasses(), model.selectedClass);

    ImGui::Separator();
    ImGui::Text("Attributes");

    // Render Attributes by iterating through the model's map
    for (auto &pair : model.attributes)
        ImGui::SliderInt(pair.first.c_str(), &pair.second, 0, 50);

    ImGui::Separator();

    if (ImGui::Button("Create Character"))
    {
        _controller.saveCharacter();
        _controller.hide();
    }
}
