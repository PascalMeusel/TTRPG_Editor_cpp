#pragma once

#include <vector>
#include <string>
#include <tuple>
#include <memory>
#include <iostream>

#include <imgui.h>
#include <imgui/misc/cpp/imgui_stdlib.h>
#include <GLFW/glfw3.h>

#include "../IWindowView.hpp"
#include "../../Models/DataBaseManager.hpp"
#include "../../Models/Rulesets/DND/DND5e.hpp"

class Application;

enum class MainMenuOption
{
    None,
    NewGame,
    LoadGame,
    AddRuleSet,
    Settings,
    Exit
};

class MainMenuWindowView : public IWindowView
{
public:
    MainMenuWindowView(std::shared_ptr<Application> parent)
        : IWindowView(parent)
    {
        ruleSets.push_back(std::make_unique<DND5e>()); // Add a default ruleset, e.g., DND5e
    }
    ~MainMenuWindowView() = default;

    // Function to update the view
    void update(GLFWwindow *window) override;

protected:
    std::vector<std::shared_ptr<IRuleSet>> ruleSets;

    // New game dialogWindow
    void handleNewGame();
    bool _showNewGamePopup = false;
    std::string _campaignName = std::string();
    int _selectedRuleIndex = 0;

    // Load game dialogWindow
    void handleLoadGame();
    bool _showLoadGamePopup = false;
    int _selectedLoadGameIndex = 0;

    void openEditor(Campaign campaign);

    MainMenuOption _currentChoice = MainMenuOption::None;
};