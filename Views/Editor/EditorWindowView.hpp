#pragma once
#include <imgui.h>
#include <GLFW/glfw3.h>

#include "../IWindowView.hpp"
#include "EditorWindowController.hpp"

class Application;

class EditorWindowView : public IWindowView
{
public:
    EditorWindowView() { controller = std::make_shared<EditorWindowController>(); };
    ~EditorWindowView() = default;

    // Function to update the view
    void update(GLFWwindow* window) override;

private:
    std::shared_ptr<EditorWindowController> controller;
};