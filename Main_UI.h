#include <stdio.h>

// �޴� ����ȭ���� ����ϴ� �Լ�
int main_page() {
	system("title ���� �뿩 ���α׷�");
	printf("==============================���� �뿩 ���α׷�==============================\n");
	printf("1. ȸ�� �űԵ��\n");
	printf("2. ���� �űԵ��\n");
	printf("3. ���� �뿩\n");
	printf("4. ��ü ���� ���\n");
	printf("5. ��ü ȸ�� ���\n");
	printf("6. ȸ�� ����\n");
	printf("7. ���� �ݳ�\n");
	printf("11. ȭ���ʱ�ȭ\n");

	int select_num;
	printf(">");
	scanf_s("%d", &select_num);

	return select_num;
}