#include "CharacterSheetView.hpp"
#include "Controllers/Editor/Widgets/CharacterSheet/CharacterSheetController.hpp"

#include "iostream"

CharacterSheetView::CharacterSheetView(CharacterSheetController &controller) : DockableWidget("Charactersheet"), _controller(controller)
{
}

void CharacterSheetView::draw()
{
    CharacterModel &model = _controller._selectedCharacterModel;

    ImGui::Text("Select Character");
    ImGui::Separator();
    RenderCombo("Characters", _controller._existingCharacters, model.name);
    std::cout << "Name of chosen char: " << model.name << " and name of no char: " << _controller.noCharacter.name << std::endl;
    if(model.name != _controller.noCharacter.name)
    {
        //we render something
        std::cout << "Hi" << std::endl;
        ImGui::Text("WE HAVE A CHARACTER");
    }
}