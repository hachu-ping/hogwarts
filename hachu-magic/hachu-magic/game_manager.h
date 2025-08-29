#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__
#include <stdbool.h>
#define MAX_RANK 10
#define MAX_NAME_LEN 20


// ���� ���� ����ü
typedef struct {
    int current_stage;
    int g_cat_life;
    double gm_start_time;
    double gm_end_time;
    bool game_clear;
    bool game_over;
    double time_taken;
} GameState;



// ��ŷ ��Ʈ��
typedef struct {
    char name[MAX_NAME_LEN];
    float time;  // -1�� ���� ǥ��
} RankEntry;

// ���� ���� �ʱ�ȭ
void init_game(GameState*);

// ���� ���� ���� ����
void is_game_over(GameState* );

// ���� ���� ó�� (�ð� ��� �� Ŭ���� ���� ����)
void is_game_clear(GameState*);

// ��ŷ ���� �Լ���
void load_rankings(void);
void save_rankings(void);
int compare_scores(const void*, const void*);
void add_score(const char* , float );
void add_score_v2(const char*, float);
void print_rankings_screen(ALLEGRO_FONT*);






#endif /* __GAME_MANAGER_H__ */

