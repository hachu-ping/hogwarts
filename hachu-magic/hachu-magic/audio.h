#ifndef __AUDIO_H__
#define __AUDIO_H__

#include <allegro5/allegro_audio.h>

#define BGM_TYPE_NUMBER 3
#define ENEMY_TYPE_NUMBER 4
#define MAGIC_TYPE_NUMBER 4

typedef struct _samples
{
    ALLEGRO_SAMPLE* background[BGM_TYPE_NUMBER];

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
void init_sample(void);


#endif /* __AUDIO_H__ */