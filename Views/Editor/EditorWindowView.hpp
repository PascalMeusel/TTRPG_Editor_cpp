#pragma once
#include <imgui.h>
#include <GLFW/glfw3.h>

#include "../IWindowView.hpp"
#include "../../Models/Campaign/Campaign.hpp"

class Application;

class EditorView : public IWindowView
{
public:
    EditorView(std::shared_ptr<Application> parent)
        : IWindowView(parent)
    {
    }
    ~EditorView() = default;

    // Function to update the view
    void update(GLFWwindow* window) override;

    void setCurrentCampaign(Campaign currentCampaign);

private:
    Campaign _currentCampaign;
};