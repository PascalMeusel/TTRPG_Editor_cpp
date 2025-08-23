cmake_minimum_required(VERSION 3.14)
cmake_policy(SET CMP0135 NEW) # Recommended for FetchContent timestamps
cmake_policy(SET CMP0072 NEW) # Recommended for modern OpenGL-Finden
project(TTRPG_Editor_cpp VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# --- GLFW ---
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(extern/glfw)

# --- OpenGL ---
find_package(OpenGL REQUIRED)

# --- SQLiteCpp ---
set(SQLITECPP_RUN_CPPCHECK OFF CACHE BOOL "" FORCE)
set(SQLITECPP_RUN_CPPLINT OFF CACHE BOOL "" FORCE)

# WORKAROUND: Tell CMake to handle SQLiteCpp's old CMakeLists.txt with modern policies
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

FetchContent_Declare(
    SQLiteCpp
    GIT_REPOSITORY https://github.com/SRombauts/SQLiteCpp.git
    GIT_TAG        3.3.0
)
FetchContent_MakeAvailable(SQLiteCpp)

# --- Main Executable ---
add_executable(TTRPG_Editor
    main.cpp
    Application.cpp
    Views/MainMenu/MainMenuWindowView.cpp
    Views/Editor/EditorWindowView.cpp
    Models/DataBaseManager.cpp
    extern/imgui/imgui.cpp
    extern/imgui/imgui_draw.cpp
    extern/imgui/imgui_widgets.cpp
    extern/imgui/imgui_tables.cpp
    extern/imgui/imgui_demo.cpp
    extern/imgui/misc/cpp/imgui_stdlib.cpp
    extern/imgui/backends/imgui_impl_glfw.cpp
    extern/imgui/backends/imgui_impl_opengl3.cpp
)

# --- Includes ---
target_include_directories(TTRPG_Editor PRIVATE
    .
    extern/imgui 
    extern/imgui/backends
)

# --- Compile Definitions ---
target_compile_definitions(TTRPG_Editor PRIVATE
    -DSQLITE_THREADSAFE=1
    -DSQLITE_ENABLE_COLUMN_METADATA
)

# --- Linking ---
target_link_libraries(TTRPG_Editor PRIVATE
    glfw
    OpenGL::GL
    SQLiteCpp
)