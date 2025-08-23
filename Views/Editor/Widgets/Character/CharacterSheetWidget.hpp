#pragma once

#include "../DockableWidget.hpp"

class CharacterSheetWidget : public DockableWidget
{
public:
    CharacterSheetWidget();
    ~CharacterSheetWidget() = default;

protected:
    void draw() override;
};