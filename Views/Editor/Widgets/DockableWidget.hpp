#pragma once

#include "imgui.h"
#include <string>

// An abstract base class for any window that needs to be dockable,
// movable, and resizable.
class DockableWidget
{
public:
    // Constructor allows setting a title and initial flags.
    // By default, it's set to auto-resize to its content.
    DockableWidget(const std::string& title, ImGuiWindowFlags flags = ImGuiWindowFlags_AlwaysAutoResize);
    
    // Virtual destructor
    virtual ~DockableWidget() = default;

    // This is the main public method to be called in your application loop.
    // It handles the Begin/End calls and calls the internal draw method.
    void render();

    // Methods to control the visibility of the window
    void show();
    void hide();
    bool isVisible() const;
    void toggleVisibility();

protected:
    // Pure virtual function that derived classes MUST implement.
    // This is where you will put all your ImGui widgets for a specific feature.
    virtual void draw() = 0;

private:
    std::string _title;
    bool _isVisible;
    ImGuiWindowFlags _flags;
};