#ifndef Swirl_hpp
#define Swirl_hpp

#include "Silly_Core.hpp"
#include "Declarations.hpp"

class Swirl_Input : public Input_Base{
    void KeyDown(short& key);
public:
    short left_k;

    using Input_Base::Input_Base;
    void Input_Update() override;
};

class Swirl : public Silly_Core{
    using Silly_Core::Silly_Core;

    Atlas* atlas;
    Swirl_Input* my_input;

    Object *circle;
    Object *square1, *square2, *square3, *square4, *square5;

    const Vector2& size = {20, 20};
    Object* Init_Object(int pos);
public:
    void SetUp();
    void Update();
};

#endif // Swirl_hpp
