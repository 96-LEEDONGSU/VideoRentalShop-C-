#include <stdio.h>
#include <windows.h>
#include "Member_info_struct.h"//ȸ������ ����ü

void new_member() {
	system("title ���� �뿩 ���α׷� - ȸ�� ���");
	FILE* MIF;
	fopen_s(&MIF, "MSinfo.txt", "a+");//Member information

	if (MIF == NULL) {
		printf("���Ͽ� ���� ������ �߻��Ͽ����ϴ�.\n");
		printf("�޴��� ���ư��ϴ�.\n");
		return;
	}

	struct membership_info MI;//MI��� �̸��� ����ü ������ ����
	memset(&MI, NULL, sizeof(MI));//����ü������ 0���� �ʱ�ȭ

	//printf("%d", MI.membership_name[0]); //�̸� �ʱ�ȭ �׽�Ʈ��
	//printf("%d", MI.membership_phonenum[0]); //��ȭ��ȣ �ʱ�ȭ �׽�Ʈ��
	//printf("%d", MI.membership_socialnum[0]); // ������� �ʱ�ȭ �׽�Ʈ��


	//printf("����ü���� �ʱ�ȭȮ���׽�Ʈ��\n");
	//printf("%d\n", MI.membership_name[0]);
	
	/*while (getchar() != '\n') rewind ������ ��ü�Ͽ���.
		continue;*/

	rewind(stdin);

	printf("================================�ű� ȸ�� ���=================================\n");

	printf("[ȸ�� �̸��� �Է��ϼ���.]\n");
	printf("(ȸ�� �̸��� 19�����Ϸ� �ۼ��ϼ���.)\n");
	printf(">");
	fgets(MI.membership_name, sizeof(MI.membership_name), stdin);

	//printf("%d", MI.membership_name[0]);
	while (MI.membership_name[0] == NULL || MI.membership_name[0] == 10) {
		printf("ȸ�� �̸��� �ʼ� �Է� �����Դϴ�. \n");
		printf("ȸ�� �̸��� �Է��ϼ���. \n");
		fgets(MI.membership_name, sizeof(MI.membership_name), stdin);
	}

	printf("ȸ�� �̸� �Է��� �Ϸ��Ͽ����ϴ�.");

	rewind(stdin);
	system("cls");
	printf("===============================================================================\n");

	//printf("%d\n", MI.membership_phonenum[0]);

	printf("[ȸ���� ��ȭ��ȣ�� 11�ڸ� ��� �Է��ϼ���.]\n");
	printf("(������ (-) �Է½� ��ȭ��ȣ�� �ùٸ��� �Էµ��� �ʽ��ϴ�.) \n");
	printf(">");
	fgets(MI.membership_phonenum, sizeof(MI.membership_phonenum), stdin);

		while ((MI.membership_phonenum[0] == NULL) || (MI.membership_phonenum[0] == 10)) {
			printf("�ƹ��͵� �Էµ��� �ʾҽ��ϴ�.\n");
			printf("ȸ���� ��ȭ��ȣ�� �ʼ� �Է� �����Դϴ�. \n");
			printf("ȸ���� ��ȭ��ȣ�� �Է��ϼ���. \n");
			printf(">");
			fgets(MI.membership_phonenum, sizeof(MI.membership_phonenum), stdin);
		}

	int k = 0;
	for (int i = 0; i < 11; i++) {//��ȭ��ȣ ������ ���ڰ� �ƴ� ���� �ԷµǾ����� �Ǻ�, Ȯ�ε� ��� k�� 1�� �Է�
		if (!(MI.membership_phonenum[i] >= 48) && (MI.membership_phonenum[i] <= 57))
			k = 1;
		else if ( (MI.membership_phonenum[i] >= 48) && (MI.membership_phonenum[i] <= 57) )
			k = 0;
	}

	while (k == 1) {
		printf("[��ȭ��ȣ�� ���ڷ� �Է��Ͻʽÿ�.]\n");
		rewind(stdin);
		printf(">");
		fgets(MI.membership_phonenum, sizeof(MI.membership_phonenum), stdin);
		for (int i = 0; i < 11; i++) {//��ȭ��ȣ ������ ���ڰ� �ƴ� ���� �ԷµǾ����� �Ǻ�, Ȯ�ε� ��� k�� 1�� �Է�
			if ( !( ( MI.membership_phonenum[i] >= 48 ) && ( MI.membership_phonenum[i] <= 57 ) ) ) {
				k = 1;
				break;
			}
			else if ( ( MI.membership_phonenum[i] >= 48 ) && ( MI.membership_phonenum[i] <= 57 ) ) {
				k = 0;
			}
		}
	}
	if (k == 0)
		printf("��ȭ��ȣ�� �ùٸ��� �ԷµǾ����ϴ�.\n");

	

	rewind(stdin);
	system("cls");
	printf("===============================================================================\n");
	printf("[ȸ���� ��������� �Է��ϼ���.]\n");
	printf("(ȸ���� ��������� ���ο� ������ �뿩�ϱ� ���Ͽ� ���˴ϴ�.)\n");
	printf(">");
	fgets(MI.membership_socialnum, sizeof(MI.membership_socialnum), stdin);
	while ((MI.membership_socialnum[0] == NULL) || (MI.membership_socialnum[0] == 10)) {//�ƹ��͵� �Էµ��� �������
		printf("�ƹ��͵� �Էµ��� �ʾҽ��ϴ�.\n");
		printf("ȸ���� ��������� �ʼ� �Է� �����Դϴ�. \n");
		printf("ȸ���� ��������� �Է��ϼ���. \n");
		printf(">");
		fgets(MI.membership_socialnum, sizeof(MI.membership_socialnum), stdin);
	}

	printf("��������� �ùٸ��� �ԷµǾ����ϴ�.\n");

	rewind(stdin);

	printf("ȸ������� �Ϸ�Ǿ����ϴ�.\n");
	printf("===============================================================================\n");

	struct membership_info IMI;
	memset(&IMI, NULL, sizeof(IMI));
	
	int i=0;//ȸ����ȣ�� �����ϴ� ����
	fseek(MIF, 0, SEEK_SET);//������ ó������ �б�����
	while (feof(MIF) == 0) {//������ ������ �д� ���� while�� ����
		fread(&IMI, sizeof(IMI), 1, MIF);//MIũ��� MIF�� �о� 
		if (IMI.membership_number >= 0) { //MI.membership_number�� 0���� ū�� �����ϴ� ��� i�� 1 ������.
			i++;
		}
	}//������ ������ �о�� MI.membership_number�� �ѹ� �����ϸ� i++�� 1ȸ ����, �ι� �����ϸ� i++�� 2ȸ ����...
	MI.membership_number = i;//i�� ������ �� ���ϳ��� �����ϴ� ��ȣ���� �ϳ� ū ���� �Է���.

	printf("ȸ�� �̸� : %s", MI.membership_name);
	printf("ȸ�� ��ȣ : %d\n", MI.membership_number);
	printf("ȸ�� ��ȭ��ȣ : %s\n", MI.membership_phonenum);
	printf("ȸ�� ������� : %s\n", MI.membership_socialnum);

	fwrite(&MI, sizeof(MI), 1, MIF);//MI����ü ���Ͽ� ����
	fclose(MIF);
	printf("\n");
}