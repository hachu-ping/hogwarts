#include "audio.h"
#include "debug.h"
#include "enemy.h"
#include "fx.h"
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
		// 비어 있는 슬롯 찾기
		if (g_magic_list[i].is_spawned == false) {  
			g_magic_list[i].pos_x = pos_x;
			g_magic_list[i].pos_y = pos_y;
			g_magic_list[i].size_w = MAGIC_WIDTH;
			g_magic_list[i].size_h = MAGIC_HEIGHT;
			g_magic_list[i].velocity = 3.0;
			g_magic_list[i].type = type;
			g_magic_list[i].target_ptr = (void*)target;

			g_magic_list[i].is_spawned = true;

			DEBUG_PRINT("%d번 마법 생성\n", i);


			play_sound(GAME_SOUND_MAGIC_ATTACK, type);
			return;
		}
	}

	//  모든 마법슬롯이 다 찬 경우
	DEBUG_PRINT("[MAGIC] 마법 실패! 모든 마법슬롯이 가득 차있어 생성할수 없습니다.\n");
}

// 타겟과의 충돌 검사
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


// 충돌 처리 함수
void handle_magic_collision(void)
{
	magic_t* magic_ptr = g_magic_list;
	enemy_t* target;

	for (int i = 0; i < MAGIC_MAX_NUMBER; ++i, ++magic_ptr) {
		// 마법이 비활성 상태에서는 검사하지 않음.
		if (!(magic_ptr->is_spawned)) { 
			continue;
		}

		target = (enemy_t*)magic_ptr->target_ptr;
		if (is_collided_with_target(magic_ptr)) {
			// 충돌 시 마법객체 소멸
			magic_ptr->is_spawned = 0;

			create_explosion(magic_ptr->pos_x, magic_ptr->pos_y);

			// 타겟의 패턴과 마법 속성이 다른 경우
			if (magic_ptr->type != target->current_pattern) {
				continue;
			}

			// 적이 아직 죽지않았을 경우에 대한 처리
			if (target->received_attack_count < (target->life-1)) { 
				target->received_attack_count += 1;
				target->current_pattern = target->pattern[target->received_attack_count];

				play_sound(GAME_SOUND_ENEMY_DAMAGED, target->type);
				DEBUG_PRINT("%d %d\n", i, target->received_attack_count);
			} else {
				// TODO: Enemy 죽을 때 함수 호출하기
				(target->is_spawned) = 0;

				play_sound(GAME_SOUND_ENEMY_DIE, target->type);
				DEBUG_PRINT("적 사망 life = %d - %d", target->received_attack_count, target->life);
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
//나중에 마법에 다이나믹한 움직임을 줄 수 있는 함수
double delta_move_magic(void) {
	extern g_frames;
	return ((rand() % 5) + 1)*fabsf(sinf(0.5*g_frames)) + 0.5;
}*/

//매 프레임마다 마법을 움직임.
void move_magic(void) {
	magic_t* magic_ptr = g_magic_list;

	for (int i = 0; i < MAGIC_MAX_NUMBER; ++i, ++magic_ptr) {
		if (!(magic_ptr->is_spawned)) {
			continue;
		}

		if (!(((enemy_t*)magic_ptr->target_ptr)->is_spawned)) {
			// 타겟이 사라졌으면 소멸
			magic_ptr->is_spawned = false;
			continue;
		}

		//1. 방향 벡터
		float magic_dx =  (((enemy_t*)magic_ptr->target_ptr)->pos_x) - (magic_ptr->pos_x);
		float magic_dy =  (((enemy_t*)magic_ptr->target_ptr)->pos_y) - (magic_ptr->pos_y);
		
		//2. 벡터 길이
		float len = (float) sqrt((magic_dx * magic_dx) + (magic_dy * magic_dy));
		
		// 이미 도착한 경우는 제외
		if (len == 0) continue; 
		
		// 단위 벡터
		magic_dx /= len; 
		magic_dy /= len;
		
		//3. 속도이동
		magic_ptr->pos_x += (magic_dx*4 * (magic_ptr->velocity));
		magic_ptr->pos_y += (magic_dy*4 * (magic_ptr->velocity));
	}
}

