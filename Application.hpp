#pragma once
#include <vector>
#include <memory>

#include "Views/IWindowView.hpp"

#include "Views/MainMenu/MainMenuWindowView.hpp"
#include "Views/Editor/EditorWindowView.hpp"
// Forward declare GLFWwindow to avoid including glfw3.h in the header
struct GLFWwindow;

enum class WindowTypes
{
    MainMenuWindow,
    EditorWindow
};

class Application : public std::enable_shared_from_this<Application>
{
public:
    Application();
    ~Application();

    void Run();

    void activateNewWindow(WindowTypes windowToActivate);

private:
    void Initialize();
    void Shutdown();

    GLFWwindow *m_Window;

    std::shared_ptr<EditorView> editor;
    std::shared_ptr<MainMenuWindowView> mainMenu;
    std::vector<std::shared_ptr<IWindowView>> m_Views;
};