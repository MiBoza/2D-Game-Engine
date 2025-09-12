#include "Aggregate.hpp"
#include "Counter.hpp"
#include "Swirl.hpp"

int main(){
    Window_Data window_data("Multiple scenes", SWIRL);
    Counter* counter;
    Swirl* swirl;

    while(window_data.state != FINISH){
        switch(window_data.state){
        case COUNTER:
            counter = new Counter(window_data);
            counter->SetUp();
            while(window_data.state == COUNTER){
                counter->input->Input_Update();
                counter->Timing();
                counter->Update();
                counter->Components();
            }
            delete counter;
            break;
        case SWIRL:
            swirl = new Swirl(window_data);
            swirl->SetUp();
            while(window_data.state == SWIRL){
                swirl->input->Input_Update();
                swirl->Timing();
                swirl->Update();
                swirl->Components();
            }
            delete swirl;
            break;
        }
    }

    return 0;
}
