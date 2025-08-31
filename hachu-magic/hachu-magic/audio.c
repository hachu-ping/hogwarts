#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdarg.h>

#include "audio.h"
#include "debug.h"
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
#if 1
    g_samples.background[0] = al_load_sample("assets/audio/bgm.wav");
    //g_samples.background[1] = al_load_sample("");
    //g_samples.background[2] = al_load_sample("assets/audio/");

    g_samples.cat_damaged = al_load_sample("assets/audio/cat_damaged.mp3");

    g_samples.enemy_damaged[0] = al_load_sample("assets/audio/enemy_0_damaged");
    g_samples.enemy_damaged[1] = al_load_sample("assets/audio/enemy_1_damaged");
    g_samples.enemy_damaged[2] = al_load_sample("assets/audio/enemy_2_damaged");
    g_samples.enemy_damaged[3] = al_load_sample("assets/audio/enemy_3_damaged");
    
    g_samples.enemy_die[0] = al_load_sample("assets/audio/enemy_0_die");
    g_samples.enemy_die[1] = al_load_sample("assets/audio/enemy_1_die");
    g_samples.enemy_die[2] = al_load_sample("assets/audio/enemy_2_die");
    g_samples.enemy_die[3] = al_load_sample("assets/audio/enemy_3_die");

    g_samples.magic_attack[1] = al_load_sample("assets/audio/magic.mp3");
    g_samples.magic_attack[2] = al_load_sample("assets/audio/magic.mp3");
    g_samples.magic_attack[3] = al_load_sample("assets/audio/magic.mp3");
    g_samples.magic_attack[4] = al_load_sample("assets/audio/magic.mp3");
#endif
}

void play_sound(game_sound_t type, ...)
{
    // 가변인자 목록 선언 및 초기화
    va_list args;
    va_start(args, 1);  
    char index;

    ALLEGRO_SAMPLE* play_target = NULL;
    ALLEGRO_PLAYMODE play_mode = ALLEGRO_PLAYMODE_ONCE;
    ALLEGRO_SAMPLE_ID* sample_id = NULL;

    switch (type) {
    case GAME_SOUND_BACKGROUND:
        if (g_samples.bgm_id != NULL) {
            al_stop_sample(g_samples.bgm_id);
        }

        index = va_arg(args, char);
        if (index < 0 || index >= BGM_TYPE_NUMBER) {
            break;
        }

        play_target = g_samples.background[index];
        play_mode = ALLEGRO_PLAYMODE_LOOP;
        sample_id = g_samples.bgm_id;
        break;
    case GAME_SOUND_CAT_DAMAGED:
        play_target = g_samples.cat_damaged;
        break;
    case GAME_SOUND_ENEMY_DAMAGED:
        index = va_arg(args, char);
        if (index < 0 || index >= ENEMY_TYPE_NUMBER) {
            break;
        }
        
        play_target = g_samples.enemy_damaged[index];
        break;
    case GAME_SOUND_ENEMY_DIE:
        index = va_arg(args, char);
        if (index < 0 || index >= ENEMY_TYPE_NUMBER) {
            break;
        }

        play_target = g_samples.enemy_die[index];
        break;
    case GAME_SOUND_MAGIC_ATTACK:
        index = va_arg(args, char);
        if (index < 0 || index >= MAGIC_TYPE_NUMBER) {
            break;
        }

        play_target = g_samples.magic_attack[index];
        break;
    default:
        play_target = NULL;
        DEBUG_PRINT("유효하지 않은 오디오 타입");
        break;
    }

    DEBUG_PRINT("출력 %d\n", type);
    al_play_sample(play_target, 1, 0, 1, play_mode, sample_id);
}

