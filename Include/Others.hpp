#ifndef Others_hpp
#define Others_hpp

#include <SDL2/SDL.h>
#include "Vector2.hpp"

void Print_Rect(const char* string, const SDL_Rect& rect);

class Behaviour{
public:
	virtual void execute() = 0;
	virtual ~Behaviour() = default;
};

class Event{
public:
    Behaviour* behaviour;
    int start, end;
};

class Input_Base{
protected:
	SDL_Event event;
	short& state;
public:
	Input_Base(short& p_state);
	virtual void Input_Update() = 0;
    virtual ~Input_Base() = default;
};

class Default_Input : public Input_Base{
    using Input_Base::Input_Base;
    void Input_Update() override;
};

enum Input_Signal{
	RESET    = 0x0,
	CURRENT  = 0x1,
	PREVIOUS = 0x2,
	POSEDGE  = 0x4,
};

enum Object_Flags{
    EMPTY     = 0x00,
    OUTDATED  = 0x01,
    DELETED   = 0x02,
    IMAGE     = 0x04,
    TEXT      = 0x08,
    COPYEX    = 0x10,
    BEHAVIOUR = 0x20,
    RIGIDBODY = 0x40
};

enum Window_Flags{
	FULLSCREEN	= 0x1,
	SCENE_READY	= 0x2
};

class Finish : public Behaviour{
    short& state;
public:
    Finish(short& p_state);
    void execute() override;
};

struct Texture_Wrapper{
    SDL_Texture* texture;
    SDL_Rect destination;
    SDL_Rect source;

    Texture_Wrapper();
};

class Missing_File : public std::exception{
	char* message;
public:
	Missing_File(const char* path);
	virtual const char* what() const throw();
	~Missing_File();
};

#endif // Others_hpp
