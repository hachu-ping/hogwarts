#ifndef __GAME_SYSTEM_H__
#define __GAME_SYSTEM_H__

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define KEY_SEEN     1
#define KEY_DOWN     2

#define SCREEN_WIDTH 1400
#define SCREEN_HEIGHT 800

extern unsigned char key[ALLEGRO_KEY_MAX];

typedef enum _magic_type {
    MAGIC_TYPE_NONE   = 0,
    MAGIC_TYPE_FIRE   = 1,
    MAGIC_TYPE_WATER  = 2,
    MAGIC_TYPE_AIR    = 3,
    MAGIC_TYPE_NATURE = 4
} magic_type_t;

typedef enum _direction {
    DIRECTION_NONE  = 0,
    DIRECTION_LEFT  = 1,
    DIRECTION_RIGHT = 2,
    DIRECTION_UP    = 3,
    DIRECTION_DOWN  = 4
} direction_t;


#if defined(_MSC_VER)
#define STRCPY_SAFE(dst, src) strncpy_s(dst, sizeof(dst), src, _TRUNCATE)
#else
#define STRCPY_SAFE(dst, src) snprintf(dst, sizeof(dst), "%s", src)
#endif

typedef enum { SCENE_TITLE, SCENE_PLAY, SCENE_RANK } Scene;

typedef struct {
    float x, y, w, h;
    const char* label;
} Button;

static inline bool point_in_button(float mx, float my, Button* b) {
    return (mx >= b->x && mx <= b->x + b->w && my >= b->y && my <= b->y + b->h);
}

// ÅØ½ºÆ® ¹Ú½º
typedef struct {
    float x, y, w, h;
    bool  focused;
    int   maxlen;
    int   len;
    char  text[64];   // ÃÖ´ë 63ÀÚ + '\0' (¿øÇÏ¸é Å©±â ´Ã¸®¼¼¿ä)
} TextBox;

extern TextBox g_name_box;        // Àü¿ª ÅØ½ºÆ®¹Ú½º
extern char    g_player_name[64]; // ½ÃÀÛ ½Ã º¹»çÇØµÑ ÇÃ·¹ÀÌ¾î ÀÌ¸§

// ÇÔ¼ö ¼±¾ğ
void textbox_init(TextBox* tb, float x, float y, float w, float h, int maxlen);
void textbox_draw(const TextBox* tb, ALLEGRO_FONT* font);
bool textbox_handle_event(TextBox* tb, const ALLEGRO_EVENT* ev); // º¯°æ ÀÖÀ¸¸é true


//¿ÜºÎ º¯¼ö ¼±¾ğ
extern Scene g_scene_screne;
extern ALLEGRO_FONT* g_font;  // ³»Àå ÆùÆ®(º°µµ TTF ¾øÀÌ)
extern ALLEGRO_FONT* g_font_btn;
extern Button g_btn_start;
extern Button g_btn_rank;

/**
 * í‚¤ë³´ë“œ ì…ë ¥ì— ë”°ë¼ ì „ì—­ë³€ìˆ˜ g__key[]ì— í•´ë‹¹ í‚¤ ë²ˆí˜¸ì— ë”°ë¥¸ í‚¤ë³´ë“œ ì…ë ¥ ìƒíƒœë¥¼ ì—…ë°ì´íŠ¸í•©ë‹ˆë‹¤.
 * @param event: ALLEGRO_EVENT* ë¥¼ ë§¤ê°œ ì´ë²¤íŠ¸ ì…ë ¥ì„ ë°›ìŠµë‹ˆë‹¤.
 */
void keyboard_update(ALLEGRO_EVENT* event);

void draw_title_screen(void);
void draw_rank_screen(void);
void textbox_clear(TextBox* tb);
void handle_start_from_title(ALLEGRO_EVENT_QUEUE* main_queue);

#endif /* __GAME_SYSTEM_H__ */

