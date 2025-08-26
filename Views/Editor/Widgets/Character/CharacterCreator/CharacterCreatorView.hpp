#pragma once
#include <memory>
#include "Views/Editor/Widgets/DockableWidget.hpp"
// Forward declarations
class CharacterCreatorController;

class CharacterCreatorView : public DockableWidget
{

public:
    friend class CharacterCreatorController;
    explicit CharacterCreatorView(CharacterCreatorController& controller);
protected:
    void draw() override;
    CharacterCreatorController& _controller;
};