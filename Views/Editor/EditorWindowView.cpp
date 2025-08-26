#include "EditorWindowView.hpp"
#include "Controllers/Editor/EditorWindowController.hpp"
#include "imgui.h"

#include <iostream>

EditorWindowView::EditorWindowView(EditorWindowController &controller) : _controller(controller)
{
}

void EditorWindowView::update(std::shared_ptr<GLFWwindow> window)
{
    
}