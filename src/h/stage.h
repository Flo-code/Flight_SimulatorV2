#ifndef STAGE_H_INCLUDED
#define STAGE_H_INCLUDED

#include "common.h"
#include "draw.h"
#include "collision.h"

void initStage(void);
void initPlane(void);
void initialiseMemory(void);
void deleteObjects(void);

void logic(void);
void doPlayer(void);
void doObjects(void);
void spawnObjects(void);
void hitPlane(void);

void drawItems(void);
void drawBackground(void);
void drawLife(void);
void drawGameover(void);
void draw(void);
int planeLife(void);

extern App app;
extern Stage stage;
#endif
