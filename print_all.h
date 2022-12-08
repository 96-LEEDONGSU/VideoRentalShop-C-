void video_print() {
	system("title ���� �뿩 ���α׷� - ���� ���");
	system("cls");
	printf("===============================���� ���� ���=================================\n");
	printf("����� ��� ������ ����մϴ�.\n");
	FILE* VIFp;
	fopen_s(&VIFp, "Vinfo.txt", "r+");

	struct video_info VI;
	memset(&VI, NULL, sizeof(VI));


	if (VIFp == NULL) {
		printf("���Ͽ� ���� ������ �߻��Ͽ����ϴ�.\n");
		printf("�޴��� ���ư��ϴ�.\n");
		return;
	}

	while (feof(VIFp) == 0) {
		fread(&VI, sizeof(VI), 1, VIFp);
		if (feof(VIFp) != 0) {//���Ͽ� ���� �����Ͽ��� while�� ����ǹǷ� �����ϵ��� ��.
			break;
		}
		printf("���� �̸� : %s", VI.video_name);
		printf("���� ��ȣ : [%d]\n", VI.video_num);
		printf("���� ���ۻ� : %s", VI.video_production_company);
		printf("���� �뿩���� : %d\n", VI.video_rental_fee);
		printf("���� �帣 : ");
		for (int L = 0; L <= 22; L++) {
			genre_translation(VI.video_genre[L]); //�帣��ȣ�� �帣������ ��ȯ
		}
		printf("\n���� ���� : %d\n", VI.same_video_num);
		printf("\n\n");
	}
	fclose(VIFp);
}

void member_print() {
	system("title ���� �뿩 ���α׷� - ȸ�� ���");
	system("cls");
	printf("================================���� ȸ�� ���==================================\n");
	printf("����� ��� ȸ���� ����մϴ�.\n");
	FILE* MIFp;
	struct membership_info MI;
	memset(&MI, NULL, sizeof(MI));
	fopen_s(&MIFp, "MSinfo.txt", "r+");

	if (MIFp == NULL) {
		printf("���Ͽ� ���� ������ �߻��Ͽ����ϴ�.\n");
		printf("�޴��� ���ư��ϴ�.\n");
		return;
	}

	if (feof(MIFp) == 0) {
		while (feof(MIFp) == 0) {
			fread(&MI, sizeof(MI), 1, MIFp);
			if (feof(MIFp) != 0) {//���Ͽ� ���� �����Ͽ��� while���� ����ǹǷ� �����ϵ��� ��.
				break;
			}
			printf("ȸ�� �̸� : %s", MI.membership_name);
			printf("ȸ�� ��ȣ : %d\n", MI.membership_number);
			printf("ȸ�� ��ȭ��ȣ : %s\n", MI.membership_phonenum);
			printf("ȸ�� ������� : %s\n", MI.membership_socialnum);
			printf("ȸ���� �뿩�� ���� ��� : ");
			if (MI.Rental_Video_List[0] == NULL)
				printf("����\n");
			for (int i = 0; i < 30; i++) {
				tras_video(MI.Rental_Video_List[i]);
			}
			printf("\n\n");
		}
	}
	fclose(MIFp);
}