

#include "enemy.h"
#include "magic.h"

// TODO: define max magic number
magic_t g_magic_list[MAGIC_MAX_NUMBER];
extern enemy_t g_enemy_list[ENEMY_MAX_NUMBER];


void create_magic(int pos_x, int pos_y, char type, enemy_t* target)
{
	for (int i = 0; i < MAGIC_MAX_NUMBER; i++) {
		if (g_magic_list[i].is_spawned == false) {  // 비어 있는 슬롯 발견
			g_magic_list[i].pos_x = pos_x;
			g_magic_list[i].pos_y = pos_y;
			g_magic_list[i].size_w = 100;
			g_magic_list[i].size_h = 100;
			g_magic_list[i].velocity = 3.0;
			g_magic_list[i].type = type;
			g_magic_list[i].target_ptr = (void*)target;

			g_magic_list[i].is_spawned = true;

			printf("%d에 마법 생성\n", i);
			return;
		}
	}

	//  모든 슬롯이 꽉 찼을 경우
	printf("[MAGIC] 생성 실패! 사용 가능한 마법 슬롯이 없습니다.\n");
}

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
		g_magic_list[0].velocity = 4.0;
		g_magic_list[1].velocity = 3.0;
		g_magic_list[2].velocity = 1.0;
		g_magic_list[3].velocity = 0.9;
		//g_magic_list[i].velocity = 2.0;
		//g_magic_list[i].target_ptr = &g_enemy_list[i];
		g_magic_list[i].target_ptr = &g_enemy_list[0];
	}

}

//임시 -> 층돌 시스템
bool is_collide_with_magic(magic_t* magic_ptr)
{
	if (magic_ptr == NULL) {
		return false;
	}

	double ax1 = (magic_ptr->pos_x);
	double ay1= (magic_ptr->pos_y);
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


//충돌 처리 함수
void collide_magic(void) 
{
	magic_t* magic_ptr = g_magic_list;

	enemy_t* target;

	for (int i = 0; i < MAGIC_MAX_NUMBER; ++i, ++magic_ptr) {
		if (!(magic_ptr->is_spawned)) { //생성된 마법에 대해서만 검사.
			continue;
		}

		target = (enemy_t*)magic_ptr->target_ptr;
		if (is_collide_with_magic(magic_ptr)) {
			magic_ptr->is_spawned = 0;

			if (magic_ptr->type != target->current_pattern) {
				// 타입이 일치하지 않은 공격은 무시
				continue;
			}

			if (target->received_attack_count < (target->life-1)) { //적의 총 생명보다 작을때 까지
				target->received_attack_count += 1;
				target->current_pattern = target->pattern[target->received_attack_count];
				printf("%d %d\n", i, target->received_attack_count);
			}
			else {

				// TODO: Enemy 죽을 때 함수 호출하기
				(target->is_spawned) = 0;
				printf("적 죽음 life = %d - %d", target->received_attack_count, target->life);
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
//나중에 마법이 움직이는 값을 변주할 때 사용
double delta_move_magic(void) {
	extern g_frames;
	return ((rand() % 5) + 1)*fabsf(sinf(0.5*g_frames)) + 0.5;
}*/

//한 프레임만 생각할 것.
void move_magic(void) {
	magic_t* magic_ptr = g_magic_list;

	for (int i = 0; i < MAGIC_MAX_NUMBER; ++i, ++magic_ptr) {
		if (!(magic_ptr->is_spawned)) {
			continue;
		}

		if (!(((enemy_t*)magic_ptr->target_ptr)->is_spawned)) {
			// 대상이 사라지면 소멸
			magic_ptr->is_spawned = false;
			continue;
		}

		//1. 방향 벡터
		float magic_dx =  (((enemy_t*)magic_ptr->target_ptr)->pos_x) - (magic_ptr->pos_x);
		float magic_dy =  (((enemy_t*)magic_ptr->target_ptr)->pos_y) - (magic_ptr->pos_y);
		//2. 벡터 길이
		float len = (float) sqrt((magic_dx * magic_dx) + (magic_dy * magic_dy));
		if (len == 0) continue; // 이미 겹친 상태일 때
		magic_dx /= len; // 단위 벡터
		magic_dy /= len;
		//3. 속도이동
		magic_ptr->pos_x += (magic_dx*4 * (magic_ptr->velocity));
		magic_ptr->pos_y += (magic_dy*4 * (magic_ptr->velocity));
	}
}

