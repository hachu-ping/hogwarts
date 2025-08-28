

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
		g_magic_list[i].is_spawned = 0;
	}


	for (int i = 0; i < MAGIC_MAX_NUMBER; i++) {
		if (i > 0) {
			g_magic_list[i].is_spawned = 0;
			continue;
		}

		g_magic_list[i].is_spawned = 1;
		g_magic_list[i].type = 0;
		g_magic_list[i].pos_x = 710;
		g_magic_list[i].pos_y = 540;
		g_magic_list[i].size_w = 20;
		g_magic_list[i].size_h = 20;
		g_magic_list[i].velocity = 1.0;
		g_magic_list[i].target_ptr = &g_enemy_list[i];
	}
}

//�ӽ� -> ���� �ý���
bool is_collide_magic(magic_t* magic_ptr){
	magic_t* magic_ptr_bool = magic_ptr;
	double ax1 = (magic_ptr_bool->pos_x);
	double ay1= (magic_ptr_bool->pos_y);
	double ax2 = (magic_ptr_bool->pos_x) + (magic_ptr_bool->size_w);
	double ay2 = (magic_ptr_bool->pos_y) + (magic_ptr_bool->size_h);
	double bx1 = (((enemy_t*)magic_ptr_bool->target_ptr)->pos_x);
	double by1 = (((enemy_t*)magic_ptr_bool->target_ptr)->pos_y);
	double bx2 = (((enemy_t*)magic_ptr_bool->target_ptr)->pos_x) + (((enemy_t*)magic_ptr_bool->target_ptr)->size_w);
	double by2 = (((enemy_t*)magic_ptr_bool->target_ptr)->pos_y) + (((enemy_t*)magic_ptr_bool->target_ptr)->size_h);
	
	if (ax1 > bx2) return false;
	if (ax2 < bx1) return false;
	if (ay1 > by2) return false;
	if (ay2 < by1) return false;

	return true;

}


//�浹 ó�� �Լ�
void collide_magic(void) {
	magic_t* magic_ptr = g_magic_list;
	for (int i = 0; i < MAGIC_MAX_NUMBER; ++i, ++magic_ptr) {
		if (!(magic_ptr->is_spawned)) { //������ ������ ���ؼ��� �˻�.
			continue;
		}
		if (is_collide_magic(magic_ptr)) {
			magic_ptr->is_spawned = 0;
			(((enemy_t*)magic_ptr->target_ptr)->is_spawned) = 0;
		}
	}
}

void init_magic(void){
	for (int i = 0; i < MAGIC_MAX_NUMBER; i++) {
		g_magic_list[i].is_spawned = 0;
	}
}
/*
//���߿� ������ �����̴� ���� ������ �� ���
double delta_move_magic(void) {
	extern g_frames;
	return ((rand() % 5) + 1)*fabsf(sinf(0.5*g_frames)) + 0.5;
}*/

//�� �����Ӹ� ������ ��.
void move_magic(void) {
	magic_t* magic_ptr = g_magic_list;

	for (int i = 0; i < MAGIC_MAX_NUMBER; ++i, ++magic_ptr) {
		if (!(magic_ptr->is_spawned)) {
			continue;
		}

		//1. ���� ����
		float magic_dx =  (((enemy_t*)magic_ptr->target_ptr)->pos_x) - (magic_ptr->pos_x);
		float magic_dy =  (((enemy_t*)magic_ptr->target_ptr)->pos_y) - (magic_ptr->pos_y);
		//2. ���� ����
		float len = (float) sqrt((magic_dx * magic_dx) + (magic_dy * magic_dy));
		if (len == 0) continue; // �̹� ��ģ ������ ��
		magic_dx /= len; // ���� ����
		magic_dy /= len;
		//3. �ӵ��̵�
		magic_ptr->pos_x += (magic_dx*4 * (magic_ptr->velocity));
		magic_ptr->pos_y += (magic_dy*4 * (magic_ptr->velocity));
	}
}

