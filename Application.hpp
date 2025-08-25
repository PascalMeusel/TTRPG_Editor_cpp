#pragma once
#include <vector>
#include <memory>

#include "Views/IWindowView.hpp"
#include "WindowTypes.hpp"

#include "Controllers/MainMenu/MainMenuWindowController.hpp"
#include "Controllers/Editor/EditorWindowController.hpp"
#include "Models/DataBaseManager.hpp"
// Forward declare GLFWwindow to avoid including glfw3.h in the header
struct GLFWwindow;

class Application : public std::enable_shared_from_this<Application>
{
public:
    Application();
    ~Application();

    void run();
private:
    void Initialize();
    void Shutdown();

    std::shared_ptr<GLFWwindow> mainWindow;
    std::shared_ptr<IWindowController> activeWindowController;

    std::shared_ptr<EditorWindowController> editor;
    std::shared_ptr<MainMenuWindowController> mainMenu;
};