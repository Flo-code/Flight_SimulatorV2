#include "../h/draw.h"
//Prépare rendu
void prepareScene(void){
	SDL_SetRenderDrawColor(app.renderer, 32, 32, 32, 255);
	SDL_RenderClear(app.renderer);
}

//Affiche le rendu
void presentScene(void){
	SDL_RenderPresent(app.renderer);
}

SDL_Texture *loadTexture(char *filename){
	SDL_Texture *texture;

	texture = IMG_LoadTexture(app.renderer, filename);

	return texture;
}

//Déplacement des items dans la fenêtre
void render(SDL_Texture *texture, int x, int y){
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

	SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}

void initBackgroung(void){
    SDL_Texture *background = SDL_CreateTexture(app.renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT * 2);
    SDL_SetRenderTarget(app.renderer,background);
}
