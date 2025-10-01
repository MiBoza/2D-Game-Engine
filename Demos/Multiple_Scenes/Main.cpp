#include "Silly_Core.hpp"
#include "Counter.hpp"
#include "Swirl.hpp"

template <typename T>
void Run_State(T* state, Window_Data& window_data){
    try{
        state = new T(window_data);
        state->SetUp();
        int running = window_data.state;
        while(window_data.state == running){
            state->input->Input_Update();
            state->Timing();
            state->Update();
            state->Components();
        }
        delete state;
    }
    catch(const std::exception& e){
        puts( e.what() );
        if(window_data.flags & SCENE_READY)
            delete state;
        window_data.state = FINISH;
    }
}

int main(){
    Window_Data window_data("Multiple scenes", SWIRL);
    window_data.Set_Font_Path("../../Include/font.ttf");
    window_data.Create_Window();
    Counter* counter;
    Swirl* swirl;

    while(window_data.state != FINISH){
        switch(window_data.state){
        case COUNTER:
            Run_State(counter, window_data);
            break;
        case SWIRL:
            Run_State(swirl, window_data);
            break;
        }
    }

    return 0;
}
