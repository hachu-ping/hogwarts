#ifndef __AUDIO_H__
#define __AUDIO_H__

#include <allegro5/allegro_audio.h>

#define BGM_TYPE_NUMBER 3
#define ENEMY_TYPE_NUMBER 4
#define MAGIC_TYPE_NUMBER 5

typedef enum _game_sound {
    GAME_SOUND_BACKGROUND,
    GAME_SOUND_CAT_DAMAGED,
    GAME_SOUND_ENEMY_DAMAGED,
    GAME_SOUND_ENEMY_DIE,
    GAME_SOUND_MAGIC_ATTACK,
    GAME_SOUND_NONE,
} game_sound_t;

typedef struct _samples
{
    ALLEGRO_SAMPLE* background[BGM_TYPE_NUMBER];
    ALLEGRO_SAMPLE_INSTANCE* bgm_instance;

    ALLEGRO_SAMPLE* cat_damaged;

    ALLEGRO_SAMPLE* enemy_damaged[ENEMY_TYPE_NUMBER];
    ALLEGRO_SAMPLE* enemy_die[ENEMY_TYPE_NUMBER];

    ALLEGRO_SAMPLE* magic_attack[MAGIC_TYPE_NUMBER];

} samples_t;

extern samples_t g_samples;

/**
 * 사운드 에셋을 로드해 저장합니다.
 * 사운드 로드에 실패할 경우 프로그램을 종료합니다.
 */
void load_audios(void);

/**
 * 전달한 타입의 사운드를 출력합니다.
 * BGM이 전달된 경우 반복하여 재생하며, 기존 BGM을 종료하고 새로운 사운드를 재생합니다.
 * 이외의 사운드는 1회 재생합니다.
 * @param type: game_sound_t enum 타입의 값을 전달해주세요.
 * @param 추가인자: char 자료형으로 번호를 전달하면 해당 번호의 사운드를 출력합니다.
 * / 고양이는 추가 입력 필요없음.
 * / 적은 type을 전달해주세요.
 * / 마법은 type을 전달해주세요.
 */
void play_sound(game_sound_t type, ...);

#endif /* __AUDIO_H__ */