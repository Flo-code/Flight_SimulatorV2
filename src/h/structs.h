#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

typedef struct Entity Entity;

typedef struct {
	SDL_Renderer *renderer;
	SDL_Window *window;
	int keyboard[MAX_KEYBOARD_KEYS];
} App;

struct Entity {
	float x;
	float y;
	int w;
	int h;
	float dx;
	float dy;
	int health;
	SDL_Texture *texture;
	Entity *next;
};

typedef struct {
	Entity fighterHead, *fighterTail;
} Stage;

#endif
