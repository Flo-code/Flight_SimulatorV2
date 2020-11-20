#include "../h/init.h"

void initSDL(void){
    //Init SDL
	if (SDL_Init(SDL_INIT_VIDEO) < -1){
		printf("Erreur d'initialisation dde SDL_Init: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	//Init TTF
    if(TTF_Init() < -1){
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
	app.window = SDL_CreateWindow("Flight Simulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

	app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_ACCELERATED);

	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
}

void cleanup(void){
	SDL_DestroyRenderer(app.renderer);

	SDL_DestroyWindow(app.window);

    TTF_Quit();
	SDL_Quit();
}
