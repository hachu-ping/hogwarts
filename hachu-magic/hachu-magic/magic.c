

#include "enemy.h"
#include "magic.h"

// TODO: define max magic number
magic_t g_magic_list[MAGIC_MAX_NUMBER];


void create_magic(int x, int y, int size_w, int size_h, float velocity, char type, enemy_t* target)
{
	for (int i = 0; i < MAGIC_MAX_NUMBER; i++) {
		if (g_magic_list[i].is_spawned == 0) {  // ��� �ִ� ���� �߰�
			g_magic_list[i].pos_x = x;
			g_magic_list[i].pos_y = y;
			g_magic_list[i].size_w = size_w;
			g_magic_list[i].size_h = size_h;
			g_magic_list[i].velocity = velocity;
			g_magic_list[i].type = type;
			g_magic_list[i].target_ptr = (void*)target;

			//  ���� ��Ȳ �α� ���
			printf("[MAGIC] ���� #%d�� ���� ������ (����: %d, �ӵ�: %.1f)\n", i, type, velocity);
			return;
		}
	}

	//  ��� ������ �� á�� ���
	printf("[MAGIC] ���� ����! ��� ������ ���� ������ �����ϴ�.\n");
}

void DEBUG_init_magic(void) {
	// for debugging
	extern enemy_t g_enemy_list[ENEMY_MAX_NUMBER];

	for (int i = 0; i < MAGIC_MAX_NUMBER; i++) {
		if (i > 5) {
			g_magic_list[i].is_spawned = 0;
		}

		g_magic_list[i].is_spawned = 1;
		g_magic_list[i].type = 0;
		g_magic_list[i].pos_x = 0;
		g_magic_list[i].pos_y = 0;
		g_magic_list[i].size_w = 20;
		g_magic_list[i].size_h = 20;
		g_magic_list[i].velocity = 1.0;
		g_magic_list[i].target_ptr = &g_enemy_list[i];
	}
}

void init_magic(void)
{
	for (int i = 0; i < MAGIC_MAX_NUMBER; i++) {
		g_magic_list[i].is_spawned = 0;
	}
}