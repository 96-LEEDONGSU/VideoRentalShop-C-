void video_print() {
	system("title 비디오 대여 프로그램 - 비디오 출력");
	system("cls");
	printf("===============================저장 비디오 출력=================================\n");
	printf("저장된 모든 비디오를 출력합니다.\n");
	FILE* VIFp;
	fopen_s(&VIFp, "Vinfo.txt", "r+");

	struct video_info VI;
	memset(&VI, NULL, sizeof(VI));


	if (VIFp == NULL) {
		printf("파일에 대한 오류가 발생하였습니다.\n");
		printf("메뉴로 돌아갑니다.\n");
		return;
	}

	while (feof(VIFp) == 0) {
		fread(&VI, sizeof(VI), 1, VIFp);
		if (feof(VIFp) != 0) {//파일에 끝에 도달하여도 while문 실행되므로 종료하도록 함.
			break;
		}
		printf("비디오 이름 : %s", VI.video_name);
		printf("비디오 번호 : [%d]\n", VI.video_num);
		printf("비디오 제작사 : %s", VI.video_production_company);
		printf("비디오 대여가격 : %d\n", VI.video_rental_fee);
		printf("비디오 장르 : ");
		for (int L = 0; L <= 22; L++) {
			genre_translation(VI.video_genre[L]); //장르번호를 장르명으로 변환
		}
		printf("\n비디오 갯수 : %d\n", VI.same_video_num);
		printf("\n\n");
	}
	fclose(VIFp);
}

void member_print() {
	system("title 비디오 대여 프로그램 - 회원 출력");
	system("cls");
	printf("================================저장 회원 출력==================================\n");
	printf("저장된 모든 회원을 출력합니다.\n");
	FILE* MIFp;
	struct membership_info MI;
	memset(&MI, NULL, sizeof(MI));
	fopen_s(&MIFp, "MSinfo.txt", "r+");

	if (MIFp == NULL) {
		printf("파일에 대한 오류가 발생하였습니다.\n");
		printf("메뉴로 돌아갑니다.\n");
		return;
	}

	if (feof(MIFp) == 0) {
		while (feof(MIFp) == 0) {
			fread(&MI, sizeof(MI), 1, MIFp);
			if (feof(MIFp) != 0) {//파일에 끝에 도달하여도 while문이 실행되므로 종료하도록 함.
				break;
			}
			printf("회원 이름 : %s", MI.membership_name);
			printf("회원 번호 : %d\n", MI.membership_number);
			printf("회원 전화번호 : %s\n", MI.membership_phonenum);
			printf("회원 생년월일 : %s\n", MI.membership_socialnum);
			printf("회원이 대여한 비디오 목록 : ");
			if (MI.Rental_Video_List[0] == NULL)
				printf("없음\n");
			for (int i = 0; i < 30; i++) {
				tras_video(MI.Rental_Video_List[i]);
			}
			printf("\n\n");
		}
	}
	fclose(MIFp);
}