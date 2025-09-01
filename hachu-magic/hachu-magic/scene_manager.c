#include "scene_manager.h"
#include "game_system.h"
#include "screen.h"

static scene_manager_t scene_manager;

button_t name_box = { 550, 300, 300, 60, "name box" };
button_t start_button = { 550, 380, 300, 60, "start" };
button_t rank_button = { 550, 460, 300, 60, "rank" };

inline const scene_manager_t* get_scene_manager()
{
	return &scene_manager;
}

void change_scene(scene_t next)
{
	scene_manager.current_scene = next;
	refresh_scene();
}