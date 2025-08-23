#include "Application.hpp"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <stdexcept>

// Include our concrete window views
// You can include other windows here, e.g., #include "SettingsWindowView.hpp"

Application::Application() : m_Window(nullptr)
{
    Initialize();
}

Application::~Application()
{
    Shutdown();
}

void Application::Initialize()
{
    if (!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    const char *glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = glfwCreateWindow(1280, 720, "My ImGui App", nullptr, nullptr);
    if (!m_Window)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMaximizeWindow(m_Window);
    glfwMakeContextCurrent(m_Window);
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

    ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // --- Create and add our window views ---
    editor = std::make_shared<EditorView>(shared_from_this());
    mainMenu = std::make_shared<MainMenuWindowView>(shared_from_this());
    m_Views.push_back(editor);
    m_Views.push_back(mainMenu);

    editor->isVisible = false;
}

void Application::Run()
{
    while (!glfwWindowShouldClose(m_Window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Enable the docking space
        ImGui::DockSpaceOverViewport();

        // Update all of our registered window views
        for (auto &view : m_Views)
        {
            // Pass the main window pointer to each view's update method
            view->update(m_Window);
        }

        // You can also render ImGui's built-in demo window
        ImGui::ShowDemoWindow();

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(m_Window, &display_w, &display_h);
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

        glfwSwapBuffers(m_Window);
    }
}

void Application::activateNewWindow(WindowTypes windowToActivate)
{
    switch (windowToActivate)
    {
    case WindowTypes::EditorWindow:
    {
        editor->setCurrentCampaign(DatabaseManager::getInstance()->getActiveCampaign());
        editor->isVisible = true;
    }
    case WindowTypes::MainMenuWindow:
    {

    }
    
    default:
        break;
    }
}

void Application::Shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(m_Window);
    glfwTerminate();
}
