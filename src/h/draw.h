#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED

#include "common.h"

#include <SDL2/SDL_image.h>
void prepareScene(void);
void presentScene(void);
void render(SDL_Texture *texture, int x, int y);
void initBackgroung(void);
extern App app;
#endif
