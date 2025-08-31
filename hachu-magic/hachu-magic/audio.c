#include <allegro5/allegro_audio.h>

#include "audio.h"
#include "utils.h"

samples_t g_samples;

/**
 * 스프라이트 이미지를 분할하여 반환합니다.
 * 스프라이트 시트가 없다면 게임 프로그램이 종료됩니다.
 * @param filename: 가져올 샘플 오디오 파일 이름
 */
static ALLEGRO_SAMPLE* load_sample(char* filename)
{
    ALLEGRO_SAMPLE* sample = al_load_sample(filename);
    must_init(sample, "load sample");
    return sample;
}

void init_sample(void)
{
#if 0
    g_samples.background[0] = al_load_sample('samples/');
    g_samples.background[1] = al_load_sample('samples/');
    g_samples.background[2] = al_load_sample('samples/');

    g_samples.cat_damaged = al_load_sample('samples/');

    g_samples.enemy_damaged[0] = al_load_sample('samples/');
    g_samples.enemy_damaged[1] = al_load_sample('samples/');
    g_samples.enemy_damaged[2] = al_load_sample('samples/');
    g_samples.enemy_damaged[3] = al_load_sample('samples/');
    
    g_samples.enemy_die[0] = al_load_sample('samples/');
    g_samples.enemy_die[1] = al_load_sample('samples/');
    g_samples.enemy_die[2] = al_load_sample('samples/');
    g_samples.enemy_die[3] = al_load_sample('samples/');

    g_samples.magic_attack[0] = al_load_sample('samples/');
    g_samples.magic_attack[1] = al_load_sample('samples/');
    g_samples.magic_attack[2] = al_load_sample('samples/');
    g_samples.magic_attack[3] = al_load_sample('samples/');
#endif
}

