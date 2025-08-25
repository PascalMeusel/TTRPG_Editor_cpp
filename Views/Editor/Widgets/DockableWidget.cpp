#include "DockableWidget.hpp"

DockableWidget::DockableWidget(const std::string& title, ImGuiWindowFlags flags)
    : _title(title), _isVisible(true), _flags(flags)
{
    // You can add any other default setup here
}

void DockableWidget::update()
{
    // If the window is not visible, do nothing.
    if (!_isVisible)
        return;

    // The ImGui::Begin call creates the window.
    // The second parameter is a pointer to a boolean which, if the user
    // closes the window, will be set to false. We use our _isVisible member here.
    if (ImGui::Begin(_title.c_str(), &_isVisible, _flags))
    {
        // If the window is not collapsed, call the derived class's draw method.
        draw();
    }
    // Always call End, even if Begin returned false.
    ImGui::End();
}

void DockableWidget::show()
{
    _isVisible = true;
}

void DockableWidget::hide()
{
    _isVisible = false;
}

bool DockableWidget::isVisible() const
{
    return _isVisible;
}

void DockableWidget::toggleVisibility()
{
    _isVisible = !_isVisible;
}