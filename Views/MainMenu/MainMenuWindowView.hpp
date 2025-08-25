#pragma once

#include <vector>
#include <string>
#include <tuple>
#include <memory>
#include <iostream>

#include <imgui.h>
#include <extern/imgui/misc/cpp/imgui_stdlib.h>
#include <GLFW/glfw3.h>

#include "../IWindowView.hpp"
#include "../../Models/DataBaseManager.hpp"
#include "../../Models/Rulesets/DND/DND5e.hpp"

class MainMenuWindowController;

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
    MainMenuWindowView() = delete;
    MainMenuWindowView(MainMenuWindowController &controller) : _controller(controller)
    {
        ruleSets.push_back(std::make_unique<DND5e>()); // Add a default ruleset, e.g., DND5e
    }
    ~MainMenuWindowView() = default;

    // Function to update the view
    void update(std::shared_ptr<GLFWwindow>) override;

protected:
    MainMenuWindowController &_controller;
    std::vector<std::shared_ptr<IRuleSet>> ruleSets;

    friend class MainMenuWindowController;

    // New game dialogWindow
    bool _showNewGamePopup = false;
    std::string _campaignName = std::string();
    int _selectedRuleIndex = 0;
    void handleNewGamePopup();

    // Load game dialogWindow
    bool _showLoadGamePopup = false;
    int _selectedLoadGameIndex = 0;
    void handleLoadGamePopup();

    void openEditor(Campaign campaign);

    MainMenuOption _currentChoice = MainMenuOption::None;
};