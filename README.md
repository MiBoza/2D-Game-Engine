<h3 align="center">Silly Game Engine</h3>

---

## Contents

* [This Project](#This)
* [Installation](#Installation)
* [Running Demos](#Running)
* [Features](#Features)
* [About Demos](#Demos)
* [Function Declarations](#Declarations)

## This Project <a name="This"></a>

The aim of this project is to write a game engine that is as intuitive to use as possible while being entirely controlled with code. Aside from asset creation, all aspects of the engine and the applications built on top should be available as human readable text to copy, edit, remove, etc. without the need to navigate a GUI.

## Installation <a name="Installation"></a>

1. Clone this repository:

	```
	git clone git@github.com:MiBoza/Silly-Engine.git Your_Project
	cd Your_Project
	```

2. Install development SDL2 libraries:

    ```
	sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev
    ```

## Running Demos <a name="Running"></a>

1. Display available demos to run, choose one and change into its directory:

	```
	ls Demos
	cd Demos/Open_Window
	```

2. Compile and run:

    ```
	make run_release
    ```

## Features <a name="Features"></a>

* Create Window
* Handle Quit Event
* Flesh Out Scenes
* Load Textures
* Add Object
* Makefile Build System


## About Demos <a name="Demos"></a>

This section will go into great detail about the mechanics demonstrated in my demos. You probably already know at least half of the contents of this section. I wrote it as a last resort if someone is utterly lost. To quickly see what the engine has to offer, I recommend looking at the [function declarations](#Declarations). If a function sounds useful and you want to see it in context, try finding a demo that includes it and read the code. Then, if you're still confused, come to this section.

For example, to search for uses of Set_Size() among the demos, run:

```
grep -rn --exclude=*.o* "Set_Size" Demos
```

1. ### Open_Window
	This is the simplest demonstration included. It's a good first step to learn the basics. In my case, I always load it whenever I break something inside the engine and need to debug.
	
	Window_Data is a class that holds an applications information that transcends changes in scene. For example, if the game starts with a menu and then switches to a minugame,  these are two different scenes. All scenes need access to the application's window, name, runtime, etc. and window_data allows them to share it.
	
	The engine expects to find Include/font.ttf, but I moved the file to the root of the repository.  For this reason, I update the font path in my demos with Set_Font_Path.
	
	Default_Input inherits from Input_Base and provides basic functionality for non-interactive applications like this. While running, if the user tries to close the application through the x-button or alt+F4, Default_Input will change the state to 0 and the loop will end.
	
	The code here boils down to the following: Open a window called ”Window Title”, while the game is running ask if the user wants to quit. If so, quit. Otherwise, draw to the window. After quitting, delete the game object and release its memory.
	
	I don't see much room for creativity with this one, but if you do want to change something in one of my demos and see what happens, I recommend compiling with:
	
	```
	make debug.obj
	```

	This results in a larger executable with debug symbols and address_sanitizer so you can run the program with gdb and get alerts for memory leaks or other memory errors.

2. ### Loading_Sprites

	An object is any entity you want to have on the game. It has a position and a display size. You can also give it a sprite (image) and render it to the screen or it can remain invisible. This demo will show you how to initialise objects and use them to display images.

	To add content to a scene, write a class that inherits from Silly_Core to hold any data you want to share implicitly between functions. Especially SetUp and Update. Like in most (if not all) engines, you'll probably want a SetUp function to declare what objects you want in your scene and an Update function that runs every frame and changes things over time.
	
	Load images to memory with texture_manager->Load(path, rows, columns). By default, rows and columns = 1 which allows for loading a single image from path. Alternatively, load an atlas with multiple images in a grid like Assets/Atlas.png and split it by indicating the number of rows and columns.

	From now on, it is convenient to make a class that inherits from Silly_Core in order to easily share data as well as use Silly_Core functions. This class is called Game for this demo.
	
	One of the member functions of the Game class is SetUp. Loading assets and declaring conditions at the beginning of a scene such as object sizes and positions should only be done once and belong in the SetUp function. Another member function of the Game class is Update. This function handles changes over time, but it is not used in this demo. It is explored further in [Objects_Swirl](#Objects_Swirl), but declaring it as an empty function will suffice for now.
	
	The result is a static image with a square, cylinder, cube and split cone displayed at the coordinates specified by the SetUp function. Feel free to change these coordinates in the code and see how the objects move after recompiling; or add your own images into assets, load them into a new object and watch it appear on the scene.
	
2. ### Objects_Swirl <a name="Objects_Swirl"></a>
	
## Function Declarations <a name="Declarations"></a>

* #### Include/Object.hpp
	* void Object::Set_Pos(const Vector2& p_pos);
	* void Object::Set_Size(const Vector2& p_size);
    * void Object::Set_Behaviour(Behaviour* behaviour);
    * void Object::Flip_Horizontally();
    * void Object::Flip_Vertically();
    * Vector2 Object::Get_Pos();
    * Vector2 Object::Get_Size();
    * void Object::Update_Dest();
    * void Object::Destroy();

* #### Include/Others.hpp
	* virtual void Behaviour::execute() = 0;
	* virtual Behaviour::~Behaviour() = default;
	* Input_Base::Input_Base(short& p_state);
	* virtual void Input_Base::Input_Update() = 0;
    * void Finish::execute() override;
    * Texture_Wrapper::Texture_Wrapper();
    * Missing_File::Missing_File(const char* path);
    * virtual const char* Missing_File::what() const throw();
    * Missing_File::~Missing_File();


* #### Include/RigidBody.hpp
	* void RigidBody::Rigid_Update();
	* void RigidBody::Collide(const Line& line);
	* void RigidBody::Set_Pos(const Vector2& p_pos);
	* void RigidBody::Set_Size(const Vector2& p_size);
	* Vector2 RigidBody::Get_Pos();
	* Vector2 RigidBody::Get_Size();
	

* #### Include/Silly_Core.hpp
	* Silly_Core::Silly_Core(Window_Data& p_window_data);
	* Silly_Core::~Silly_Core();
	* void Silly_Core::Components();
	* void Silly_Core::Event_Handler();
	* void Silly_Core::Timing();
	* Object* Silly_Core::AddObject(RigidBody* p_rb = nullptr);
	* Object* Silly_Core::AddEXObject(RigidBody* p_rb = nullptr);
	* Object* Silly_Core::AddTextBox(const char line[] = " ");
	* void Silly_Core::Set_Text(Object* obj, const char line[]);
	* void Silly_Core::Set_Text(Object* obj, const std::string line);
	* RigidBody* Silly_Core::AddRigidBody(Object* object = nullptr);
	* void Silly_Core::AddEvent(Event&& event);
	* void Silly_Core::Set_Framerate(float framerate);
	* void Silly_Core::Timelimit_Thread(int miliseconds);
	* void Silly_Core::Timelimit_Event(int miliseconds);
	

* #### Include/TextureManager.hpp
	* void Atlas::Assign_Sprite(Object* obj, int p_row, int p_column);
	* void Atlas::Assign_Sprite(Object* obj, int pos = 0);
	* void Atlas::Assign_Sprite(RigidBody* rb, int row, int column);
	* void Atlas::Assign_Sprite(RigidBody* rb, int pos = 0);
	* Atlas* TextureManager::Load(const char* path, int rows = 1, int columns = 1);
	* TextureManager::TextureManager(const Window_Data& window_data);
	* TextureManager::~TextureManager();
	
* #### Include/Vector2.hpp
	* void Vector2::Normalise();
	* float Magnitude_Squared(const Vector2& u);
	* float Magnitude(const Vector2& u);
	* float Angle(const Vector2& u);
	* float Angle_Degrees(const Vector2& u);
	* Vector2 Polar_Constructor(float magnitude, float angle);
	* Vector2 Degree_Constructor(float magnitude, float degrees);
	* Vector2 operator-(const Vector2& u, const Vector2& v);
	* Vector2 operator+(const Vector2& u, const Vector2& v);
	* float operator*(const Vector2& u, const Vector2& v);
	* Vector2 operator*(const Vector2& u, float A);
	* Vector2 operator/(const Vector2& u, float A);
	* bool Not_Zero(const Vector2& u);
	* bool Is_Zero(const Vector2& u);
	* void operator+=(Vector2& u, const Vector2& v);
	* void operator-=(Vector2& u, const Vector2& v);
	* void operator*=(Vector2& u, float A);
	* void operator/=(Vector2& u, float A);
	* Vector2 operator*(const Vector2& u, float A);
	* Vector2 operator*(float A, const Vector2& u);
	* void Print_Vector2(const char* string, const Vector2& u);
	

* #### Include/Window_Data.hpp
	* void Window_Data::Set_Font_Path(char* p_font_path);
	* Window_Data::Window_Data(char p_title[], int p_state = 1);
	* void Window_Data::Create_Window();
	* Window_Data::~Window_Data();