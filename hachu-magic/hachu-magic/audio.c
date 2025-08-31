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
    g_samples.background[0] = load_sample("assets/audio/bgm.mp3");
    g_samples.background[1] = load_sample("assets/audio/bgm.mp3");
    g_samples.background[2] = load_sample("assets/audio/bgm.mp3");

    g_samples.cat_damaged = load_sample("assets/audio/cat_damaged.mp3");

    g_samples.enemy_damaged[0] = load_sample("assets/audio/enemy_0_damaged.mp3");
    g_samples.enemy_damaged[1] = load_sample("assets/audio/enemy_1_damaged.mp3");
    g_samples.enemy_damaged[2] = load_sample("assets/audio/enemy_2_damaged.mp3");
    g_samples.enemy_damaged[3] = load_sample("assets/audio/enemy_3_damaged.mp3");
    
    g_samples.enemy_die[0] = load_sample("assets/audio/enemy_0_die.mp3");
    g_samples.enemy_die[1] = load_sample("assets/audio/enemy_1_die.mp3");
    g_samples.enemy_die[2] = load_sample("assets/audio/enemy_2_die.mp3");
    g_samples.enemy_die[3] = load_sample("assets/audio/enemy_3_die.mp3");

    g_samples.magic_attack[1] = load_sample("assets/audio/magic.mp3");
    g_samples.magic_attack[2] = load_sample("assets/audio/magic.mp3");
    g_samples.magic_attack[3] = load_sample("assets/audio/magic.mp3");
    g_samples.magic_attack[4] = load_sample("assets/audio/magic.mp3");
#endif
}

// 전역 변수로 효과음 ID 풀 관리
#define MAX_EFFECT_SOUNDS 40
ALLEGRO_SAMPLE_ID effect_sound_pool[MAX_EFFECT_SOUNDS];
int next_effect_slot = 0;

// 효과음 재생 시
ALLEGRO_SAMPLE_ID* get_next_effect_id() {
    ALLEGRO_SAMPLE_ID* id = &effect_sound_pool[next_effect_slot];
    next_effect_slot = (next_effect_slot + 1) % MAX_EFFECT_SOUNDS;
    return id;
}

void play_sound(game_sound_t type, ...)
{
    // 가변인자 목록 선언 및 초기화
    va_list args;
    va_start(args, type);
    char index;
    
    ALLEGRO_SAMPLE* play_target = NULL;
    ALLEGRO_PLAYMODE play_mode = ALLEGRO_PLAYMODE_ONCE;
    bool is_background = false;
    
    switch (type) {
    case GAME_SOUND_BACKGROUND:
        // 기존 배경음악 중단
        if (g_samples.bgm_instance != NULL) {
            al_stop_sample_instance(g_samples.bgm_instance);
            al_destroy_sample_instance(g_samples.bgm_instance);
            g_samples.bgm_instance = NULL;
        }
        
        index = va_arg(args, char);
        if (index < 0 || index >= BGM_TYPE_NUMBER) {
            break;
        }
        
        play_target = g_samples.background[index];
        play_mode = ALLEGRO_PLAYMODE_LOOP;
        is_background = true;
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
        DEBUG_PRINT("출력 %p\n", play_target);
        break;
        
    case GAME_SOUND_MAGIC_ATTACK:
        index = va_arg(args, char);
        if (index < 0 || index >= MAGIC_TYPE_NUMBER) {
            break;
        }
        //play_target = g_samples.magic_attack[index];
        break;
        
    default:
        play_target = NULL;
        DEBUG_PRINT("유효하지 않은 오디오 타입");
        break;
    }
    
    // 샘플 재생
    if (play_target != NULL) {
        ALLEGRO_SAMPLE_INSTANCE* instance = al_create_sample_instance(play_target);
        if (instance) {
            al_set_sample_instance_playmode(instance, play_mode);
            al_set_sample_instance_gain(instance, 1.0);
            al_attach_sample_instance_to_mixer(instance, al_get_default_mixer());
            
            if (is_background) {
                // 배경음악은 전역으로 관리
                g_samples.bgm_instance = instance;
            }
            
            al_play_sample_instance(instance);
            
            // 효과음은 재생 후 자동 정리 (배경음악이 아닌 경우)
            if (!is_background) {
                // 재생이 끝나면 인스턴스를 정리해야 하지만
                // 여기서는 간단히 재생만 시작
                // 실제로는 별도 스레드나 타이머에서 정리 필요
            }
        }
    }
    
    va_end(args);
}