#pragma once

#include "imgui.h"
#include <vector>
#include <string>

#include <iostream>

// Helper function for creating dynamic combo boxes
inline void RenderCombo(const char *label, const std::vector<std::string> &items, std::string &current_item)
{
    if (ImGui::BeginCombo(label, current_item.c_str()))
    {
        for (const auto &item : items)
        {
            const bool is_selected = (current_item == item);
            if (ImGui::Selectable(item.c_str(), is_selected))
            {
                std::cout << "Setting the reference. Was " << current_item << " and changed to " << item << std::endl;
                current_item = item;
            }
            if (is_selected)
            {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }
}
