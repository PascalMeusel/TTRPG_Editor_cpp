#pragma once
#include <vector>
#include <memory>

#include "Views/IWindowView.hpp"

// Forward declare GLFWwindow to avoid including glfw3.h in the header
struct GLFWwindow;

class Application {
public:
    Application();
    ~Application();

    void Run();

private:
    void Initialize();
    void Shutdown();

    // Helper function to create the main menu bar
    void RenderMainMenu();

    GLFWwindow* m_Window;
    std::vector<std::unique_ptr<IWindowView>> m_Views;
};