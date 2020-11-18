#include "../h/stage.h"

static void logic(void);
static void draw(void);
static void initPlayer(void);
static void doPlayer(void);
static void doFighters(void);
static void drawFighters(void);
static void spawnEnemies(void);
static void hitPlane(void);

static Entity *player;
static SDL_Texture *bulletTexture;
static SDL_Texture *enemyTexture;
static int enemySpawnTimer;

void initStage(void)
{
	app.delegate.logic = logic;
	app.delegate.draw = draw;

	memset(&stage, 0, sizeof(Stage));
	stage.fighterTail = &stage.fighterHead;

	initPlayer();

	enemyTexture = loadTexture("gfx/crate.png");
	enemySpawnTimer = 0;
}

static void initPlayer()
{
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

static void logic(void)
{
	doPlayer();

	doFighters();

	spawnEnemies();

	hitPlane();
}

static void doPlayer(void)
{

	if (app.keyboard[SDL_SCANCODE_LEFT] && player->x > 5)
	{
		player->x -= PLAYER_SPEED;
	}

	if (app.keyboard[SDL_SCANCODE_RIGHT] && player->x < 595)
	{
		player->x += PLAYER_SPEED;
	}

}

static void doFighters(void)
{
	Entity *e, *prev;

	prev = &stage.fighterHead;

	for (e = stage.fighterHead.next ; e != NULL ; e = e->next)
	{
		e->x += e->dx;
		e->y += e->dy;

		if (e != player && e->x < -e->w)
		{
			if (e == stage.fighterTail)
			{
				stage.fighterTail = prev;
			}

			prev->next = e->next;
			free(e);
			e = prev;
		}
		prev = e;
	}
}

static void spawnEnemies(void)
{
	Entity *enemy;

	if (--enemySpawnTimer <= 0)
	{
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
		enemySpawnTimer = 30 + (rand() % 60);
	}
}

static void hitPlane(void){
	Entity *e;
	for (e = stage.fighterHead.next ; e != NULL ; e = e->next)
	{
		if (collision(player->x, player->y, player->w, player->h, e->x, e->y, e->w, e->h) && e != player)
		{
			player->health = 0;
		}
	}
}

static void draw(void)
{
	drawFighters();
}

static void drawFighters(void)
{
	Entity *e;

	for (e = stage.fighterHead.next ; e != NULL ; e = e->next)
	{
		blit(e->texture, e->x, e->y);
	}
}

