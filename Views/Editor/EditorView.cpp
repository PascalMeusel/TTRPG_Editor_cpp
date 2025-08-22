#include "EditorView.hpp"

void EditorView::update(GLFWwindow* window)
{
    // Get the main viewport to determine the available drawing area
    ImGuiViewport* mainViewport = ImGui::GetMainViewport();

    // Set our next window to be the size of the main viewport, with no decorations
    ImGui::SetNextWindowPos(mainViewport->WorkPos);
    ImGui::SetNextWindowSize(mainViewport->WorkSize);
    ImGui::SetNextWindowBgAlpha(0.0f); // Make the window transparent

    // Define window flags to make it act as a drawing canvas rather than a window
    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoTitleBar |
                                   ImGuiWindowFlags_NoResize |
                                   ImGuiWindowFlags_NoMove |
                                   ImGuiWindowFlags_NoCollapse |
                                   ImGuiWindowFlags_NoScrollbar |
                                   ImGuiWindowFlags_NoSavedSettings |
                                   ImGuiWindowFlags_NoDocking;

    // Begin a "window" that covers the entire viewport.
    if (ImGui::Begin("EditorContainer", nullptr, windowFlags))
    {
        // Here you can add your editor controls and widgets
        ImGui::Text("Editor View");
        // Add more editor-specific UI elements here

        // Example: A simple text input field
        static char textBuffer[256] = "";
        ImGui::InputText("Text Input", textBuffer, sizeof(textBuffer));

        // Example: A button to simulate saving changes
        if (ImGui::Button("Save Changes"))
        {
            // Handle save logic here
        }
    }
    
    ImGui::End();
}