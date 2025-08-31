#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

#include <allegro5/allegro5.h>

#include "game_system.h"

typedef struct _button {
	float x, y, w, h;
	const char* label;
} button_t;

button_t start_button = { 550, 380, 300, 60, "start" };
button_t rank_button = { 550, 460, 300, 60, "rank" };

typedef enum _scene {
	SCENE_TITLE,
	SCENE_PLAY,
	SCENE_RANK
} scene_t;

typedef struct _scene_manager {
	scene_t current_scene;
	text_box_t textbox;
} scene_manager_t;

inline const scene_manager_t* get_scene_manager();

const change_scene(scene_t next);

#endif /* __SCENE_MANAGER_H__ */