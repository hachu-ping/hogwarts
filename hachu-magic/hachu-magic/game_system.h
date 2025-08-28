#ifndef __GAME_SYSTEM_H__
#define __GAME_SYSTEM_H__

#define KEY_SEEN     1
#define KEY_DOWN     2


/**
 * 키보드 입력에 따라 전역변수 g__key[]에 현재 각 기호에 대한 키보드의 입력 여부를 업데이트합니다.
 * @param event: ALLEGRO_EVENT* 를 통해 이벤트 입력을 감지합니다.
 */
void keyboard_update(ALLEGRO_EVENT* event);

#endif /* __GAME_SYSTEM_H__ */

