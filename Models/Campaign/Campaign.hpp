#pragma once

#include "Models/Rulesets/IRuleSet.hpp"
#include <string>
#include <memory>

struct Campaign
{
    long long id = -1;
    std::string name;
    std::shared_ptr<IRuleSet> ruleSet;
};