#include "CharacterCreatorView.hpp"
#include "Controllers/Editor/Widgets/CharacterCreator/CharacterCreatorController.hpp"
#include "Models/Character/CharacterModel.hpp"
#include "Models/Rulesets/IRuleSet.hpp"
#include "imgui.h"

#include <iostream>

CharacterCreatorView::CharacterCreatorView(CharacterCreatorController& controller) : _controller(controller) {}

// Helper function for creating dynamic combo boxes
void RenderCombo(const char* label, const std::vector<std::string>& items, std::string& current_item)
{
    if (ImGui::BeginCombo(label, current_item.c_str()))
    {
        for (const auto& item : items)
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


void CharacterCreatorView::update(bool* p_open)
{
    std::cout<< "Character creator" << "\n";
    if (!ImGui::Begin("Character Creator", p_open))
    {
        std::cout<< "Character creator unssuccesful" << "\n";
        ImGui::End();
        return;
    }

    // Get the model and ruleset from the controller
    CharacterModel& model = _controller.getModel();
    std::shared_ptr<IRuleSet> ruleSet = _controller.getRuleSet();

    ImGui::InputText("Name", model.nameBuffer, 128);

    // --- Dynamically render UI elements ---

    // Render Level if it exists in the ruleset
    if (ruleSet->levelsExist()) {
        ImGui::InputInt("Level", &model.level);
    }

    ImGui::Separator();

    // Render Races
    RenderCombo("Race", ruleSet->getRaces(), model.selectedRace);

    // Render Classes
    RenderCombo("Class", ruleSet->getClasses(), model.selectedClass);

    ImGui::Separator();
    ImGui::Text("Attributes");

    // Render Attributes by iterating through the model's map
    for (auto& pair : model.attributes) {
        ImGui::SliderInt(pair.first.c_str(), &pair.second, 1, 20);
    }
    
    ImGui::Separator();

    if (ImGui::Button("Create Character"))
    {
        // TODO: Add logic to create the character object and save it.
        _controller.hide();
    }
    
    ImGui::End();
}