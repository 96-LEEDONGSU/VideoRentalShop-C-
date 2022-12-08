#include <stdio.h>
#include <windows.h>

void rental_video() {
	rewind(stdin);
	system("cls");//화면 초기화
	system("title 비디오 대여 프로그램 - 비디오 대여");
	FILE* MIFp;
	fopen_s(&MIFp, "MSinfo.txt", "r+");
	FILE* VIFp;
	fopen_s(&VIFp, "Vinfo.txt", "r+");

	struct membership_info MI;//회원정보 구조체 MI
	struct video_info VI;//비디오정보 구조체 VI
	char member_name_search[20];//회원 구조체 멤버인 회원이름과 동일한 크기
	int member_num_search = -1;//회원구조체 멤버인 회원번호와 동일한 크기
	char video_name[50];//비디오 구조체 멤버인 비디오이름과 동일한 크기
	int video_num = -1;//비디오 구조체 멤버인 비디오번호와 동일한 크기
	int i = -1;//회원이름과 번호 검색 변수
	fpos_t pos_member;
	fpos_t pos_video;


	if (MIFp == 0 || VIFp == 0) {
		printf("파일에 대한 오류가 발생하였습니다.\n");
		printf("메뉴로 돌아갑니다.\n");
		return;
	}

	memset(&MI, 0, sizeof(MI));
	memset(&VI, 0, sizeof(VI));
	memset(&video_name, 0, sizeof(video_name));
	memset(&member_name_search, 0, sizeof(member_name_search));//회원이름 찾기를 초기화
	fseek(MIFp, 0, SEEK_SET);

	//char* FINDp = NULL;
	printf("[회원의 이름으로 검색하려면 1을 입력하세요.]\n");
	printf("[회원번호로 검색하려면 2를 입력하세요.]\n");
	printf("회원의 선택은 번호로만 가능합니다.\n");
	printf(">");
	scanf_s("%d", &i);

		if(i == 1) {
			fseek(MIFp, 0, SEEK_SET);
			printf("==================================비디오 대여===================================\n");
			printf("[대여할 회원의 이름을 입력하세요.]\n");

			rewind(stdin);
			rewind(stdout);

			printf(">");
			fgets(member_name_search, sizeof(member_name_search), stdin);

			while (feof(MIFp) == 0) {
				fgetpos(MIFp, &pos_member);
				fread(&MI, sizeof(MI), 1, MIFp);
				if (strcmp(MI.membership_name, member_name_search) == 0) {
					printf("회원의 이름 %s을 찾았습니다.\n", member_name_search);
					printf("이름 : %s", MI.membership_name);
					printf("전화번호 : %s\n", MI.membership_phonenum);
					printf("생년월일 : %s\n", MI.membership_socialnum);
					printf("회원번호 : [%d]\n", MI.membership_number);

					printf("이름이 중복되는 경우 회원번호를 이용하여 회원을 선택하십시오.\n");
					break;
				}
				else if ((feof(MIFp) != 0) && (MI.membership_number != member_num_search)) {
					printf("이름을 찾지 못했습니다.\n");
					video_num = 0;
					fclose(MIFp);
					fclose(VIFp);

					return;
				}
			}
			rewind(stdin);
		}

		else if(i == 2) {
			printf("==================================비디오 대여===================================\n");

			printf("[대여할 회원의 번호를 입력하세요.]\n");

			rewind(stdin);

			printf(">");
			scanf_s("%d", &member_num_search);

			while (feof(MIFp) == 0) {
				fgetpos(MIFp, &pos_member);
				fread(&MI, sizeof(MI), 1, MIFp);
				if ((MI.membership_number) == (member_num_search)) {
					printf("회원번호 [%d]와 일치하는 회원을 찾았습니다.\n", MI.membership_number);

					printf("이름 : %s", MI.membership_name);
					printf("전화번호 : %s\n", MI.membership_phonenum);
					printf("생년월일 : %s\n", MI.membership_socialnum);
					printf("주의 <생년월일을 확인하고 비디오를 대여하십시오.>\n");
					break;//회원번호는 중복될 수 없으므로 파일 끝까지 확인할 필요가 없음. 
				}
				else if ((feof(MIFp) != 0) && (MI.membership_number != member_num_search)){
					printf("일치하는 회원번호가 없습니다.\n");
					fclose(MIFp);
					fclose(VIFp);
					return;
				}
			}
		}
		else {
			printf("잘못된 번호를 선택하였습니다.\n");
			printf("대여하려면 회원을 선택하여야 합니다.\n");
		}
	rewind(stdin);

	int k = 0;
	while (video_num != 0) {
		printf("\n\n비디오 대여를 멈추려면 0을 입력하세요.\n");
		printf("해당 회원 [%d]의 대여가 진행됩니다.\n", MI.membership_number);
		printf("[대여하려는 비디오의 번호를 입력하세요.]\n");
		rewind(stdin);
		printf(">");
		scanf_s("%d", &video_num);

		fseek(VIFp, 0, SEEK_SET);
		while (feof(VIFp) == 0) {
			fgetpos(VIFp, &pos_video);
			fread(&VI, sizeof(VI), 1, VIFp);
			if (VI.same_video_num > 0) {
				if (k >= 29) {
					printf("해당 비디오의 재고가 없습니다.\n");
					printf("대여를 종료합니다.\n");
					break;
				}
				MI.Rental_Video_List[k] = video_num;
				MI.rental_fee = VI.video_rental_fee + MI.rental_fee;
				printf("비디오 이름 : %s", VI.video_name);
				printf("비디오 제작사 : %s", VI.video_production_company);
				printf("비디오 대여가격 : %d\n", VI.video_rental_fee);
				printf("비디오 장르 : ");
				for (int L = 0; L <= 22; L++) {
					genre_translation(VI.video_genre[L]); //장르번호를 장르명으로 변환
				}
				printf("비디오 번호 : [%d]\n", VI.video_num);
				printf("해당 비디오를 대여합니다.\n");
				VI.same_video_num = VI.same_video_num - 1;
				fsetpos(MIFp, &pos_member);
				fwrite(&MI, sizeof(MI), 1, MIFp);
				fsetpos(VIFp, &pos_video);
				fwrite(&VI, sizeof(VI), 1, VIFp);
				k++;
				break;
			}
			else if ((video_num != VI.video_num)&&(feof(VIFp) != 0)) {
				printf("찾으려는 비디오가 없습니다.\n");
				printf("계속 대여를 진행합니다.\n");
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