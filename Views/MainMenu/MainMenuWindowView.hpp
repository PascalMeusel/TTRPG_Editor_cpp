#pragma once
#include  <vector>
#include <string>
#include <tuple>
#include <memory>

#include <imgui.h>
#include <GLFW/glfw3.h>

#include "../IWindowView.hpp"
#include "../../Models/Rulesets/DND/DND5e.hpp"

class MainMenuWindowView : public IWindowView
{
public:
    MainMenuWindowView();
    ~MainMenuWindowView() = default;

    // Function to update the view
    void update(GLFWwindow* window) override;

protected:
    // You can add protected members here if needed for internal state management
    std::vector<std::unique_ptr<IRuleSet>> ruleSets;
};