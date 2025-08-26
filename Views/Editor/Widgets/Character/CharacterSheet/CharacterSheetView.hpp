#pragma once

#include <vector>

#include "Views/Editor/Widgets/DockableWidget.hpp"

class CharacterSheetController;

class CharacterSheetView : public DockableWidget
{
public:
    CharacterSheetView(CharacterSheetController &controller);
    ~CharacterSheetView() = default;

protected:
    CharacterSheetController &_controller;
    void draw() override;
};