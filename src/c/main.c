#include "../h/main.h"

App app;
Stage stage;

int main(int argc, char *argv[])
{
	memset(&app, 0, sizeof(App));

	initSDL();

	atexit(cleanup);

	initStage();


	while (1)
	{
		prepareScene();

		doInput();
        app.delegate.logic();
        app.delegate.draw();
		presentScene();

        SDL_Delay(16);
	}

	return 0;
}
