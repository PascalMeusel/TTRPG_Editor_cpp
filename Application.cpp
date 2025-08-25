#include "Application.hpp"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <iostream>
// Include our concrete window views
// You can include other windows here, e.g., #include "SettingsWindowView.hpp"

Application::Application() : mainWindow(nullptr)
{
    try
    {
        Initialize();
    }
    catch (const std::exception &e)
    {
        // A simple way to catch initialization errors
        throw e;
    }
}

Application::~Application()
{
    Shutdown();
}

// Deleter function
void destroyGlfwWindow(GLFWwindow *window)
{
    glfwDestroyWindow(window);
}

void Application::Initialize()
{
    std::cout << "Anwendung wird initialisiert..." << std::endl;
    if (!glfwInit())
        throw std::runtime_error("Failed to initialize GLFW");

    const char *glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *raw_window = glfwCreateWindow(1280, 720, "My ImGui App", nullptr, nullptr);
    if (!raw_window)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
    mainWindow = std::shared_ptr<GLFWwindow>(raw_window, destroyGlfwWindow);
    glfwMaximizeWindow(mainWindow.get());
    glfwMakeContextCurrent(mainWindow.get());
    glfwSwapInterval(1); // Enable vsync

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui::StyleColorsDark();
    ImGuiStyle &style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplGlfw_InitForOpenGL(mainWindow.get(), true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // --- Create and add our window views ---
    editor = std::make_shared<EditorWindowController>();
    mainMenu = std::make_shared<MainMenuWindowController>();
    activeWindowController = mainMenu;
    editor->setWindowOpacity(false);
}

void Application::run()
{
    while (!glfwWindowShouldClose(mainWindow.get()))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // --- Create the main, full-screen dockspace ---
        const ImGuiViewport *viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

        // Begin the dockspace window
        ImGui::Begin("MainDockSpace", nullptr, window_flags);
        ImGui::PopStyleVar(3); // Pop the 3 style vars we pushed

        // Create the actual dockspace ID and layout
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);

        if (activeWindowController == editor)
        {
            if (ImGui::BeginMenuBar())
            {
                if (ImGui::BeginMenu("File"))
                {
                    if (ImGui::MenuItem("Exit"))
                        glfwSetWindowShouldClose(mainWindow.get(), true);
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("Widgets"))
                {
                    if (ImGui::MenuItem("Character Creator"))
                        editor->showCharacterCreator();
                    if (ImGui::MenuItem("Character Sheet"))
                    {
                        // editor->showCharacterCreator(); // Uncomment when ready
                    }
                    ImGui::EndMenu();
                }
                // Add other editor-specific menus here (e.g., "Edit", "View", "Assets")
                ImGui::EndMenuBar();
            }
        }

        // Update all of our registered window views
        if (activeWindowController->getWindowActive())
        {
            activeWindowController->update(mainWindow);
        }
        else
        {
            switch (activeWindowController->getWindowType())
            {
            case WindowTypes::MainMenuWindow:
            {
                activeWindowController = editor;
                editor->setCurrentCampaign(DatabaseManager::getInstance()->getActiveCampaign());
                break;
            }
            case WindowTypes::EditorWindow:
            {
                activeWindowController = mainMenu;
                break;
            }
            }
            activeWindowController->setWindowOpacity(true);
            activeWindowController->update(mainWindow);
        }
        // You can also render ImGui's built-in demo window
        ImGui::ShowDemoWindow();

        ImGui::End();

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(mainWindow.get(), &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow *backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        glfwSwapBuffers(mainWindow.get());
    }
}

void Application::Shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(mainWindow.get());
    glfwTerminate();
}
