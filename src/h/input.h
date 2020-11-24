#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

#include "common.h"
void doKeyUp(SDL_KeyboardEvent *event);
void doKeyDown(SDL_KeyboardEvent *event);
void doInput(void);

extern App app;

#endif
