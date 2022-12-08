void video_return() {
	rewind(stdin);
	system("cls");
	system("title 비디오 대여 프로그램 - 비디오 반납");
	FILE* MIFp;
	FILE* VIFp;
	fopen_s(&MIFp, "MSinfo.txt", "r+");

	struct membership_info MI;//회원정보 구조체 MI
	struct video_info VI;//비디오정보 구조체 VI
	char video_name[50];//비디오 구조체 멤버인 비디오이름과 동일한 크기
	int video_num = -1;//비디오 구조체 멤버인 비디오번호와 동일한 크기
	char member_name_search[20];//회원 구조체 멤버인 회원이름과 동일한 크기
	int member_num_search = -1;//회원구조체 멤버인 회원번호와 동일한 크기
	int i = -1;
	int k = -1;

	if (MIFp == 0) {
		printf("파일에 대한 오류가 발생하였습니다.\n");
		printf("메뉴로 돌아갑니다.\n");
		return;
	}

	memset(&MI, 0, sizeof(MI));
	memset(&VI, 0, sizeof(VI));
	memset(&video_name, 0, sizeof(video_name));

	fseek(MIFp, 0, SEEK_SET);

	printf("반납하려는 회원의 정보를 입력하세요.\n");
	printf("회원 이름으로 입력하려면 1을 입력하세요.\n");
	printf("회원 번호로 입력하려면 2를 입력하세요.\n");
	printf("메인화면으로 돌아가려면 0을 입력하세요.\n");
	printf(">");
	scanf_s("%d", &i);

	fpos_t pos_member;
	fpos_t pos_video;
	if (i == 1) {//회원 이름으로 저장 정보를 검색
		printf("==================================비디오 반납===================================\n");

		while (k != 0) {
			printf("\n비디오 반납을 멈추려면 0을 입력하세요.\n");
			printf("계속하려면 1을 입력하세요.\n");
			rewind(stdin);
			scanf_s("%d", &k);
			if (k == 0) {
				fclose(MIFp);
				break;
			}
			printf("[반납할 회원의 이름을 입력하세요.]\n");
			rewind(stdin);
			printf(">");
			fgets(member_name_search, sizeof(member_name_search), stdin);
			
			while (feof(MIFp) == 0) {
				fgetpos(MIFp, &pos_member);
				fread(&MI, sizeof(MI), 1, MIFp);
				if (strcmp(member_name_search, MI.membership_name) == 0) {
					printf("회원의 이름 [%s]을 찾았습니다.\n", member_name_search);
					printf("이름 : %s", MI.membership_name);
					printf("전화번호 : %s\n", MI.membership_phonenum);
					printf("생년월일 : %s\n", MI.membership_socialnum);
					printf("회원번호 : [%d]\n", MI.membership_number);
					printf("대여한 비디오 목록 :");
					if (MI.Rental_Video_List[0] == NULL) {
						printf("대여한 비디오가 없습니다.\n");
					}
					for (int i = 0; i < 30; i++) {
						tras_video(MI.Rental_Video_List[i]);
					}
					printf("이름이 중복되는 경우 회원번호를 이용하여 회원을 선택하십시오.\n");
					while (1) {

						fopen_s(&VIFp, "Vinfo.txt", "r+");
						fseek(VIFp, 0, SEEK_SET);

						printf("[반납하려는 비디오 번호를 입력하세요.]\n");
						scanf_s("%d", &video_num);
						for (int i = 0; i < 30; i++) {
							if (MI.Rental_Video_List[i] == video_num) {

								fclose(VIFp);
								tras_video(MI.Rental_Video_List[i]);

								printf("\n해당 비디오를 반납합니다.\n");
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
						printf("반납하려는 비디오가 없습니다.\n");
						fclose(VIFp);
						break;
					}

					fsetpos(MIFp, &pos_member);
					fwrite(&MI, sizeof(MI), 1, MIFp);
					
					break;
				}
				else if ((strcmp(VI.video_name, video_name) != 0)) {
					printf("저장된 비디오 중 해당 이름의 비디오가 없습니다.\n");
					printf("비디오 이름을 확인하고 다시 반납하거나 비디오 번호로 반납하세요.\n");
					break;
				}
			}
		}
		fclose(MIFp);
		return;
	}
	if (i == 2) {
		printf("==================================비디오 반납===================================\n");
		rewind(stdin);
		int j = -1;
		printf("[반납할 회원의 회원번호를 입력하세요.]\n");
		scanf_s("%d", &j);
		while (feof(MIFp) == 0) {
			fgetpos(MIFp, &pos_member);
			fread(&MI, sizeof(MI), 1, MIFp);
			if ((MI.membership_number == j)) {
				printf("회원번호 [%d]를 가진 회원을 찾았습니다.\n", j);
				printf("이름 : %s", MI.membership_name);
				printf("전화번호 : %s\n", MI.membership_phonenum);
				printf("생년월일 : %s\n", MI.membership_socialnum);
				printf("회원번호 : [%d]\n", MI.membership_number);
				printf("대여한 비디오 목록 :");
				for (int i = 0; i < 30; i++) {
					tras_video(MI.Rental_Video_List[i]);
				}
				while (1) {
					fopen_s(&VIFp, "Vinfo.txt", "r+");
					fseek(VIFp, 0, SEEK_SET);
					printf("[반납하려는 비디오 번호를 입력하세요.]\n");
					scanf_s("%d", &video_num);
					for (int i = 0; i < 30; i++) {
						if (MI.Rental_Video_List[i] == video_num) {

							fclose(VIFp);
							tras_video(MI.Rental_Video_List[i]);

							printf("\n해당 비디오를 반납합니다.\n");
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
					printf("반납하려는 비디오가 없습니다.\n");
					fclose(VIFp);
					break;
				}

				fsetpos(MIFp, &pos_member);
				fwrite(&MI, sizeof(MI), 1, MIFp);

				break;
			}
			else if ((strcmp(VI.video_name, video_name) != 0)) {
				printf("저장된 비디오 중 해당 이름의 비디오가 없습니다.\n");
				printf("비디오 이름을 확인하고 다시 반납하거나 비디오 번호로 반납하세요.\n");
				break;
			}
		}
	}
	fclose(MIFp);
	return;
}