
#include "debug.h"
#include "enemy.h"
#include "magic.h"

extern enemy_t g_enemy_list[ENEMY_MAX_NUMBER];

magic_t g_magic_list[MAGIC_MAX_NUMBER];

void DEBUG_clear_magic(void) {
	// for debugging

	for (int i = 0; i < MAGIC_MAX_NUMBER; i++) {
		g_magic_list[i].is_spawned = 0;
	}

	for (int i = 0; i < MAGIC_MAX_NUMBER; i++) {
		if (i > 3) {
			g_magic_list[i].is_spawned = 0;
			continue;
		}

		g_magic_list[i].is_spawned = 1;
		g_magic_list[i].type = 1;
		g_magic_list[i].pos_x = 710;
		g_magic_list[i].pos_y = 540;
		g_magic_list[i].size_w = 20;
		g_magic_list[i].size_h = 20;
		g_magic_list[i].target_ptr = &g_enemy_list[0];
	}

	g_magic_list[0].velocity = 4.0;
	g_magic_list[1].velocity = 3.0;
	g_magic_list[2].velocity = 1.0;
	g_magic_list[3].velocity = 0.9;
}

void create_magic(double pos_x, double pos_y, magic_type_t type, enemy_t* target)
{
	for (int i = 0; i < MAGIC_MAX_NUMBER; i++) {
		// ��� �ִ� ���� �߰�
		if (g_magic_list[i].is_spawned == false) {  
			g_magic_list[i].pos_x = pos_x;
			g_magic_list[i].pos_y = pos_y;
			g_magic_list[i].size_w = MAGIC_WIDTH;
			g_magic_list[i].size_h = MAGIC_HEIGHT;
			g_magic_list[i].velocity = 3.0;
			g_magic_list[i].type = type;
			g_magic_list[i].target_ptr = (void*)target;

			g_magic_list[i].is_spawned = true;

			DEBUG_PRINT("%d�� ���� ����\n", i);
			return;
		}
	}

	//  ��� ������ �� á�� ���
	DEBUG_PRINT("[MAGIC] ���� ����! ��� ������ ���� ������ �����ϴ�.\n");
}

// Ÿ�ٰ��� ���� �˻�
bool is_collided_with_target(magic_t* magic_ptr)
{
	if (magic_ptr == NULL) {
		return false;
	}

	double ax1 = (magic_ptr->pos_x);
	double ay1 = (magic_ptr->pos_y);
	double ax2 = (magic_ptr->pos_x) + (magic_ptr->size_w);
	double ay2 = (magic_ptr->pos_y) + (magic_ptr->size_h);
	double bx1 = (((enemy_t*)magic_ptr->target_ptr)->pos_x);
	double by1 = (((enemy_t*)magic_ptr->target_ptr)->pos_y);
	double bx2 = (((enemy_t*)magic_ptr->target_ptr)->pos_x) + (((enemy_t*)magic_ptr->target_ptr)->size_w);
	double by2 = (((enemy_t*)magic_ptr->target_ptr)->pos_y) + (((enemy_t*)magic_ptr->target_ptr)->size_h);
	
	if (ax1 > bx2) return false;
	if (ax2 < bx1) return false;
	if (ay1 > by2) return false;
	if (ay2 < by1) return false;

	return true;
}


// �浹 ó�� �Լ�
void handle_magic_collision(void)
{
	magic_t* magic_ptr = g_magic_list;
	enemy_t* target;

	for (int i = 0; i < MAGIC_MAX_NUMBER; ++i, ++magic_ptr) {
		// ������ ������ ���ؼ��� �˻�.
		if (!(magic_ptr->is_spawned)) { 
			continue;
		}

		target = (enemy_t*)magic_ptr->target_ptr;
		if (is_collided_with_target(magic_ptr)) {
			// �浹 �� ������ �Ҹ�
			magic_ptr->is_spawned = 0;

			// Ÿ���� ��ġ���� ���� ������ ����
			if (magic_ptr->type != target->current_pattern) {
				continue;
			}

			// ���� �� �������� ������ ����
			if (target->received_attack_count < (target->life-1)) { 
				target->received_attack_count += 1;
				target->current_pattern = target->pattern[target->received_attack_count];

				DEBUG_PRINT("%d %d\n", i, target->received_attack_count);
			} else {
				// TODO: Enemy ���� �� �Լ� ȣ���ϱ�
				(target->is_spawned) = 0;

				DEBUG_PRINT("�� ���� life = %d - %d", target->received_attack_count, target->life);
			}
		}
	}
}

void clear_magic(void)
{
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

		if (!(((enemy_t*)magic_ptr->target_ptr)->is_spawned)) {
			// ����� ������� �Ҹ�
			magic_ptr->is_spawned = false;
			continue;
		}

		//1. ���� ����
		float magic_dx =  (((enemy_t*)magic_ptr->target_ptr)->pos_x) - (magic_ptr->pos_x);
		float magic_dy =  (((enemy_t*)magic_ptr->target_ptr)->pos_y) - (magic_ptr->pos_y);
		
		//2. ���� ����
		float len = (float) sqrt((magic_dx * magic_dx) + (magic_dy * magic_dy));
		
		// �̹� ��ģ ������ ��
		if (len == 0) continue; 
		
		// ���� ����
		magic_dx /= len; 
		magic_dy /= len;
		
		//3. �ӵ��̵�
		magic_ptr->pos_x += (magic_dx*4 * (magic_ptr->velocity));
		magic_ptr->pos_y += (magic_dy*4 * (magic_ptr->velocity));
	}
}

