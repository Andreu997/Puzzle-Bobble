#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "PuzzleBubble/ModuleParticles.h"

#define ANGLE_INCREMENT 85.f/63.f


ModulePlayer::ModulePlayer()
{
	position.x = 139;
	position.y = 163;
	
	//all arrow animation frames

	//Central
	arrow[0].x = 14;
	arrow[0].y = 514;
	arrow[0].w = 24;
	arrow[0].h = 55;

	//-----------
	

}

ModulePlayer::~ModulePlayer()
{}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;

	arrow_center.x = 50;
	arrow_center.y = 130;

	player_angle = 90;

	graphics = App->textures->Load("Sprites/Game Sprites.png");
	return ret;
}


update_status ModulePlayer::Update()
{
	if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT && player_angle > 5) {
		//aqui va q giri la flecha
		player_angle -= ANGLE_INCREMENT;
	}

	if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT && player_angle < 175) {
		player_angle += ANGLE_INCREMENT;
	}

	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_DOWN) {
		App->particles->AddParticle(App->particles->red_bubble, App->particles->red_bubble.position.x, App->particles->red_bubble.position.y, COLLIDER_PLAYER_SHOT);
	}
	
	App->render->Blit(graphics, position.x, position.y, &(arrow.GetCurrentFrame()), 0.75f);

	return UPDATE_CONTINUE;
}