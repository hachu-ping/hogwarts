#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__
#include <stdbool.h>
#define MAX_RANK 10
#define MAX_NAME_LEN 20


// 게임 상태 구조체
typedef struct {
    int current_stage;
    int g_cat_life;
    double gm_start_time;
    double gm_end_time;
    bool game_clear;
    bool game_over;
    double time_taken;
} GameState;



// 랭킹 엔트리
typedef struct {
    char name[MAX_NAME_LEN];
    float time;  // -1은 실패 표시
} RankEntry;

// 게임 상태 초기화
void init_game(GameState*);

// 게임 종료 여부 판정
void is_game_over(GameState* );

// 게임 종료 처리 (시간 계산 및 클리어 여부 설정)
void is_game_clear(GameState*);

// 랭킹 관련 함수들
void load_rankings(void);
void save_rankings(void);
int compare_scores(const void*, const void*);
void add_score(const char* , float );
void add_score_v2(const char*, float);
void print_rankings_screen(ALLEGRO_FONT*);






#endif /* __GAME_MANAGER_H__ */

