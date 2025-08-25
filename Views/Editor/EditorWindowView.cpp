#include "EditorWindowView.hpp"
#include "Controllers/Editor/EditorWindowController.hpp"
#include "imgui.h"

#include <iostream>

EditorWindowView::EditorWindowView(EditorWindowController &controller) : _controller(controller)
{
}

void EditorWindowView::update(std::shared_ptr<GLFWwindow> window)
{
    // Render the editor's dockable windows
    ImGui::Begin("Scene View");
    ImGui::Text("This is where the 3D scene would be rendered.");
    ImGui::End();

    ImGui::Begin("Inspector");
    ImGui::Text("Object properties will be shown here.");
    ImGui::End();
}