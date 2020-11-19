#include "../h/draw.h"
//Pr�pare rendu
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

//D�placement des items dans la fen�tre
void blit(SDL_Texture *texture, int x, int y){
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

	SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}
