#include "../h/main.h"

App app;
Stage stage;

SDL_Color couleurNoire = {0, 0, 0};
int main(int argc, char *argv[]){
	memset(&app, 0, sizeof(App));
	initSDL();
    initialiseMemory();
    while(1){
        initStage();
        while (planeLife()>0){
            prepareScene();

            doInput();
            logic();
            draw();

            presentScene();
            SDL_Delay(16);
        }
        deleteObjects();
        drawGameover();
    }
        cleanMemory();
	return 0;
}
