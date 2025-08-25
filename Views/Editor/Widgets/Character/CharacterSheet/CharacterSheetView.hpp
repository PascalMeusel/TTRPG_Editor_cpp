#pragma once

#include "Views/Editor/Widgets/DockableWidget.hpp"

class CharacterSheetView : public DockableWidget
{
public:
    CharacterSheetView();
    ~CharacterSheetView() = default;

protected:
    void draw() override;
};