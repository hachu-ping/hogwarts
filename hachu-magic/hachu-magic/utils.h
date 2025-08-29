#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdbool.h>

#include "game_system.h"

/**
 * ù ��° ���ڷ� ���޵� ���� ��ȿ���� �˻��մϴ�. 
 * ���� �ش� ���� false (0) �̶�� description �� ����ϰ� ���α׷��� �����մϴ�.
 * @param test: ��ȿ�� �˻� ���
 * @param description : ����� ���� ��ȿ���� �ʴٸ� (0�̶��) �ش� �޽����� ���
 * @return void / ���� 0�̶�� ���α׷� ����
 */
void must_init(bool test, const char* description);

/**
 * �Է¹��� Ű �ڵ带 ���� ������ ��ȯ�մϴ�. 
 * ����Ű �̿��� ���� DIRECTION_NONE ���� ��ȯ�մϴ�.
 * @param keycode: �Է¹��� Ű�� allegro �ڵ尪
 * @return direction_t: ���⿡ ���� enum
 */
direction_t keycode_to_direction(char keycode);

/**
 * �Է¹��� ���� ���� ���� Ÿ�� ������ ��ȯ�մϴ�.
 * ���� �̿��� ���� MAGIC_TYPE_NONE ���� ��ȯ�մϴ�.
 * @param direction: ���� enum ��
 * @return magic_type_t: ���� Ÿ�Կ� ���� enum
 */
magic_type_t direction_to_magic_type(direction_t direction);

#endif /* __UTILS_H__ */


/**
 * A brief description. A more elaborate class description
 * @param somebool a boolean argument.
 * @return The test results
 */