#include "../h/stage.h"

//Vars
Entity *player;
SDL_Texture *enemyTexture[2];
SDL_Texture *Aeroport;
SDL_Texture *life;
SDL_Texture *gameoverScreen;
int enemySpawnTimer;
SDL_Rect piste =  {0, 0, SCREEN_WIDTH ,SCREEN_HEIGHT };

void initStage(void){
    initBackgroung();
	initPlane();
}

void initPlane(void){
	player->x = 300;
	player->y = 750;
	player->health = 4;
	SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
}

void initialiseMemory(void){
    memset(&stage, 0, sizeof(Stage));
	stage.fighterTail = &stage.fighterHead;
    player = malloc(sizeof(Entity));
    memset(player, 0, sizeof(Entity));
    stage.fighterTail->next = player;
	stage.fighterTail = player;

    player->texture = loadTexture("gfx/player.png");
    Aeroport = loadTexture("gfx/background.png");
    life = loadTexture("gfx/heart.png");
    gameoverScreen = loadTexture("gfx/gameover.png");
    enemyTexture[0]= loadTexture("gfx/crate.png");
    enemyTexture[1]= loadTexture("gfx/bird.png");
}

void deleteObjects(void){
    Entity *e, *prev;

    prev = &stage.fighterHead;

    for (e = stage.fighterHead.next ; e != NULL ; e = e->next){
        if(e !=player){
            //Reparcourir la liste chainée
            if (e == stage.fighterTail){
                stage.fighterTail = prev;
            }
            //test pour ne pas supprimer l'avion
            if(prev->next!=player){
                prev->next = e->next;
                free(e);
                e = prev;
            }else{
            //pour ne pas supprimer la tête de la liste => sinon avion supprimer
                prev = player;
                prev->next = e->next;
                free(e);
                e = prev;
            }
        }
        prev = e;
    }
}


void logic(void){
	doPlayer();

	doObjects();

	spawnObjects();

	hitPlane();
}

void doPlayer(void){

	if (app.keyboard[SDL_SCANCODE_LEFT] && player->x > 90){
		player->x -= PLAYER_SPEED;
	}

	if (app.keyboard[SDL_SCANCODE_RIGHT] && player->x < 510){
		player->x += PLAYER_SPEED;
	}

}

void doObjects(void){
	Entity *e, *prev;

	prev = &stage.fighterHead;

	for (e = stage.fighterHead.next ; e != NULL ; e = e->next){
	    if(e !=player){
            e->x += e->dx;
            e->y += e->dy;

            if (e->x > SCREEN_WIDTH || e->y > SCREEN_HEIGHT|| e->health<=0 ){//TODO modif condition
                //Reparcourir la liste chainée
                if (e == stage.fighterTail){
                    stage.fighterTail = prev;
                }
                //test pour ne pas supprimer l'avion
                if(prev->next!=player){
                    prev->next = e->next;
                    free(e);
                    e = prev;
                }else{
                    //pour ne pas supprimer la tête de la liste => sinon avion supprimer
                    prev = player;
                    prev->next = e->next;
                    free(e);
                    e = prev;
                }
            }
            prev = e;
        }
	}
}

void spawnObjects(void){
	Entity *enemy;

	if (--enemySpawnTimer <= 0){
        enemy = malloc(sizeof(Entity));
        memset(enemy, 0, sizeof(Entity));
        stage.fighterTail->next = enemy;
        stage.fighterTail = enemy;
        int randomEnemy = rand()%10;
        if(randomEnemy<=6){
        //Taille crate prise en compte dans le calcul
            enemy->x = rand()%(SCREEN_WIDTH-250)+100;
            enemy->y = -50;
            enemy->dy = SPEEDRUNWAY;
            enemy->health = 2;
            enemy->texture = enemyTexture[0];
        }
        if(randomEnemy>6){
            enemy->y = rand()%(SCREEN_HEIGHT-200);
            enemy->x = -30;
            enemy->dx = 5;
            enemy->dy = 4;
            enemy->health = 1;
            enemy->texture = enemyTexture[1];
        }
		SDL_QueryTexture(enemy->texture, NULL, NULL, &enemy->w, &enemy->h);
		enemySpawnTimer = 30 + (rand() % 10);
	}
}

void hitPlane(void){
	Entity *e;
	for (e = stage.fighterHead.next ; e != NULL ; e = e->next){
		if (collision(player->x, player->y, player->w, player->h, e->x, e->y, e->w, e->h) && e != player){
			player->health -= e->health;
			e->health = 0;
		}
	}
}

void drawItems(void){
    Entity *e;

    for (e = stage.fighterHead.next ; e != NULL ; e = e->next){
        render(e->texture, e->x, e->y);
    }
}

void drawBackground(void){
    piste.y -=SPEEDRUNWAY ;
    if (piste.y <= 0){
        piste.y = piste.h;
    }
    SDL_Rect dest =  {0, 0, SCREEN_WIDTH ,SCREEN_HEIGHT };
    SDL_SetRenderTarget(app.renderer , NULL);

    SDL_RenderCopy(app.renderer, Aeroport, &piste, &dest);
}

void drawLife(void){
    for(int nbLife= player->health; nbLife>0; nbLife--){
        render(life,(nbLife*45), 10);
    }
}

void drawGameover(void){
    prepareScene();
    render(gameoverScreen, 0, 0);
    presentScene();
    while(app.keyboard[SDL_SCANCODE_RETURN] == 0){doInput();}
}

void draw(void){
    drawBackground();
    drawItems();
    drawLife();
}

int planeLife(void){
    return player->health;
}

