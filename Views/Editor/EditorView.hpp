#pragma once
#include <imgui.h>
#include <GLFW/glfw3.h>

#include "../IWindowView.hpp"

class EditorView : public IWindowView
{
public:
    EditorView() = default;
    ~EditorView() = default;

    // Function to update the view
    void update(GLFWwindow* window) override;
};