void video_return() {
	rewind(stdin);
	system("cls");
	system("title ���� �뿩 ���α׷� - ���� �ݳ�");
	FILE* MIFp;
	FILE* VIFp;
	fopen_s(&MIFp, "MSinfo.txt", "r+");

	struct membership_info MI;//ȸ������ ����ü MI
	struct video_info VI;//�������� ����ü VI
	char video_name[50];//���� ����ü ����� �����̸��� ������ ũ��
	int video_num = -1;//���� ����ü ����� ������ȣ�� ������ ũ��
	char member_name_search[20];//ȸ�� ����ü ����� ȸ���̸��� ������ ũ��
	int member_num_search = -1;//ȸ������ü ����� ȸ����ȣ�� ������ ũ��
	int i = -1;
	int k = -1;

	if (MIFp == 0) {
		printf("���Ͽ� ���� ������ �߻��Ͽ����ϴ�.\n");
		printf("�޴��� ���ư��ϴ�.\n");
		return;
	}

	memset(&MI, 0, sizeof(MI));
	memset(&VI, 0, sizeof(VI));
	memset(&video_name, 0, sizeof(video_name));

	fseek(MIFp, 0, SEEK_SET);

	printf("�ݳ��Ϸ��� ȸ���� ������ �Է��ϼ���.\n");
	printf("ȸ�� �̸����� �Է��Ϸ��� 1�� �Է��ϼ���.\n");
	printf("ȸ�� ��ȣ�� �Է��Ϸ��� 2�� �Է��ϼ���.\n");
	printf("����ȭ������ ���ư����� 0�� �Է��ϼ���.\n");
	printf(">");
	scanf_s("%d", &i);

	fpos_t pos_member;
	fpos_t pos_video;
	if (i == 1) {//ȸ�� �̸����� ���� ������ �˻�
		printf("==================================���� �ݳ�===================================\n");

		while (k != 0) {
			printf("\n���� �ݳ��� ���߷��� 0�� �Է��ϼ���.\n");
			printf("����Ϸ��� 1�� �Է��ϼ���.\n");
			rewind(stdin);
			scanf_s("%d", &k);
			if (k == 0) {
				fclose(MIFp);
				break;
			}
			printf("[�ݳ��� ȸ���� �̸��� �Է��ϼ���.]\n");
			rewind(stdin);
			printf(">");
			fgets(member_name_search, sizeof(member_name_search), stdin);
			
			while (feof(MIFp) == 0) {
				fgetpos(MIFp, &pos_member);
				fread(&MI, sizeof(MI), 1, MIFp);
				if (strcmp(member_name_search, MI.membership_name) == 0) {
					printf("ȸ���� �̸� [%s]�� ã�ҽ��ϴ�.\n", member_name_search);
					printf("�̸� : %s", MI.membership_name);
					printf("��ȭ��ȣ : %s\n", MI.membership_phonenum);
					printf("������� : %s\n", MI.membership_socialnum);
					printf("ȸ����ȣ : [%d]\n", MI.membership_number);
					printf("�뿩�� ���� ��� :");
					if (MI.Rental_Video_List[0] == NULL) {
						printf("�뿩�� ������ �����ϴ�.\n");
					}
					for (int i = 0; i < 30; i++) {
						tras_video(MI.Rental_Video_List[i]);
					}
					printf("�̸��� �ߺ��Ǵ� ��� ȸ����ȣ�� �̿��Ͽ� ȸ���� �����Ͻʽÿ�.\n");
					while (1) {

						fopen_s(&VIFp, "Vinfo.txt", "r+");
						fseek(VIFp, 0, SEEK_SET);

						printf("[�ݳ��Ϸ��� ���� ��ȣ�� �Է��ϼ���.]\n");
						scanf_s("%d", &video_num);
						for (int i = 0; i < 30; i++) {
							if (MI.Rental_Video_List[i] == video_num) {

								fclose(VIFp);
								tras_video(MI.Rental_Video_List[i]);

								printf("\n�ش� ������ �ݳ��մϴ�.\n");
								MI.Rental_Video_List[i] = 0;

								fopen_s(&VIFp, "Vinfo.txt", "r+");
								fseek(VIFp, 0, SEEK_SET);
								while (feof(VIFp) == 0) {
									fgetpos(VIFp, &pos_video);
									fread(&VI, sizeof(VI), 1, VIFp);
									if (VI.video_num == video_num) {
										VI.same_video_num = VI.same_video_num++;
										fsetpos(VIFp, &pos_video);
										fwrite(&VI, sizeof(VI), 1, VIFp);
										fclose(VIFp);
										break;
									}
								}
							}
						}
						printf("�ݳ��Ϸ��� ������ �����ϴ�.\n");
						fclose(VIFp);
						break;
					}

					fsetpos(MIFp, &pos_member);
					fwrite(&MI, sizeof(MI), 1, MIFp);
					
					break;
				}
				else if ((strcmp(VI.video_name, video_name) != 0)) {
					printf("����� ���� �� �ش� �̸��� ������ �����ϴ�.\n");
					printf("���� �̸��� Ȯ���ϰ� �ٽ� �ݳ��ϰų� ���� ��ȣ�� �ݳ��ϼ���.\n");
					break;
				}
			}
		}
		fclose(MIFp);
		return;
	}
	if (i == 2) {
		printf("==================================���� �ݳ�===================================\n");
		rewind(stdin);
		int j = -1;
		printf("[�ݳ��� ȸ���� ȸ����ȣ�� �Է��ϼ���.]\n");
		scanf_s("%d", &j);
		while (feof(MIFp) == 0) {
			fgetpos(MIFp, &pos_member);
			fread(&MI, sizeof(MI), 1, MIFp);
			if ((MI.membership_number == j)) {
				printf("ȸ����ȣ [%d]�� ���� ȸ���� ã�ҽ��ϴ�.\n", j);
				printf("�̸� : %s", MI.membership_name);
				printf("��ȭ��ȣ : %s\n", MI.membership_phonenum);
				printf("������� : %s\n", MI.membership_socialnum);
				printf("ȸ����ȣ : [%d]\n", MI.membership_number);
				printf("�뿩�� ���� ��� :");
				for (int i = 0; i < 30; i++) {
					tras_video(MI.Rental_Video_List[i]);
				}
				while (1) {
					fopen_s(&VIFp, "Vinfo.txt", "r+");
					fseek(VIFp, 0, SEEK_SET);
					printf("[�ݳ��Ϸ��� ���� ��ȣ�� �Է��ϼ���.]\n");
					scanf_s("%d", &video_num);
					for (int i = 0; i < 30; i++) {
						if (MI.Rental_Video_List[i] == video_num) {

							fclose(VIFp);
							tras_video(MI.Rental_Video_List[i]);

							printf("\n�ش� ������ �ݳ��մϴ�.\n");
							MI.Rental_Video_List[i] = 0;

							fopen_s(&VIFp, "Vinfo.txt", "r+");
							fseek(VIFp, 0, SEEK_SET);
							while (feof(VIFp) == 0) {
								fgetpos(VIFp, &pos_video);
								fread(&VI, sizeof(VI), 1, VIFp);
								if (VI.video_num == video_num) {
									VI.same_video_num = VI.same_video_num++;
									fsetpos(VIFp, &pos_video);
									fwrite(&VI, sizeof(VI), 1, VIFp);
									fclose(VIFp);
									break;
								}
							}
						}
					}
					printf("�ݳ��Ϸ��� ������ �����ϴ�.\n");
					fclose(VIFp);
					break;
				}

				fsetpos(MIFp, &pos_member);
				fwrite(&MI, sizeof(MI), 1, MIFp);

				break;
			}
			else if ((strcmp(VI.video_name, video_name) != 0)) {
				printf("����� ���� �� �ش� �̸��� ������ �����ϴ�.\n");
				printf("���� �̸��� Ȯ���ϰ� �ٽ� �ݳ��ϰų� ���� ��ȣ�� �ݳ��ϼ���.\n");
				break;
			}
		}
	}
	fclose(MIFp);
	return;
}