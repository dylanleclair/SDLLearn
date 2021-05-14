#include <iostream>
#include <SDL.h>

#define WIDTH 1280
#define HEIGHT 720


bool running, fullscreen;


void update();
void input();
void draw();
bool load_media();


enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

SDL_Renderer* renderer = NULL;
SDL_Window* window = NULL; // the window we render to

SDL_Surface* gScreenSurface = NULL; /// the surface contained by the image
SDL_Surface* gHelloWorld = NULL; 

SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL]; // the list of images corresponding to keypresses
SDL_Surface* gCurrentSurface = NULL; // the currently displayed image


int frameCount, timerFPS, lastFrame, fps;


bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface(window);
		}
	}

	return success;
}


void close()
{
	//Deallocate surface
	SDL_FreeSurface(gCurrentSurface);
	gCurrentSurface = NULL;

	//Destroy window
	SDL_DestroyWindow(window);
	window = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

int main(int argc, char* args[]) {

	init();

	load_media();

	// Main loop flag
	bool quit = false;

	// Event handler
	SDL_Event e;

	// Set the default current surface

	gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

	while (!quit) {

		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			else if (e.type == SDL_KEYDOWN) {
				// Select surfaces based on key press
				switch (e.key.keysym.sym) {
				case SDLK_UP:
					gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
					break;
				default:
					gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
					break;
				}
			}
		}
		SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);
		SDL_UpdateWindowSurface(window);
	}



	close();
	return 0;
}


void update() {
	frameCount++;
	timerFPS = SDL_GetTicks() - lastFrame;
	if (timerFPS < (1000 / 60)) {
		SDL_Delay((1000 / 60) - timerFPS);
	}


}

void input() {}

void draw() {
	SDL_SetRenderDrawColor(renderer, 100,0,0,255);
	SDL_Rect rect;

	rect.x = rect.y = 0;
	rect.w = WIDTH;
	rect.h = HEIGHT;
	SDL_RenderFillRect(renderer, &rect);

	// anything on top of bkg goes here

	SDL_RenderPresent(renderer);
}

SDL_Surface* load_surface(std::string path) {


	SDL_Surface* loaded = SDL_LoadBMP(path.c_str());
	if (loaded == NULL) {
		printf("Unable to load image!");
	}

	// Images loaded here are deallocated in the close function!
	// Memory leaks are not a concern here. 

	return loaded;

}


bool load_media() {
	bool success = true;

	gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = load_surface("example.bmp");
	if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
		std::cout << "Failed to load default image.\n";
	}

	gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = load_surface("alternate.bmp");
	if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
		std::cout << "Failed to load alternate image.\n";
	}

	return success;
}