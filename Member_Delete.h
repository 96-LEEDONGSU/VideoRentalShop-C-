// Delete member function
void delete_member() {
	system("title ���� �뿩 ���α׷� - ȸ�� ����");
	FILE* MIFp;
	fopen_s(&MIFp, "MSinfo.txt", "r+");

	if (MIFp == NULL) {
		printf("���Ͽ� ���� ������ �߻��Ͽ����ϴ�.\n");
		printf("�޴��� ���ư��ϴ�.\n");
		return;
	}
	fseek(MIFp, 0, SEEK_SET);

	struct membership_info MI;
	memset(&MI, NULL, sizeof(MI));
	struct membership_info temporary_MI;
	memset(&temporary_MI, NULL, sizeof(temporary_MI));


	printf("===============================���� ȸ�� ����=================================\n");

	printf("�����Ϸ��� ȸ���� �����Ͽ��� �մϴ�.\n");
	int d_n = -1;
	printf("1. ȸ�� �̸�\n");
	printf("2. ȸ�� ��ȣ\n");
	printf(">");
	scanf_s("%d", &d_n);

	// member name searching
	if (d_n == 1) {
		system("cls");
		printf("ȸ���� �̸��� �˻��Ͽ� �����մϴ�.\n");
		printf("�ߺ��Ǵ� ��� ȸ����ȣ�� �����Ͽ� �����մϴ�.\n\n");

		printf("[�����Ϸ��� ȸ���� �̸��� �Է��ϼ���.]\n");
		printf("(ȸ���� �̸��� 19�� �̳��� �ۼ��ϼ���.)\n");
		rewind(stdin);
		printf(">");
		fgets(temporary_MI.membership_name, sizeof(temporary_MI.membership_name), stdin);

		while (feof(MIFp) == 0) 
		{
			fpos_t pos;
			fgetpos(MIFp, &pos);
			fread(&MI, sizeof(MI), 1, MIFp);

			if (strcmp(MI.membership_name, temporary_MI.membership_name) == 0) {
				printf("��ġ�ϴ� ȸ���� ã�ҽ��ϴ�.\n");
				printf("ȸ�� �̸� : %s", MI.membership_name);
				printf("ȸ�� ��ȣ : %d\n", MI.membership_number);
				printf("ȸ�� ��ȭ��ȣ : %s\n\n", MI.membership_phonenum);
				printf("�����Ϸ��� 1, �����Ϸ��� 0�� �Է��ϼ���.\n");
				int k = -1;
				printf(">");
				scanf_s("%d", &k);
				if (k == 1) {
					temporary_MI.membership_name[0] = 'x';
					temporary_MI.membership_number = 0;
					temporary_MI.membership_phonenum[0] = '0';
					temporary_MI.membership_socialnum[0] = '0';
					temporary_MI.Rental_Video_List[0] = '0';
					temporary_MI.rental_fee = 0;

					fsetpos(MIFp, &pos);
					fwrite(&temporary_MI, sizeof(temporary_MI), 1, MIFp);
					fclose(MIFp);
					printf("�����Ǿ����ϴ�.\n");
					break;
				}
				else if (k == 0) {
					printf("ȸ�������� �����˴ϴ�.\n");
					fclose(MIFp);
					break;
				}
				else {
					printf("�߸��� ��ȣ�� �Է��Ͽ����ϴ�\n");
					fclose(MIFp);
					return;
				}
			}
			else if ((feof(MIFp) == 0) && (strcmp(MI.membership_name, temporary_MI.membership_name) == 0)){
				printf("��ġ�ϴ� ȸ���� �����ϴ�.\n");
				break;
			}
		}
	}
	
	// Member id searching
	else if (d_n == 2) {
		system("cls");
		printf("ȸ�� ��ȣ�� �˻��Ͽ� �����մϴ�.\n");
		printf("ȸ�� ��ȣ�� �ߺ����� ������ �����ϴ��� �ٸ� ��ȣ�� �����˴ϴ�.\n\n");

		printf("[�����Ϸ��� ȸ�� ��ȣ�� �Է��ϼ���.]\n");
		printf("(ȸ�� ��ȣ�� �����Դϴ�.)\n");
		rewind(stdin);
		printf(">");
		scanf_s("%d", &temporary_MI.membership_number);

		while (feof(MIFp) == 0) {
			fpos_t pos;
			fgetpos(MIFp, &pos);
			fread(&MI, sizeof(MI), 1, MIFp);

			if (temporary_MI.membership_number == MI.membership_number) {
				printf("ȸ����ȣ [%d]�� ��ġ�ϴ� ȸ���� ã�ҽ��ϴ�.\n\n", temporary_MI.membership_number);
				printf("ȸ�� �̸� : %s", MI.membership_name);
				printf("ȸ�� ��ȣ : %d\n", MI.membership_number);
				printf("ȸ�� ��ȭ��ȣ : %s\n\n", MI.membership_phonenum);
				printf("�����Ϸ��� 1, �����Ϸ��� 0�� �Է��ϼ���.\n");
				int k = -1;
				printf(">");
				scanf_s("%d", &k);
				if (k == 1) {
					fsetpos(MIFp, &pos);
					temporary_MI.membership_name[0] = 'x';
					temporary_MI.membership_number = 0;
					temporary_MI.membership_phonenum[0] = '0';
					temporary_MI.membership_socialnum[0] = '0';
					for (int i = 0; i <= 22; i++) {
						temporary_MI.Rental_Video_List[i] = '0';
					}
					temporary_MI.rental_fee = 0;
					fwrite(&temporary_MI, sizeof(temporary_MI), 1, MIFp);
					fclose(MIFp);
					printf("�����Ǿ����ϴ�.\n");
					break;
				}
				else if (k == 0) {
					printf("ȸ�������� �����˴ϴ�.\n");
					fclose(MIFp);
					break;
				}
				else {
					printf("�߸��� ��ȣ�Դϴ�.\n");
					fclose(MIFp);
					return;
				}
			}
			else {
				printf("���� ȸ�� ��ȣ�Դϴ�.\n");
			}
		}

	}
	else {
		printf("�߸��� ���� �Է���.\n");
		fclose(MIFp);
		return;
	}
	fclose(MIFp);
	return;
}