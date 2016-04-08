#ifndef __MODULESCENEMAINMENU_H__
#define __MODULESCENEMAINMENU_H__

#include "../Module.h"
#include "../Animation.h"
#include "../Globals.h"

struct SDL_Texture;

class ModuleSceneMainMenu : public Module {
public:
	ModuleSceneMainMenu();
	~ModuleSceneMainMenu();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* background_graphics = nullptr;
	SDL_Texture* UI_graphics = nullptr;
	SDL_Rect background;
	Animation UI;
	
};

#endif 