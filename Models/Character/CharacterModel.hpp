#pragma once
#include <string>
#include <vector>
#include <map>

struct CharacterModel
{
    char nameBuffer[128] = "Hero";
    int level = 1;

    // Use a map to store attributes dynamically. Key = attribute name, Value = score.
    std::map<std::string, int> attributes;

    // Store the selected class and race as strings
    std::string selectedClass;
    std::string selectedRace;
};
