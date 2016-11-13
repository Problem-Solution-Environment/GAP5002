#include "GameBase.h"
#include "awfont.h"	//v1.1

SDL_Surface* GameBase::screen_surface = NULL;
SDL_Surface* GameBase::background_surface = NULL;

SDL_Window* GameBase::window = NULL;	//v1.1
SDL_Renderer* GameBase::renderer = NULL;
SDL_Texture* GameBase::texture = NULL;

/*
Initialise the SDL.
SDL functions  return 0 on success and <0 for failure so do the same here.
return 0 if successful
*/
int GameBase::initSDL(int width, int height, string title){	//v5.0
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO) != 0){
		cout << "Unable to initialise SDL\n\nPROGRAM TERMINATED\n\n";
		system("pause");
		return -1;
	}
	// So we have managed to initialise the SDL systems so make sure we
	// uninitialise them when the program terminates
	atexit(SDL_Quit);

//**************************************************	//v1.1
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if (window == NULL){
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}else{
//		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);	//use GPU & sync with screen
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);	//use GPU
		if (renderer == NULL){
			printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			return false;
		}else{
			//Initialize renderer color
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

			//Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags)){
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				return false;
			}
		}
	}
//**************************************************
	// Now initialise  the screen this will initialise event handling as well

	screen_surface = SDL_GetWindowSurface(window);	//v1.1
	// Make sure we have got the screen before moving on
	if (screen_surface == NULL) {
		cout << "Unable to initialise display window\n\nPROGRAM TERMINATED\n\n";
		system("pause");
		return -1;
	}
	// Resize the console window to make it less obvious
	console.setSize(50, 30, false);
	// Get default grey background
	background_surface = getSurface(width, height, 0, 0, 0);

	// SDL functions return 0 on success
	return 0;
}

SDL_Surface* GameBase::getSurface(int width, int height, int red, int green, int blue){
	Uint32 rmask, gmask, bmask, amask;
	/* SDL interprets each pixel as a 32-bit number, so our masks must depend
	   on the endianness (byte order) of the machine */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif
	SDL_Surface* newSurface = SDL_GetWindowSurface(window);	//v1.1
	SDL_FillRect(newSurface, NULL,
		SDL_MapRGB(newSurface->format, red, green, blue));
	return newSurface;
}

GameBase::GameBase(void){
	screen = screen_surface;
	bg = background_surface;
	width = screen->w;
	height = screen->h;
	mouseX = mouseY = 0;
	cout << "Screen size " << width << " x " << height << endl;
	fs_white = new AWFont("vera_white.bmp", "vera.dat");
	fs_green = new AWFont("vera_green.bmp", "vera.dat");
	fs_red = new AWFont("vera_red.bmp", "vera.dat");

	m_camera.x = m_camera.y = 0;	//v1.1
	m_camera.w = width;
	m_camera.h = height;
	bgTexture = NULL;
}

GameBase::~GameBase(void){
	delete fs_white;
	delete fs_green;
	delete fs_red;
	SDL_FreeSurface(bg);	

	//Free loaded image 
	SDL_DestroyTexture( texture );	//v1.1
	texture = NULL; 
	//Destroy window 
	SDL_DestroyRenderer( renderer ); 
	SDL_DestroyWindow( window ); 
	window = NULL; 
	renderer = NULL; 
	//Quit SDL subsystems 
	IMG_Quit(); 
	SDL_Quit();
}

void GameBase::start(){
	gameLoop();
}

void GameBase::setBackground(int red, int green, int blue){
	bg = getSurface(width, height, red, green, blue);
}

void GameBase::setBackground(char *imageFileName){
	// Get the background image
	bg = IMG_Load(imageFileName);	//v1.1
	if (bg != NULL){
		SDL_SetColorKey(bg, SDL_TRUE, SDL_MapRGB(bg->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);	//v1.1

		if (texture == NULL)	{
			printf("Unable to create texture from %s! SDL Error: %s\n", imageFileName, SDL_GetError());
		}
		bgTexture = SDL_CreateTextureFromSurface(renderer, bg);	
	}
	else{
		cout << "Unable to locate image file " << imageFileName << endl;
	}
}

bool GameBase::addSound(char* filename, string name){
	return AudioManager::getInstance()->addSound(filename, name);
}

bool GameBase::addSound(char* filename, string name, int volDivider){	//v1.1
	return AudioManager::getInstance()->addSound(filename, name, volDivider);
}

void GameBase::playSound(string name){
	AudioManager::getInstance()->playSound(name);
}

void GameBase::getUserInput(){
	SDL_Event an_event;
	if (SDL_PollEvent(&an_event)){
		keyDown = keyUp = 0;
		switch (an_event.type)
		{
		case SDL_QUIT:
			gameover = true;
			break;
		case SDL_KEYDOWN:
			ctrlPressed = ((an_event.key.keysym.mod & KMOD_CTRL) == KMOD_CTRL);
			shiftPressed = ((an_event.key.keysym.mod & KMOD_SHIFT) == KMOD_SHIFT);
			altPressed = ((an_event.key.keysym.mod & KMOD_ALT) == KMOD_ALT);
			keyDown = an_event.key.keysym.sym;
			gameover = ((keyDown & SDLK_ESCAPE) == SDLK_ESCAPE);
			onKeyPressed();
			break;
		case SDL_KEYUP:
			ctrlPressed = ((an_event.key.keysym.mod & KMOD_CTRL) == KMOD_CTRL);
			shiftPressed = ((an_event.key.keysym.mod & KMOD_SHIFT) == KMOD_SHIFT);
			altPressed = ((an_event.key.keysym.mod & KMOD_ALT) == KMOD_ALT);
			keyUp = an_event.key.keysym.sym;
			onKeyReleased();
			break;
		case SDL_MOUSEMOTION:
			pmouseX = mouseX;
			pmouseY = mouseY;
			mouseX = an_event.motion.x;
			mouseY = an_event.motion.y;
			onMouseMoved();
			break;
		case SDL_MOUSEBUTTONDOWN:
			mouseButton = an_event.button.button; // SDL_BUTTON_LEFT)
			mouseX = an_event.button.x;
			mouseY = an_event.button.y;
			onMousePressed();
			break;
		case SDL_MOUSEBUTTONUP:
			mouseButton = an_event.button.button; // SDL_BUTTON_LEFT)
			mouseX = an_event.button.x;
			mouseY = an_event.button.y;
			onMouseReleased();
			break;
		default:
			// An event that we do not need to process
			break;
		} // end of poll event switch
	} // end if
}

void GameBase::gameLoop(){
	gameover = false;
	while (!gameover) {
		SDL_Delay(1);
		getUserInput();
		logic();

		SDL_RenderClear(renderer);	//v1.1
		SDL_RenderCopy(renderer, bgTexture, &m_camera, NULL);	//render background

		draw();

		SDL_RenderPresent(renderer);	//v1.1
		SDL_DestroyTexture(texture);	
		texture = NULL;
		post();
	}
}

int GameBase::enableKeyRepeat(int first, int repeat){
//	return SDL_EnableKeyRepeat(first, repeat);	//v1.1 func NOT req'd in SDL2
	return 0;
}

int GameBase::print(string value, int x, int y, int color){
	return (getFontToUse(color))->print_string(value.c_str(), x, y);
}

int GameBase::print(const char* value, int x, int y, int color){
	return getFontToUse(color)->print_string(value, x, y);
}

int GameBase::print(int value, int x, int y, int color){
	return getFontToUse(color)->print_integer(value, x, y);
}

int GameBase::print(float value, int x, int y, int color){
	return getFontToUse(color)->print_float(value, x, y);
}

AWFont* GameBase::getFontToUse(int color){
	switch (color){
	case GREEN:
		return fs_green;
	case WHITE:
		return fs_white;
	case RED:
		return fs_red;
	default:
		return fs_green;
	}
}