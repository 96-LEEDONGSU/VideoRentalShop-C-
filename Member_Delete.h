// Delete member function
void delete_member() {
	system("title 비디오 대여 프로그램 - 회원 삭제");
	FILE* MIFp;
	fopen_s(&MIFp, "MSinfo.txt", "r+");

	if (MIFp == NULL) {
		printf("파일에 대한 오류가 발생하였습니다.\n");
		printf("메뉴로 돌아갑니다.\n");
		return;
	}
	fseek(MIFp, 0, SEEK_SET);

	struct membership_info MI;
	memset(&MI, NULL, sizeof(MI));
	struct membership_info temporary_MI;
	memset(&temporary_MI, NULL, sizeof(temporary_MI));


	printf("===============================기존 회원 삭제=================================\n");

	printf("삭제하려는 회원을 선택하여야 합니다.\n");
	int d_n = -1;
	printf("1. 회원 이름\n");
	printf("2. 회원 번호\n");
	printf(">");
	scanf_s("%d", &d_n);

	// member name searching
	if (d_n == 1) {
		system("cls");
		printf("회원의 이름을 검색하여 삭제합니다.\n");
		printf("중복되는 경우 회원번호를 선택하여 삭제합니다.\n\n");

		printf("[삭제하려는 회원의 이름을 입력하세요.]\n");
		printf("(회원의 이름은 19자 이내로 작성하세요.)\n");
		rewind(stdin);
		printf(">");
		fgets(temporary_MI.membership_name, sizeof(temporary_MI.membership_name), stdin);

		while (feof(MIFp) == 0) 
		{
			fpos_t pos;
			fgetpos(MIFp, &pos);
			fread(&MI, sizeof(MI), 1, MIFp);

			if (strcmp(MI.membership_name, temporary_MI.membership_name) == 0) {
				printf("일치하는 회원을 찾았습니다.\n");
				printf("회원 이름 : %s", MI.membership_name);
				printf("회원 번호 : %d\n", MI.membership_number);
				printf("회원 전화번호 : %s\n\n", MI.membership_phonenum);
				printf("삭제하려면 1, 유지하려면 0을 입력하세요.\n");
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
					printf("삭제되었습니다.\n");
					break;
				}
				else if (k == 0) {
					printf("회원정보가 유지됩니다.\n");
					fclose(MIFp);
					break;
				}
				else {
					printf("잘못된 번호를 입력하였습니다\n");
					fclose(MIFp);
					return;
				}
			}
			else if ((feof(MIFp) == 0) && (strcmp(MI.membership_name, temporary_MI.membership_name) == 0)){
				printf("일치하는 회원이 없습니다.\n");
				break;
			}
		}
	}
	
	// Member id searching
	else if (d_n == 2) {
		system("cls");
		printf("회원 번호를 검색하여 삭제합니다.\n");
		printf("회원 번호는 중복되지 않으며 삭제하더라도 다른 번호는 유지됩니다.\n\n");

		printf("[삭제하려는 회원 번호를 입력하세요.]\n");
		printf("(회원 번호는 숫자입니다.)\n");
		rewind(stdin);
		printf(">");
		scanf_s("%d", &temporary_MI.membership_number);

		while (feof(MIFp) == 0) {
			fpos_t pos;
			fgetpos(MIFp, &pos);
			fread(&MI, sizeof(MI), 1, MIFp);

			if (temporary_MI.membership_number == MI.membership_number) {
				printf("회원번호 [%d]와 일치하는 회원을 찾았습니다.\n\n", temporary_MI.membership_number);
				printf("회원 이름 : %s", MI.membership_name);
				printf("회원 번호 : %d\n", MI.membership_number);
				printf("회원 전화번호 : %s\n\n", MI.membership_phonenum);
				printf("삭제하려면 1, 유지하려면 0을 입력하세요.\n");
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
					printf("삭제되었습니다.\n");
					break;
				}
				else if (k == 0) {
					printf("회원정보가 유지됩니다.\n");
					fclose(MIFp);
					break;
				}
				else {
					printf("잘못된 번호입니다.\n");
					fclose(MIFp);
					return;
				}
			}
			else {
				printf("없는 회원 번호입니다.\n");
			}
		}

	}
	else {
		printf("잘못된 값을 입력함.\n");
		fclose(MIFp);
		return;
	}
	fclose(MIFp);
	return;
}