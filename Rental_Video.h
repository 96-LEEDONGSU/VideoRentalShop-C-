#include <stdio.h>
#include <windows.h>

void rental_video() {
	rewind(stdin);
	system("cls");//ȭ�� �ʱ�ȭ
	system("title ���� �뿩 ���α׷� - ���� �뿩");
	FILE* MIFp;
	fopen_s(&MIFp, "MSinfo.txt", "r+");
	FILE* VIFp;
	fopen_s(&VIFp, "Vinfo.txt", "r+");

	struct membership_info MI;//ȸ������ ����ü MI
	struct video_info VI;//�������� ����ü VI
	char member_name_search[20];//ȸ�� ����ü ����� ȸ���̸��� ������ ũ��
	int member_num_search = -1;//ȸ������ü ����� ȸ����ȣ�� ������ ũ��
	char video_name[50];//���� ����ü ����� �����̸��� ������ ũ��
	int video_num = -1;//���� ����ü ����� ������ȣ�� ������ ũ��
	int i = -1;//ȸ���̸��� ��ȣ �˻� ����
	fpos_t pos_member;
	fpos_t pos_video;


	if (MIFp == 0 || VIFp == 0) {
		printf("���Ͽ� ���� ������ �߻��Ͽ����ϴ�.\n");
		printf("�޴��� ���ư��ϴ�.\n");
		return;
	}

	memset(&MI, 0, sizeof(MI));
	memset(&VI, 0, sizeof(VI));
	memset(&video_name, 0, sizeof(video_name));
	memset(&member_name_search, 0, sizeof(member_name_search));//ȸ���̸� ã�⸦ �ʱ�ȭ
	fseek(MIFp, 0, SEEK_SET);

	//char* FINDp = NULL;
	printf("[ȸ���� �̸����� �˻��Ϸ��� 1�� �Է��ϼ���.]\n");
	printf("[ȸ����ȣ�� �˻��Ϸ��� 2�� �Է��ϼ���.]\n");
	printf("ȸ���� ������ ��ȣ�θ� �����մϴ�.\n");
	printf(">");
	scanf_s("%d", &i);

		if(i == 1) {
			fseek(MIFp, 0, SEEK_SET);
			printf("==================================���� �뿩===================================\n");
			printf("[�뿩�� ȸ���� �̸��� �Է��ϼ���.]\n");

			rewind(stdin);
			rewind(stdout);

			printf(">");
			fgets(member_name_search, sizeof(member_name_search), stdin);

			while (feof(MIFp) == 0) {
				fgetpos(MIFp, &pos_member);
				fread(&MI, sizeof(MI), 1, MIFp);
				if (strcmp(MI.membership_name, member_name_search) == 0) {
					printf("ȸ���� �̸� %s�� ã�ҽ��ϴ�.\n", member_name_search);
					printf("�̸� : %s", MI.membership_name);
					printf("��ȭ��ȣ : %s\n", MI.membership_phonenum);
					printf("������� : %s\n", MI.membership_socialnum);
					printf("ȸ����ȣ : [%d]\n", MI.membership_number);

					printf("�̸��� �ߺ��Ǵ� ��� ȸ����ȣ�� �̿��Ͽ� ȸ���� �����Ͻʽÿ�.\n");
					break;
				}
				else if ((feof(MIFp) != 0) && (MI.membership_number != member_num_search)) {
					printf("�̸��� ã�� ���߽��ϴ�.\n");
					video_num = 0;
					fclose(MIFp);
					fclose(VIFp);

					return;
				}
			}
			rewind(stdin);
		}

		else if(i == 2) {
			printf("==================================���� �뿩===================================\n");

			printf("[�뿩�� ȸ���� ��ȣ�� �Է��ϼ���.]\n");

			rewind(stdin);

			printf(">");
			scanf_s("%d", &member_num_search);

			while (feof(MIFp) == 0) {
				fgetpos(MIFp, &pos_member);
				fread(&MI, sizeof(MI), 1, MIFp);
				if ((MI.membership_number) == (member_num_search)) {
					printf("ȸ����ȣ [%d]�� ��ġ�ϴ� ȸ���� ã�ҽ��ϴ�.\n", MI.membership_number);

					printf("�̸� : %s", MI.membership_name);
					printf("��ȭ��ȣ : %s\n", MI.membership_phonenum);
					printf("������� : %s\n", MI.membership_socialnum);
					printf("���� <��������� Ȯ���ϰ� ������ �뿩�Ͻʽÿ�.>\n");
					break;//ȸ����ȣ�� �ߺ��� �� �����Ƿ� ���� ������ Ȯ���� �ʿ䰡 ����. 
				}
				else if ((feof(MIFp) != 0) && (MI.membership_number != member_num_search)){
					printf("��ġ�ϴ� ȸ����ȣ�� �����ϴ�.\n");
					fclose(MIFp);
					fclose(VIFp);
					return;
				}
			}
		}
		else {
			printf("�߸��� ��ȣ�� �����Ͽ����ϴ�.\n");
			printf("�뿩�Ϸ��� ȸ���� �����Ͽ��� �մϴ�.\n");
		}
	rewind(stdin);

	int k = 0;
	while (video_num != 0) {
		printf("\n\n���� �뿩�� ���߷��� 0�� �Է��ϼ���.\n");
		printf("�ش� ȸ�� [%d]�� �뿩�� ����˴ϴ�.\n", MI.membership_number);
		printf("[�뿩�Ϸ��� ������ ��ȣ�� �Է��ϼ���.]\n");
		rewind(stdin);
		printf(">");
		scanf_s("%d", &video_num);

		fseek(VIFp, 0, SEEK_SET);
		while (feof(VIFp) == 0) {
			fgetpos(VIFp, &pos_video);
			fread(&VI, sizeof(VI), 1, VIFp);
			if (VI.same_video_num > 0) {
				if (k >= 29) {
					printf("�ش� ������ ��� �����ϴ�.\n");
					printf("�뿩�� �����մϴ�.\n");
					break;
				}
				MI.Rental_Video_List[k] = video_num;
				MI.rental_fee = VI.video_rental_fee + MI.rental_fee;
				printf("���� �̸� : %s", VI.video_name);
				printf("���� ���ۻ� : %s", VI.video_production_company);
				printf("���� �뿩���� : %d\n", VI.video_rental_fee);
				printf("���� �帣 : ");
				for (int L = 0; L <= 22; L++) {
					genre_translation(VI.video_genre[L]); //�帣��ȣ�� �帣������ ��ȯ
				}
				printf("���� ��ȣ : [%d]\n", VI.video_num);
				printf("�ش� ������ �뿩�մϴ�.\n");
				VI.same_video_num = VI.same_video_num - 1;
				fsetpos(MIFp, &pos_member);
				fwrite(&MI, sizeof(MI), 1, MIFp);
				fsetpos(VIFp, &pos_video);
				fwrite(&VI, sizeof(VI), 1, VIFp);
				k++;
				break;
			}
			else if ((video_num != VI.video_num)&&(feof(VIFp) != 0)) {
				printf("ã������ ������ �����ϴ�.\n");
				printf("��� �뿩�� �����մϴ�.\n");
				break;
				/*fsetpos(MIFp, &pos_member);
				fwrite(&MI, sizeof(MI), 1, MIFp);
				fsetpos(VIFp, &pos_video);
				fclose(MIFp);
				fclose(VIFp);
				return;*/
			}
		}
	}

	fsetpos(MIFp, &pos_member);
	fwrite(&MI, sizeof(MI), 1, MIFp);
	fsetpos(VIFp, &pos_video);
	fwrite(&VI, sizeof(VI), 1, VIFp);

	fclose(MIFp);
	fclose(VIFp);
	printf("\n");
}