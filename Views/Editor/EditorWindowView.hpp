#pragma once
#include <imgui.h>
#include <GLFW/glfw3.h>

#include "../IWindowView.hpp"
#include "Models/DataBaseManager.hpp"

class EditorWindowController;

class EditorWindowView : public IWindowView
{
public:
    EditorWindowView() = delete;
    EditorWindowView(EditorWindowController &controller);
    ~EditorWindowView() = default;
    // Function to update the view
    void update(std::shared_ptr<GLFWwindow> window) override;

private:
    EditorWindowController &_controller;
    
    friend class EditorWindowController;
};