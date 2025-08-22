#include "Application.hpp"
#include <iostream>

int main(int, char**) {
    try {
        Application app;
        app.Run();
    } catch (const std::exception& e) {
        // A simple way to catch initialization errors
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}