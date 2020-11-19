#include "../h/input.h"
//Action sur touche relachée
void doKeyUp(SDL_KeyboardEvent *event){
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS){
		app.keyboard[event->keysym.scancode] = 0;
	}
}

//Action sur touche appuyée
void doKeyDown(SDL_KeyboardEvent *event){
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS){
		app.keyboard[event->keysym.scancode] = 1;
	}
}

//Check les imputs
void doInput(void){
	SDL_Event event;

	while (SDL_PollEvent(&event)){
		switch (event.type)
		{
			case SDL_QUIT:
				exit(0);
				break;

			case SDL_KEYDOWN:
				doKeyDown(&event.key);
				break;

			case SDL_KEYUP:
				doKeyUp(&event.key);
				break;

			default:
				break;
		}
	}
}
