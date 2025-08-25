#include "CharacterCreatorView.hpp"
#include "Controllers/Editor/Widgets/CharacterCreator/CharacterCreatorController.hpp"
#include "Models/Character/CharacterModel.hpp"
#include "Models/Rulesets/IRuleSet.hpp"
#include "imgui.h"

#include <iostream>

CharacterCreatorView::CharacterCreatorView(CharacterCreatorController &controller) : DockableWidget("CharacterCreator", 0), _controller(controller) {}

// Helper function for creating dynamic combo boxes
void RenderCombo(const char *label, const std::vector<std::string> &items, std::string &current_item)
{
    if (ImGui::BeginCombo(label, current_item.c_str()))
    {
        for (const auto &item : items)
        {
            const bool is_selected = (current_item == item);
            if (ImGui::Selectable(item.c_str(), is_selected))
            {
                current_item = item;
            }
            if (is_selected)
            {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }
}

void CharacterCreatorView::draw()
{
    // Get the model and ruleset from the controller
    CharacterModel &model = _controller.getModel();

    ImGui::InputText("Name", model.nameBuffer, 128);

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
