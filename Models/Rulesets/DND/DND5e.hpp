#pragma once

#include "../IRuleSet.hpp"

class DND5e : public IRuleSet
{
public:
    DND5e() = default;
    ~DND5e() override = default;

    // Override the getName method to return the ruleset name
    const char *getName() const override
    {
        return "Dungeons & Dragons 5th Edition";
    }

    // Override methods to return attributes

    const bool levelsExist() const override { return true; }

    const std::vector<std::string> getAttributes() const override
    {
        return {"Strength", "Dexterity", "Constitution", "Intelligence", "Wisdom", "Charisma"};
    }
    const std::vector<std::string> getClasses() const override
    {
        return {"Fighter", "Wizard", "Rogue", "Cleric", "Druid", "Paladin", "Ranger", "Bard"};
    }
    const std::vector<std::string> getRaces() const override
    {
        return {"Human", "Elf", "Dwarf", "Halfling", "Dragonborn", "Tiefling"};
    }
    // Additional methods specific to DND5e can be added here
};