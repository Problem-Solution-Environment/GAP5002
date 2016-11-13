// Copyright Peter Lager and the University of Bolton
// Do what you like with the program, but please include your
// sourcecode with any distribution and retain my copyright notices
//
// v1.1 functions added.

#pragma once;

#include<iostream>
#include<map>
#include<string>
using namespace std;

#include "SDL_mixer.h"

typedef map<string, Mix_Chunk*> CMAP;
typedef map<string, Mix_Chunk*>::iterator CMAPIT;

class AudioManager
{
private:
	// Static variable of type AudioManager pointer
	static AudioManager* instance;

	// All constructors are declared private to prevent
	// it being used to create AudioManager objects
	// from outside the class
	AudioManager();

public:
	// Static (global) method to return the attribute
	// 'instance'. If instance is NULL it creates an
	// object of type AudioManager and stores it address
	// in the static attribute instance
	static AudioManager* getInstance();

	~AudioManager();

public:
	bool addSound(char* filename, string name);
	void playSound(string name);

	bool addSound(char* filename, string name, int volDivider);	//v1.1
	void playMusic(string name);
	int playMusicOnChannel(string name, int channel);
	void stopMusicOnChannel(int c);

private:
	// Map container to maintain collection of sounds
	CMAP soundmap;
};
