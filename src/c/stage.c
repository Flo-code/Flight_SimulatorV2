#include "../h/stage.h"

void logic(void);
void draw(void);
int planeLife(void);
static void initPlane(void);
static void doPlayer(void);
static void doObjects(void);
static void drawFighters(void);
static void spawnObjects(void);
static void hitPlane(void);

static Entity *player;
static SDL_Texture *bulletTexture;
static SDL_Texture *enemyTexture;
static int enemySpawnTimer;

void initStage(void){

	memset(&stage, 0, sizeof(Stage));
	stage.fighterTail = &stage.fighterHead;

	initPlane();

	enemyTexture = loadTexture("gfx/crate.png");
	enemySpawnTimer = 0;
}

static void initPlane(){
	player = malloc(sizeof(Entity));
	memset(player, 0, sizeof(Entity));
	stage.fighterTail->next = player;
	stage.fighterTail = player;

	player->x = 300;
	player->y = 750;
	player->health = 1;
	player->texture = loadTexture("gfx/player.png");
	SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
}

void logic(void){
	doPlayer();

	doObjects();

	spawnObjects();

	hitPlane();
}

static void doPlayer(void){

	if (app.keyboard[SDL_SCANCODE_LEFT] && player->x > 5){
		player->x -= PLAYER_SPEED;
	}

	if (app.keyboard[SDL_SCANCODE_RIGHT] && player->x < 595){
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

            if (e->x < -e->w){
                if (e == stage.fighterTail){
                    stage.fighterTail = prev;
                }

                prev->next = e->next;
                free(e);
                e = prev;
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

		enemy->x = rand() %SCREEN_WIDTH;
		enemy->y = -50;
		enemy->texture = enemyTexture;
		SDL_QueryTexture(enemy->texture, NULL, NULL, &enemy->w, &enemy->h);
        enemy->dy = 8;
        enemy->health = 1;

		enemySpawnTimer = 30 + (rand() % 5);
	}
}

static void hitPlane(void){
	Entity *e;
	for (e = stage.fighterHead.next ; e != NULL ; e = e->next){
		if (collision(player->x, player->y, player->w, player->h, e->x, e->y, e->w, e->h) && e != player){
			player->health -= 1;
		}
	}
}

void draw(void){
    Entity *e;

    for (e = stage.fighterHead.next ; e != NULL ; e = e->next){
        blit(e->texture, e->x, e->y);
    }
}

int planeLife(void){
    return player->health;
}

