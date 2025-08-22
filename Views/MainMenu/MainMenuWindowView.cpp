

#include "MainMenuWindowView.hpp"

MainMenuWindowView::MainMenuWindowView()
{
    ruleSets.push_back(std::make_unique<DND5e>()); // Add a default ruleset, e.g., DND5e
    // Constructor can initialize any member variables if needed
}
// The update method now takes the window pointer as an argument
void MainMenuWindowView::update(GLFWwindow* window)
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
    // This allows us to position elements within the main application window.
    if (ImGui::Begin("MainMenuContainer", nullptr, windowFlags))
    {
        // Define a larger button size
        ImVec2 buttonSize(200, 50);

        // Calculate the total height of all buttons and spacing to center them vertically
        const int numButtons = 5;
        const float buttonSpacing = 10.0f;
        float totalContentHeight = (buttonSize.y * numButtons) + (buttonSpacing * (numButtons - 1));
        
        // Set the initial vertical position to center the block of buttons
        ImGui::SetCursorPosY((mainViewport->WorkSize.y - totalContentHeight) * 0.5f);

        // --- Render the centered buttons ---

        // Helper lambda to render a centered button
        auto renderCenteredButton = [&](const char* label) -> bool {
            return ImGui::Button(label, buttonSize);
        };
        
        ImGui::SetCursorPosX((mainViewport->WorkSize.x - buttonSize.x) * 0.5f);
        if(ImGui::Button("New Game", buttonSize))
        {
            ImGui::Begin("New Game Dialog");
            ImGui::Text("Enter new compaingn name:");
            static char campaignName[128] = "";
            ImGui::InputText("Campaign Name", campaignName, sizeof(campaignName));
            ImGui::Text("Choose a ruleset:");
            static int selectedRuleset = 0;
            std::vector<const char*> rulesetStrings;
            for (const auto& ruleset : ruleSets)
            {
                rulesetStrings.push_back(ruleset->getName());
            }
            // Use ImGui::Combo to create a dropdown for rulesets
            ImGui::Combo("Ruleset", &selectedRuleset, rulesetStrings.data(), static_cast<int>(rulesetStrings.size()));
            
            if (ImGui::Button("Create"))
            {
                // Handle the creation of a new campaign here
                // For now, just close the dialog
                printf("Creating new campaign: %s with ruleset: %s\n", campaignName, ruleSets[selectedRuleset]->getName());
                ImGui::CloseCurrentPopup();
            }
            ImGui::End();
        }
        ImGui::Dummy(ImVec2(0.0f, buttonSpacing)); // Add vertical spacing
        ImGui::SetCursorPosX((mainViewport->WorkSize.x - buttonSize.x) * 0.5f);
        ImGui::Button("Load Game", buttonSize);
        ImGui::Dummy(ImVec2(0.0f, buttonSpacing)); // Add vertical spacing
        ImGui::SetCursorPosX((mainViewport->WorkSize.x - buttonSize.x) * 0.5f);
        ImGui::Button("Add Ruleset", buttonSize);
        ImGui::Dummy(ImVec2(0.0f, buttonSpacing)); // Add vertical spacing
        ImGui::SetCursorPosX((mainViewport->WorkSize.x - buttonSize.x) * 0.5f);
        ImGui::Button("Settings", buttonSize);
        ImGui::Dummy(ImVec2(0.0f, buttonSpacing)); // Add vertical spacing

        // --- Exit Button ---
        // For the last button, check if it's clicked
        ImGui::SetCursorPosX((mainViewport->WorkSize.x - buttonSize.x) * 0.5f);
        if (ImGui::Button("Exit", buttonSize))
        {
            // If clicked, tell GLFW to close the window.
            // The main loop in Application::Run() will detect this and exit.
            glfwSetWindowShouldClose(window, true);
        }
    }
    // Always call End, even if Begin returned false
    ImGui::End();
}