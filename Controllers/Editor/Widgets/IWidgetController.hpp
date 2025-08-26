#pragma once
#include <memory>
#include <GLFW/glfw3.h>
#include "Views/Editor/Widgets/DockableWidget.hpp"
// An interface for all editor widgets
class IWidgetController
{
protected:
    std::shared_ptr<DockableWidget> widget;

public:
    virtual ~IWidgetController() = default;

    // The main update loop for the widget's view
    virtual void update(std::shared_ptr<GLFWwindow> window) = 0;

    // Public methods to control visibility
    void show() { widget->show(); }
    void hide() { widget->hide(); }
    bool isOpen() const { return widget->isVisible(); }

    virtual void toggleVisibility() { widget->toggleVisibility(); }
};