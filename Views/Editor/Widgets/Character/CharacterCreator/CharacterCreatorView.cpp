#include "CharacterCreatorView.hpp"
#include "Controllers/Editor/Widgets/Character/CharacterCreator/CharacterCreatorController.hpp"
#include "Models/Character/CharacterModel.hpp"
#include "Models/Rulesets/IRuleSet.hpp"
#include "imgui.h"
#include "misc/cpp/imgui_stdlib.h"

#include <iostream>

CharacterCreatorView::CharacterCreatorView(CharacterCreatorController &controller) : DockableWidget("CharacterCreator", 0), _controller(controller) {}

void CharacterCreatorView::draw()
{
    CharacterModel &model = _controller.getModel();

    ImGui::InputText("Name", &model.name);
    if (_controller._currentCampaign.ruleSet->levelsExist())
        ImGui::InputInt("Level", &model.level);
    ImGui::Separator();
    RenderCombo("Race", _controller._currentCampaign.ruleSet->getRaces(), model.selectedRace);
    RenderCombo("Class", _controller._currentCampaign.ruleSet->getClasses(), model.selectedClass);
    ImGui::Separator();
    ImGui::Text("Attributes");

    for (auto &pair : model.attributes)
        ImGui::SliderInt(pair.first.c_str(), &pair.second, 0, 50);
    ImGui::Separator();

    if (ImGui::Button("Create Character"))
    {
        _controller.saveCharacter();
        _controller.hide();
    }
}
