#include "../h/stage.h"

//For main
void logic(void);
void draw(void);
int planeLife(void);
//Local
static void initBackgroung(void);
static void initPlane(void);
static void initLife(void);

static void doPlayer(void);
static void doObjects(void);

static void drawItems(void);
static void drawBackground(void);
static void drawLife(void);

static void spawnObjects(void);
static void hitPlane(void);
//Vars
Entity *player;
static SDL_Texture *enemyTexture[2];
static SDL_Texture *Aeroport;
static SDL_Texture *life;
static int enemySpawnTimer;
static SDL_Rect piste =  {0, 0, SCREEN_WIDTH ,SCREEN_HEIGHT };

void initStage(void){
	memset(&stage, 0, sizeof(Stage));
	stage.fighterTail = &stage.fighterHead;

    initBackgroung();
    initLife();
	initPlane();

    enemyTexture[0]= loadTexture("gfx/crate.png");
    enemyTexture[1]= loadTexture("gfx/bird.png");
}

static void initPlane(void){
	player = malloc(sizeof(Entity));
	memset(player, 0, sizeof(Entity));
	stage.fighterTail->next = player;
	stage.fighterTail = player;

	player->x = 300;
	player->y = 750;
	player->health = 4;
	player->texture = loadTexture("gfx/player.png");
	SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
}

static void initBackgroung(void){
    SDL_Texture *background = SDL_CreateTexture(app.renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT * 2);
    SDL_SetRenderTarget(app.renderer,background);
    Aeroport = loadTexture("gfx/background.png");
}

static void initLife(void){
    life = loadTexture("gfx/heart.png");
}

void logic(void){
	doPlayer();

	doObjects();

	spawnObjects();

	hitPlane();
}

static void doPlayer(void){

	if (app.keyboard[SDL_SCANCODE_LEFT] && player->x > 90){
		player->x -= PLAYER_SPEED;
	}

	if (app.keyboard[SDL_SCANCODE_RIGHT] && player->x < 510){
		player->x += PLAYER_SPEED;
	}

}

static void doObjects(void){
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

static void spawnObjects(void){
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

static void hitPlane(void){
	Entity *e;
	for (e = stage.fighterHead.next ; e != NULL ; e = e->next){
		if (collision(player->x, player->y, player->w, player->h, e->x, e->y, e->w, e->h) && e != player){
			player->health -= e->health;
			e->health = 0;
		}
	}
}

static void drawItems(void){
    Entity *e;

    for (e = stage.fighterHead.next ; e != NULL ; e = e->next){
        blit(e->texture, e->x, e->y);
    }
}

static void drawBackground(void){
    piste.y -=SPEEDRUNWAY ;
    if (piste.y <= 0){
        piste.y = piste.h;
    }
    SDL_Rect dest =  {0, 0, SCREEN_WIDTH ,SCREEN_HEIGHT };
    SDL_SetRenderTarget(app.renderer , NULL);

    SDL_RenderCopy(app.renderer, Aeroport, &piste, &dest);
}

static void drawLife(void){
    for(int nbLife= player->health; nbLife>0; nbLife--){
        blit(life,(nbLife*45), 10);
    }
}

void draw(void){
    drawBackground();
    drawLife();
    drawItems();
}

int planeLife(void){
    return player->health;
}

