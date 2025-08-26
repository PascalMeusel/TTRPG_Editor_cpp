#include "CharacterSheetView.hpp"
#include "Controllers/Editor/Widgets/Character/CharacterSheet/CharacterSheetController.hpp"

#include "misc/cpp/imgui_stdlib.h"
#include "iostream"

CharacterSheetView::CharacterSheetView(CharacterSheetController &controller) : DockableWidget("Charactersheet"), _controller(controller)
{
}

void CharacterSheetView::draw()
{
    CharacterModel &model = _controller._selectedCharacterModel;

    ImGui::Text("Select Character");
    ImGui::Separator();
    std::string nameBeforeCombo = model.name;
    RenderCombo("Characters", _controller._existingCharacters, model.name);
    if (model.name != nameBeforeCombo)
    {
        _controller.loadCharacter(model.name);
        return;
    }
    if (model.name != _controller.noCharacter.name)
    {
        ImGui::Text("Name");
        ImGui::Separator();
        ImGui::Text("%s", model.name.c_str());

        ImGui::Text("Level");
        ImGui::Separator();
        ImGui::Text("%d", model.level);

        ImGui::Text("Race");
        ImGui::Separator();
        ImGui::Text("%s", model.selectedRace.c_str());

        ImGui::Text("Class");
        ImGui::Separator();
        ImGui::Text("%s", model.selectedClass.c_str());

        for (auto& attributePair : model.attributes)
        {
            const std::string& attributeName = attributePair.first;
            int& attributeValue = attributePair.second;

            ImGui::Text("%s: %d", attributeName.c_str(), attributeValue);

            ImGui::SameLine();
            std::string minusButtonLabel = "-##" + attributeName;
            if (ImGui::Button(minusButtonLabel.c_str()))
                attributeValue--;

            ImGui::SameLine();
            std::string plusButtonLabel = "+##" + attributeName;
            if (ImGui::Button(plusButtonLabel.c_str()))
                attributeValue++;
        }
        ImGui::Separator();
        if (ImGui::Button("Save Character"))
            _controller.saveCharacter();
    }
}
