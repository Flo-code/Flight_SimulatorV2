#include "common.h"

//For main
void logic(void);
void draw(void);
int planeLife(void);
void initialiseMemory(void);
//Local
void initBackgroung(void);
void initPlane(void);

void doPlayer(void);
void doObjects(void);

void drawItems(void);
void drawBackground(void);
void drawLife(void);

void spawnObjects(void);
void hitPlane(void);

extern void blit(SDL_Texture *texture, int x, int y);
extern int collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
extern SDL_Texture *loadTexture(char *filename);

extern App app;
extern Stage stage;
