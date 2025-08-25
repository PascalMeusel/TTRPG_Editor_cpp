#pragma once
#include <memory>
#include "Views/Editor/Widgets/DockableWidget.hpp"
// Forward declarations
class CharacterCreatorController;

class CharacterCreatorView : DockableWidget
{

public:
    friend class CharacterCreatorController;
    explicit CharacterCreatorView(CharacterCreatorController& controller);

    // Note the `bool* p_open` parameter. This is the key to self-closing.
    void update(bool* p_open);
private:
    CharacterCreatorController& _controller;
};