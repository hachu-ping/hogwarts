#include "scene_manager.h"
#include "screen.h"

static scene_manager_t scene_manager;

inline const scene_manager_t* get_scene_manager()
{
	return &scene_manager;
}

const change_scene(scene_t next)
{
	scene_manager.current_scene = next;
	refresh_scene();
}