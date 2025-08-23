#pragma once
#include <imgui.h>
#include <GLFW/glfw3.h>

#include "../IWindowView.hpp"
#include "../../Models/Campaign/Campaign.hpp"

class Application;

class EditorWindowView : public IWindowView
{
public:
    EditorWindowView() = default;
    ~EditorWindowView() = default;

    // Function to update the view
    void update(GLFWwindow* window) override;

    void setCurrentCampaign(Campaign currentCampaign);

private:
    Campaign _currentCampaign;
};