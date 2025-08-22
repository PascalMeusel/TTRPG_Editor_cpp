#pragma once

#include <vector>
#include <string>

class IRuleSet {
public:
    virtual ~IRuleSet() = default;

    // Pure virtual function to get the name of the ruleset
    virtual const char* getName() const = 0;

    virtual const std::vector<std::string> getAttributes() const = 0;
    virtual const std::vector<std::string> getClasses() const = 0;
    virtual const std::vector<std::string> getRaces() const = 0;
};