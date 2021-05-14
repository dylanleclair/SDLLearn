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
SDL_Window* window = NULL;

SDL_Surface* gScreenSurface = NULL; /// the currently displayed image
SDL_Surface* gHelloWorld = NULL;

SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

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
	SDL_FreeSurface(gHelloWorld);
	gHelloWorld = NULL;

	//Destroy window
	SDL_DestroyWindow(window);
	window = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

int main(int argc, char* args[]) {


	if (init() ) {
		load_media();
		SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
		SDL_UpdateWindowSurface(window);
	}
	else {
		std::cout << "could not init window" << std::endl;
	}

	SDL_Event e;
	bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}
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

bool load_media() {
	bool success = 0;

	gHelloWorld = SDL_LoadBMP("example.bmp");
	if (gHelloWorld == NULL) {
		printf("Unable to load image!");
		success = false;
	}

	return success;

}