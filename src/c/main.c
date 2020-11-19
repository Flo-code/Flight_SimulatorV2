#include "../h/main.h"

App app;
Stage stage;

int main(int argc, char *argv[]){
	memset(&app, 0, sizeof(App));

	initSDL();

	atexit(cleanup);

    while(1){

        initStage();

        while (planeLife()!=0){
            prepareScene();

            doInput();
            logic();
            draw();

            presentScene();

            SDL_Delay(16);
        }
    }
	return 0;
}
