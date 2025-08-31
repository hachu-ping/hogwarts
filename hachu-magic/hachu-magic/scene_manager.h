#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

#include <allegro5/allegro5.h>

typedef struct _text_box text_box_t;

typedef struct _button {
	float x, y, w, h;
	const char* label;
} button_t;

extern button_t start_button;
extern button_t rank_button;


typedef enum _scene {
	SCENE_TITLE,
	SCENE_PLAY,
	SCENE_RANK
} scene_t;

typedef struct _scene_manager {
	scene_t current_scene;
	//text_box_t textbox;
} scene_manager_t;

extern inline const scene_manager_t* get_scene_manager();

void change_scene(scene_t next);

#endif /* __SCENE_MANAGER_H__ */