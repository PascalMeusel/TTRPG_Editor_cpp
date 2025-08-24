#pragma once

#include "../../Models/Campaign/Campaign.hpp"

class EditorWindowController
{
public:
    EditorWindowController() = default;
    ~EditorWindowController() = default;


    void inline setCurrentCampaign(Campaign currentCampaign) { _currentCampaign = currentCampaign; }
    Campaign inline getCurrentCampaign() const { return _currentCampaign; }
private:
    Campaign _currentCampaign;
};