#ifndef Block_hpp
#define Blocks_hpp

#include "Silly_Core.hpp"

class Blocks : public Silly_Core{
    using Silly_Core::Silly_Core;

    Atlas* atlas;
    float square_speed = 0.1;
    const int num_squares = 5;
    Object* Init_Square(int x);
public:
    void SetUp();
    void Update();
};

class Square_Bh : public Behaviour{
public:
    Square_Bh(Object* obj, float p_speed, const Uint32& delta_t);
    void execute() override;
private:
    float speed;
    Object* object;
    const Uint32& delta_time;
};

#endif // Blocks_hpp
