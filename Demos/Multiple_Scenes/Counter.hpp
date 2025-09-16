#ifndef Counter_hpp
#define Counter_hpp

#include "Silly_Core.hpp"
#include "Declarations.hpp"

class Counter_Input : public Input_Base{
    void KeyDown(short& key);
public:
    short right_k;

    using Input_Base::Input_Base;
    void Input_Update() override;
};

class Counter : public Silly_Core{
    using Silly_Core::Silly_Core;

    Object* box;
    Atlas* atlas;
    Counter_Input* my_input;
    char box_buffer[11];
    int count = 1;
    int last_change;
public:
    void SetUp();
    void Update();
};

#endif // Counter_hpp
