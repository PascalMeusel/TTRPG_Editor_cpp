#pragma once
#include <memory>

// Forward declarations
class CharacterCreatorController;

class CharacterCreatorView
{
private:
    CharacterCreatorController& _controller;

public:
    explicit CharacterCreatorView(CharacterCreatorController& controller);

    // Note the `bool* p_open` parameter. This is the key to self-closing.
    void update(bool* p_open);
};