// Copyright Peter Lager and Steve Manning and the University of Bolton
// Do what you like with the program, but please include your
// sourcecode with any distribution and retain my copyright notices
//
// v1.1 - upgraded to use SDL2 with Renderer and Texture and audio code added.

#pragma once

#include <iostream>
#include <string>

#include "SDL.h"
#include "SDL_image.h"
#include "audiomanager.h"
#include "AWSprite.h"

class AWFont;	//v1.1

#include "console.h"
#include "random.h"

using namespace std;
using namespace con;
using namespace random;

// Colour constants
const int GREEN = 0;
const int WHITE = 1;
const int RED = 2;

#define SAFE_DELETE_PTR(ptr) if( (ptr) != NULL ) delete (ptr); (ptr) = NULL;	//v1.1 Added by A.Simpson
#define SAFE_DELETE_ARY(ary) if( (ary) != NULL ) delete[] (ary); (ary) = NULL;

/**
This has the core functionality to create simple games. <br>

All games should be built from its own game class that inherits
from this class. <br>
*/
class GameBase
{
public:
	GameBase(void);
	virtual ~GameBase(void);

	/**
	You should override this method to provide code to setup your
	game variables and state.
	*/
	virtual void setup(){}
	/**
	Once your game has been created and initialised (using setup)
	call this method to start the game.
	*/
	virtual void start();
//******************************************************	//v1.1
	static SDL_Window *window;
	static SDL_Renderer *renderer;
	static SDL_Texture *texture;
	SDL_Rect m_camera;
	//******************************************************
protected:
	SDL_Surface* screen;
	SDL_Surface* bg;
	AWFont *fs_white, *fs_green, *fs_red;

	SDL_Texture *bgTexture; //v1.1

	/*
	The values in these variables are updated every iteration of the game loop
	and should be used in the onKey??? and onMouse??? methods to change the game
	variables and state.
	*/
	int mouseX, mouseY;
	int pmouseX, pmouseY;
	int mouseButton;
	int keyDown, keyUp;
	bool ctrlPressed, shiftPressed, altPressed;

	boolean gameover;

	// These are used to store the width and height of the display area
	// and are initialised when you create the game object.
	int width, height;

	virtual void logic(){}
	virtual void draw(){}
	virtual void post(){}

	virtual void getUserInput();

	int enableKeyRepeat(int first = 70, int repeat = 70);

	/**
	Set the background colour for the display. The parameters should
	be in the range 0-255 inclusive.
	*/
	void setBackground(int red, int green, int blue);
	/**
	Set the backgorund image to be used for the display area. It makes
	sense if the image is the same size as the display area as scaling
	is not applied to the image.
	*/
	void setBackground(char *imageFileName);

	/**
	Add a sound effect for later playing.
	@param filename the filename of the audio file to load.
	@param name this should be unique for eah sound effect added.
	*/
	bool addSound(char* filename, string name);
	/**
	Play the sound effect (expect some latency)
	@param name the unique name of the sound effect to play
	*/
	void playSound(string name);

	/*
	These  provide nill functionality event handlers you should
	override these if needed.
	*/
	virtual void onMousePressed(){}
	virtual void onMouseReleased(){}
	virtual void onMouseMoved(){}
	virtual void onKeyPressed(){}
	virtual void onKeyReleased(){}

	/**
	This is the main gameloop and is called when the game is started. <br>
	Although it is possible to override this method in your own game class
	this is not recommended unless you really know what you are doing!!!
	*/
	void gameLoop();

	/**
	These methods are used to display text on the screen at a given position.
	Three colours are available GREEN, WHITE and RED if you don't specify a
	colour then it will use green text.
	@param value the value to display can be of type string, char array,
	integer or float
	@param x the horizontal pixel position to start printing
	@param y the vertical (character top) pixel position to use
	@param color the colour to use (choice of GREEN, WHITE or RED)
	*/
	int print(string value, int x, int y, int color = GREEN);
	int print(const char* value, int x, int y, int color = GREEN);
	int print(int value, int x, int y, int color = GREEN);
	int print(float value, int x, int y, int color = GREEN);

private:
	AWFont* getFontToUse(int color);

private:
	//static SDL_Surface* screen_surface;	//****
	//static SDL_Surface* background_surface;

protected:
	/**
	Get a surface for the display of the given size and colour
	*/
	static SDL_Surface* getSurface(int width, int height, int red, int green, int blue);

public:
	/**
	This method should be called before you create your game object otherwise your
	program will crash. <br>
	It creates the window with a display area width x height and sets the background
	to black. <br>
	You can use the setBackground methods to change the background colour or
	provide an image to use.
	*/
	static int initSDL(int width, int height, string title = "SDL Game");	//v1.1
	bool addSound(char* filename, string name, int volDivider);

	static SDL_Surface* screen_surface;	//v1.1
	static SDL_Surface* background_surface;

};
