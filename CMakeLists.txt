cmake_minimum_required(VERSION 3.14)
cmake_policy(SET CMP0135 NEW) # Empfohlen für FetchContent-Timestamps
cmake_policy(SET CMP0072 NEW) # Empfohlen für modernes OpenGL-Finden
project(TTRPG_Editor_cpp VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

set(SQLITECPP_RUN_CPPCHECK OFF CACHE BOOL "" FORCE)
set(SQLITECPP_RUN_CPPLINT OFF CACHE BOOL "" FORCE)
add_subdirectory(SQLiteCpp)

add_executable(TTRPG_Editor
    main.cpp
    Application.cpp
    Views/MainMenu/MainMenuWindowView.cpp
    Views/Editor/EditorWindowView.cpp
    Models/DataBaseManager.cpp
    imgui/imgui.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_demo.cpp
    imgui/misc/cpp/imgui_stdlib.cpp
    imgui/backends/imgui_impl_glfw.cpp
    imgui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(TTRPG_Editor PRIVATE
    .
    imgui 
    imgui/backends
    SQLiteCpp
    include_directories(${SQLite3_INCLUDE_DIRS})
)

target_compile_definitions(TTRPG_Editor PRIVATE
    -DSQLITE_THREADSAFE=1
    -DSQLITE_ENABLE_COLUMN_METADATA
)

target_link_libraries(TTRPG_Editor PRIVATE
    glfw
    OpenGL::GL
    SQLiteCpp
)