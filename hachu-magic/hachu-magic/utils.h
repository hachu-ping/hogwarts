#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdbool.h>

/**
 * ù ��° ���ڷ� ���޵� ���� ��ȿ���� �˻��մϴ�. ���� �ش� ���� false (0) �̶�� description �� ����ϰ� ���α׷��� �����մϴ�.
 * @param test: ��ȿ�� �˻� ���
 * @param description : ����� ���� ��ȿ���� �ʴٸ� (0�̶��) �ش� �޽����� ���
 * @return void / ���� 0�̶�� ���α׷� ����
 */
void must_init(bool, const char*);

#endif /* __UTILS_H__ */


/**
 * A brief description. A more elaborate class description
 * @param somebool a boolean argument.
 * @return The test results
 */
