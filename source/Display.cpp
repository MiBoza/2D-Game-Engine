#include "Aggregate.hpp"

void Aggregate::Components(){
    //Looks through the list of objects and
    //Renders or calculates physics as required

    SDL_RenderClear(renderer);
    typename std::list<Object*>::iterator it = objects.begin();
    for(; it != objects.end();){
        Object* object = *it;

        if(object->flags & DELETED){
            Destroy_Object(object);
            it = objects.erase(it);
            continue;
        }
        ++it;
        if(object->flags & RENDER)
            Render(object);
        if(object->rb){
            object->rb->Rigid_Update();
        }
    }
    SDL_RenderPresent(renderer);
}

// const static int Letter_pos[] = {0, 19, 37, 58, 89, 116, 153, 186, 202, 220, 239, 266, 294, 311, 332, 347, 370, 399, 425, 453, 480, 509, 536, 564, 592, 619, 648, 664, 682, 710, 738, 764, 789, 826, 859, 888, 919, 952, 979, 1004, 1038, 1070, 1086, 1109, 1138, 1165, 1204, 1236, 1272, 1300, 1336, 1364, 1389, 1419, 1449, 1478, 1518, 1546, 1575, 1604, 1621, 1643, 1663, 1689, 1714, 1732, 1761, 1789, 1814, 1843, 1869, 1890, 1921, 1950, 1962, 1984, 2011, 2028, 2068, 2096, 2126, 2154, 2184, 2206, 2229, 2252, 2279, 2305, 2340, 2365, 2392, 2416, 2445, 2465, 2487};
// const static int Letter_size[] = {17, 5, 10, 20, 16, 26, 23, 4, 8, 9, 17, 17, 6, 9, 5, 13, 17, 10, 17, 16, 18, 16, 17, 17, 16, 17, 5, 7, 17, 17, 17, 14, 27, 22, 17, 19, 20, 14, 14, 21, 19, 9, 9, 19, 15, 24, 19, 23, 16, 23, 18, 16, 19, 19, 21, 31, 20, 20, 17, 8, 13, 8, 17, 16, 8, 16, 17, 14, 16, 16, 13, 17, 16, 4, 9, 16, 4, 27, 16, 18, 17, 17, 12, 13, 12, 16, 18, 26, 17, 18, 14, 12, 3, 12, 17};


void Aggregate::Render(Object* obj){
    if(obj->outdated)
        obj->Update_Dest();
	// if(obj->text)
	// 	RenderText(object->text);
    if(obj->flags & COPYEX){
        SDL_RenderCopyEx(renderer, obj->texture, &obj->source, &obj->destination,
            obj->rotation_angle, NULL, obj->flip);
    }
    else{
        SDL_RenderCopy(renderer, obj->texture, &obj->source, &obj->destination);
    }
}
