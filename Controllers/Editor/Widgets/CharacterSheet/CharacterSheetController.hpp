#pragma once

#include "Models/Campaign/Campaign.hpp"
#include "Views/Editor/Widgets/Character/CharacterSheet/CharacterSheetView.hpp"
#include "Controllers/Editor/Widgets/IWidgetController.hpp"

class CharacterSheetController : IWidgetController
{
public:
CharacterSheetController(Campaign &currentCampaign);

private:
    std::unique_ptr<CharacterSheetView> view;
    Campaign &_currentCampaign;
};