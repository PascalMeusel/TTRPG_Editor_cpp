#include "MainMenuWindowView.hpp"

#include "Application.hpp"

// The update method now takes the window pointer as an argument
void MainMenuWindowView::update(GLFWwindow *window)
{
    if(!isVisible)
        return;
    _currentChoice = MainMenuOption::None;
    // Get the main viewport to determine the available drawing area
    ImGuiViewport *mainViewport = ImGui::GetMainViewport();

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
        ImVec2 buttonSize(300, 100);

        // Calculate the total height of all buttons and spacing to center them vertically
        const int numButtons = 5;
        const float buttonSpacing = 25.0f;
        float totalContentHeight = (buttonSize.y * numButtons) + (buttonSpacing * (numButtons - 1));

        // Set the initial vertical position to center the block of buttons
        ImGui::SetCursorPosY((mainViewport->WorkSize.y - totalContentHeight) * 0.5f);

        // --- Render the centered buttons ---

        ImGui::SetCursorPosX((mainViewport->WorkSize.x - buttonSize.x) * 0.5f);
        if (ImGui::Button("New Game", buttonSize))
        {
            _showNewGamePopup = true;

            ImGui::OpenPopup("New Game");
            _campaignName = "";
            _selectedRuleIndex = 0;
        }
        ImGui::Dummy(ImVec2(0.0f, buttonSpacing)); // Add vertical spacing
        ImGui::SetCursorPosX((mainViewport->WorkSize.x - buttonSize.x) * 0.5f);
        if (ImGui::Button("Load Game", buttonSize))
        {
            _showLoadGamePopup = true;
            ImGui::OpenPopup("Load Game");
            _selectedLoadGameIndex = 0;
        }
        ImGui::Dummy(ImVec2(0.0f, buttonSpacing)); // Add vertical spacing
        ImGui::SetCursorPosX((mainViewport->WorkSize.x - buttonSize.x) * 0.5f);
        ImGui::Button("Add Ruleset", buttonSize);
        ImGui::Dummy(ImVec2(0.0f, buttonSpacing)); // Add vertical spacing
        ImGui::SetCursorPosX((mainViewport->WorkSize.x - buttonSize.x) * 0.5f);
        ImGui::Button("Settings", buttonSize);
        ImGui::Dummy(ImVec2(0.0f, buttonSpacing)); // Add vertical spacing

        // --- Exit Button ---
        ImGui::SetCursorPosX((mainViewport->WorkSize.x - buttonSize.x) * 0.5f);
        if (ImGui::Button("Exit", buttonSize))
        {
            // If clicked, tell GLFW to close the window.
            // The main loop in Application::Run() will detect this and exit.
            glfwSetWindowShouldClose(window, true);
        }
        handleNewGame();
        handleLoadGame();
    }
    // Always call End, even if Begin returned false
    ImGui::End();
}

void MainMenuWindowView::handleNewGame()
{
    if (ImGui::BeginPopupModal("New Game", &_showNewGamePopup, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("Enter new campaign name:");
        ImGui::InputText("##CampaignName", &_campaignName);

        ImGui::Separator();
        ImGui::Text("Choose a ruleset:");

        // --- Correctly handle the Combo box ---
        // You must convert from vector<unique_ptr<IRuleSet>> to const char*
        std::vector<const char *> rulesetNames;
        for (const auto &rulesetPtr : ruleSets)
        {
            rulesetNames.push_back(rulesetPtr->getName());
        }

        if (!rulesetNames.empty())
        {
            ImGui::Combo("Ruleset", &_selectedRuleIndex, rulesetNames.data(), static_cast<int>(rulesetNames.size()));
        }

        ImGui::Separator();

        if (ImGui::Button("Create", ImVec2(120, 0)))
        {
            Campaign newCampaign;
            newCampaign.name = _campaignName;
            newCampaign.ruleSet = ruleSets[_selectedRuleIndex];
            std::vector<Campaign> campaigns = DatabaseManager::getInstance()->loadAllCampaigns();
            bool campaignNameExists = false;
            for (auto campaign : campaigns)
            {
                if (campaign.name == _campaignName)
                    campaignNameExists = true;
            }
            if (!campaignNameExists)
            {
                DatabaseManager::getInstance()->saveCampaign(newCampaign);
                openEditor(newCampaign);
            }
            else
            {
                ImGui::OpenPopup("Creation Failed");
            }
            // Close the popup
            _showNewGamePopup = false;
            ImGui::CloseCurrentPopup();
        }

        ImGui::SameLine(); // Place the next widget on the same line

        if (ImGui::Button("Cancel", ImVec2(120, 0)))
        {
            // Just close the popup
            _showNewGamePopup = false;
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
}

void MainMenuWindowView::handleLoadGame()
{
    if (ImGui::BeginPopupModal("Load Game", &_showLoadGamePopup, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("Choose a Saved Campaign:");

        std::vector<const char *> campaignNames;
        auto campaigns = DatabaseManager::getInstance()->loadAllCampaigns();
        for (const auto &campaign : campaigns)
        {
            campaignNames.push_back(campaign.name.c_str());
        }
        ImGui::Combo("Campaigns", &_selectedLoadGameIndex, campaignNames.data(), static_cast<int>(campaignNames.size()));

        ImGui::Separator();

        if (ImGui::Button("Load", ImVec2(120, 0)))
        {
            auto chosenCampaign = DatabaseManager::getInstance()->loadCampaign(campaignNames[_selectedLoadGameIndex]);
            openEditor(chosenCampaign);
            // Close the popup
            _showLoadGamePopup = false;
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

void MainMenuWindowView::openEditor(Campaign campaign)
{
    this->isVisible = false;
    _editor->isVisible = true;
    _editor->setCurrentCampaign(campaign);
}
