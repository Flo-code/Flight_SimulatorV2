#include "../h/main.h"

App app;
Stage stage;

SDL_Color couleurNoire = {0, 0, 0};
int main(int argc, char *argv[]){
	memset(&app, 0, sizeof(App));
	initSDL();
	atexit(cleanup);
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
        prepareScene();
        drawGameover();
        presentScene();
        while(app.keyboard[SDL_SCANCODE_RETURN] == 0){doInput();}
    }
        SDL_DestroyRenderer(app.renderer);
        SDL_DestroyWindow(app.window);
        SDL_Quit();
	return 0;
}
