#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "PuzzleBubble/ModuleParticles.h"
#include "ModuleTextures.h"
#include "Enemy.h"
#include "Bobbles.h"

#define SPAWN_MARGIN 200

ModuleEnemies::ModuleEnemies()
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = new Enemy;
}

// Destructor
ModuleEnemies::~ModuleEnemies()
{
}

bool ModuleEnemies::Start()
{
	// Create a prototype for each enemy available so we can copy them around
	sprites = App->textures->Load("Resources/Sprites/Player sprites.png");

	return true;
}

update_status ModuleEnemies::PreUpdate()
{
	// check camera position to decide what to spawn
	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(queue[i].type != ENEMY_TYPES::NO_TYPE)
		{
				SpawnEnemy(queue[i]);
				queue[i].type = ENEMY_TYPES::NO_TYPE;
				LOG("Spawning enemy at %d", queue[i].x * SCREEN_SIZE);
		}
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleEnemies::Update()
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
		if(enemies[i] != nullptr) enemies[i]->Move();

	for(uint i = 0; i < MAX_ENEMIES; ++i)
		if(enemies[i] != nullptr) enemies[i]->Draw(sprites);

	return UPDATE_CONTINUE;
}

update_status ModuleEnemies::PostUpdate()
{
	LOG("postupdate ENEMIES");

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	App->textures->Unload(sprites);

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool ModuleEnemies::EraseAll() {
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			enemies[i]->collider->to_delete = true;
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPES type, int x, int y)
{
	bool ret = false;

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(queue[i].type == ENEMY_TYPES::NO_TYPE)
		{
			queue[i].type = type;
			queue[i].x = x;
			queue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemies::SpawnEnemy(const EnemyInfo& info)
{
	// find room for the new enemy
	uint i = 0;
	for(; enemies[i] != nullptr && i < MAX_ENEMIES; ++i);

	if(i != MAX_ENEMIES)
	{
		switch(info.type)
		{
		case ENEMY_TYPES::BOBBLE_BLUE:
			enemies[i] = new Bobble_Blue(info.x,info.y);
			break;

		case ENEMY_TYPES::BOBBLE_RED:
			enemies[i] = new Bobble_Red(info.x, info.y);
			break;

		case ENEMY_TYPES::BOBBLE_GREEN:
			enemies[i] = new Bobble_Green(info.x, info.y);
			break;

		case ENEMY_TYPES::BOBBLE_YELLOW:
			enemies[i] = new Bobble_Yellow(info.x, info.y);
			break;

		case ENEMY_TYPES::BOBBLE_BLACK:
			enemies[i] = new Bobble_Black(info.x, info.y);
			break;

		case ENEMY_TYPES::BOBBLE_ORANGE:
			enemies[i] = new Bobble_Orange(info.x, info.y);
			break;

		case ENEMY_TYPES::BOBBLE_GREY:
			enemies[i] = new Bobble_Grey(info.x, info.y);
			break;

		case ENEMY_TYPES::BOBBLE_PURPLE:
			enemies[i] = new Bobble_Purple(info.x, info.y);
			break;
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			delete enemies[i];
			enemies[i] = nullptr;
			break;
		}
	}
}