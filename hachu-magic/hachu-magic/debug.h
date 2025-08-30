#ifndef __DEBUG_H__
#define __DEBUG_H__

// ����� ����� ��Ȱ��ȭ ���ؼ��� �Ʒ� ���� �ּ�ó�� ���ּ���.
#define DEBUG_MODE

#ifdef DEBUG_MODE

/**
 * ���� �� ������� ���� printf �Դϴ�.
 * debug.h ������ #define DEBUG_MODE �� Ȱ��ȭ �Ǿ��ִٸ� 
 * ������ ������ ����մϴ�.
 * ��Ȱ��ȭ(�ּ�ó��)�Ǿ��ִٸ� ������� �ʽ��ϴ�.
 * @param printf�� �����ϰ� ���ڸ� ���޹޽��ϴ�.
 */
#define DEBUG_PRINT(fmt, ...) \
	do { \
		printf(fmt, ##__VA_ARGS__); \
	} while(0)
#else
	#define DEBUG_PRINT(fmt, ...) 
#endif /* DEBUG_ON */

#endif /* __DEBUG_H__ */