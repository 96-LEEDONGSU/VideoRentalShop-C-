void genre();
void genre_translation(int);

void new_video() {
	system("title 비디오 대여 프로그램 - 비디오 등록");
	FILE* VIFp;//Video Information File
	fopen_s(&VIFp, "Vinfo.txt", "a+");//파일이 없는 경우 생성하기 위하여 사용
	/*
	* "a+"모드로 열고 바로 닫은 이유는 비디오 등록을 파일이 없는 경우에
	* 사용자가 먼저 실행할 가능성이 매우 다분하므로 파일이 없는 경우 파일을
	* 생성하고 그 후 진행하도록 "a+"모드로 열고 바로 닫아줌.
	*/
	fclose(VIFp);

	fopen_s(&VIFp, "Vinfo.txt", "r+");//비디오 정보를 담은 파일을 열기.
	/*"r+"모드로 열어야 해당 비디오 정보를 등록 가능하며 위치지시자를 이동시키기 위하여 
	+모드 사용.*/
	fseek(VIFp, 0, SEEK_SET);

	if (VIFp == NULL) {
		printf("파일에 대한 오류가 발생하였습니다.\n");
		printf("메뉴로 돌아갑니다.\n");
		return;
	}

	struct video_info VI;
	struct video_info temporary_VI;
	memset(&VI, NULL, sizeof(VI));
	memset(&temporary_VI, NULL, sizeof(temporary_VI));

	printf("===============================신규 비디오 등록================================\n");

	printf("[비디오 이름을 입력하세요.]\n");
	printf("(비디오 이름은 49자이내로 작성하세요.)\n");
	rewind(stdin);
	fgets(VI.video_name, sizeof(VI.video_name), stdin);

	while ((VI.video_name[0] == 10) || (VI.video_name[0] == 0)) {
		printf("★비디오 이름은 필수 입력 사항입니다.\n");
		printf("[비디오 이름을 입력하세요.]");
		rewind(stdin);
		fgets(VI.video_name, sizeof(VI.video_name), stdin);
	}

	rewind(stdin);
	char temporary_char[2];//Y/N를 받아야하므로 임시변수
	while (feof(VIFp) == 0) {

		fpos_t pos;
		fgetpos(VIFp, &pos);
		fread(&temporary_VI, sizeof(temporary_VI), 1, VIFp);

		if (strcmp(VI.video_name, temporary_VI.video_name) == 0) {
			printf("===============================================================================\n");
			printf("같은 이름의 비디오 [%s]가 있습니다.\n", VI.video_name);
			printf("[저장하시겠습니까?](Y/N)\n");
			printf(">");
			rewind(stdin);
			fgets(temporary_char, sizeof(temporary_char), stdin);
			if ((strcmp(temporary_char, "Y") == 0)||(strcmp(temporary_char, "y"))) {
				printf("같은 이름의 비디오로 저장합니다.\n");
				temporary_VI.same_video_num = temporary_VI.same_video_num + 1;//같은 비디오 개수 1 증가
				fsetpos(VIFp, &pos);
				fwrite(&temporary_VI, sizeof(temporary_VI), 1, VIFp);
				fclose(VIFp);
				return;
			}
			if ((strcmp(temporary_char, "N") == 0)||((strcmp(temporary_char, "n") == 0))) {
				printf("비디오 등록을 종료합니다\n");
				fclose(VIFp);
				return;
			}
		}
		else if ( (feof(VIFp) != 0) && (strcmp(VI.video_name, temporary_VI.video_name) == 0) ){
			printf("같은 이름의 비디오가 없습니다.\n");
			printf("계속 진행합니다.\n");
			break;
		}
	}

	rewind(stdin);
	
	system("cls");
	//printf("===============================================================================\n");
	int i = -1;
	for (int k = 0; k <= 22; k++) {
		if(k >= 1)
			printf("%d", VI.video_genre[k]);
		system("cls");
		printf("=============================신규 비디오 장르 등록=============================\n");
		genre();//장르 메뉴를 출력하는 함수 [New_video.h에 위치한 함수]
		printf("[원하는 장르 번호를 입력하세요.]\n");
		printf("(0번을 입력하면 종료합니다.)\n");
		rewind(stdin);
		printf(">");
		scanf_s("%d", &i);
		VI.video_genre[k] = i;
		if (i == 0)
			break;																						
	}

	//printf("===============================================================================\n");//UI용 복사해서 사용하시오

	system("cls");
	printf("===========================신규 비디오 제작사 등록=============================\n");
	printf("[비디오의 제작사를 입력하세요.]\n");
	printf("(비디오의 제작사는 49자이내로 작성하세요.)\n");
	rewind(stdin);
	printf(">");
	fgets(VI.video_production_company, sizeof(VI.video_production_company), stdin);

	if ((VI.video_production_company[0] == 10) || (VI.video_production_company[0] == 0)) {
		printf("비디오 제작사를 입력하지 않았습니다.\n");
		printf("비디오 제작사는 필수 입력 사항이 아닙니다.\n");
	}

	system("cls");
	printf("===========================신규 비디오 대여가격 등록===========================\n");
	printf("[비디오의 대여가격을 입력하세요.]\n");
	printf("(비디오의 대여가격은 21억원을 넘을 수 없습니다.)\n");
	rewind(stdin);
	printf(">");
	scanf_s("%d", &VI.video_rental_fee);

	if ((VI.video_rental_fee <= 0) || VI.video_rental_fee >= 2100000000 ) {
		printf("비디오 대여가격은 필수 입력 사항입니다.\n");
		printf("[비디오 대여가격을 입력하세요.]\n");
		rewind(stdin);
		printf(">");
		scanf_s("%d", &VI.video_rental_fee);
	}

	int VN = 0;//비디오 번호를 저장하는 변수
	struct video_info VI_vn;
	memset(&VI_vn, NULL, sizeof(VI_vn));
	fseek(VIFp, 0, SEEK_SET);//파일을 처음부터 읽기위함
	while (feof(VIFp) == 0) {//파일을 끝까지 읽는 동안 while문 실행
		fread(&VI_vn, sizeof(VI_vn), 1, VIFp);//VI크기로 VIFp를 읽어
		///printf("회원번호 파일읽기 while문 실행테스트문\n");
		if (VI_vn.video_num >= 0) {
			VN++;
			//printf("if문 실행테스트문 %d\n", VN);
		}
	}
	VI.video_num = VN;
	VI.same_video_num = VI.same_video_num++;

	system("cls");

	printf("===========================신규 비디오 등록 정보================================\n");
	printf("비디오 번호 : [%d]\n", VI.video_num);
	printf("비디오 이름 : %s", VI.video_name);
	printf("비디오 장르 : ");
	for (int L = 0; L <= 22; L++) {
		genre_translation(VI.video_genre[L]); //장르번호를 장르명으로 변환[New_video.h에 위치한 함수]
	}
	printf("\n비디오 대여가격 : %d 원\n", VI.video_rental_fee);
	printf("비디오 제작사 : %s", VI.video_production_company);
	printf("대여 가능한 비디오 갯수 : %d\n", VI.same_video_num);

	int k=-1;
	printf("[이대로 입력하려면 1을 입력하고, 다시 입력하려면 0을 입력하세요.]\n");
	printf(">");
	scanf_s("%d", &k);
	if(k == 1){
		fwrite(&VI, sizeof(VI), 1, VIFp);//MI구조체 파일에 쓰기
		fclose(VIFp);
		printf("\n");
	}
	else if(k == 0){
		fclose(VIFp);
		printf("\n");
	}
	else {
		printf("미쳤습니까 휴먼?\n");
		printf("1초 후에 파일에 작성합니다.\n");
		Sleep(1000);
		fwrite(&VI, sizeof(VI), 1, VIFp);
		fclose(VIFp);
	}
}

void genre() {
	printf("비디오의 장르를 선택하세요\n");
	printf("1. 액션\n");
	printf("2. 코미디\n");
	printf("3. 범죄\n");
	printf("4. 다큐\n");
	printf("5. 드라마\n");
	printf("6. 공포\n");
	printf("7. 음악/뮤지컬\n");
	printf("8. 로맨스/멜로\n");
	printf("9. 공상과학\n");
	printf("10. 미스터리/서스펜스\n");
	printf("11. 스릴러\n");
	printf("12. 애니메이션\n");
	printf("13. 가족\n");
	printf("14. 역사\n");
	printf("15. 고전\n");
	printf("16. 인디\n");
	printf("17. 한국\n");
	printf("18. 일본\n");
	printf("19. 미국\n");
	printf("20. 외국\n");
	printf("21. 에로\n");
	printf("22. 기타\n");
}

void genre_translation(int i) {
	if (i == 1) {
		printf(" [액션] ");
		return;
	}
	else if (i == 2) {
		printf(" [코미디] ");
		return;
	}
	else if (i == 3) {
		printf(" [범죄] ");
		return;
	}
	else if (i == 4) {
		printf(" [다큐] ");
		return;
	}
	else if (i == 5) {
		printf(" [드라마] ");
		return;
	}
	else if (i == 6) {
		printf(" [공포] ");
		return;
	}
	else if (i == 7) {
		printf(" [음악/뮤지컬] ");
		return;
	}
	else if (i == 8) {
		printf(" [로맨스/멜로] ");
		return;
	}
	else if (i == 9) {
		printf(" [공상과학] ");
		return;
	}
	else if (i == 10) {
		printf(" [미스터리/서스펜스] ");
		return;
	}
	else if (i == 11) {
		printf(" [스릴러] ");
		return;
	}
	else if (i == 12) {
		printf(" [애니메이션] ");
		return;
	}
	else if (i == 13) {
		printf(" [가족] ");
		return;
	}
	else if (i == 14) {
		printf(" [역사] ");
		return;
	}
	else if (i == 15) {
		printf(" [고전] ");
		return;
	}
	else if (i == 16) {
		printf(" [인디] ");
		return;
	}
	else if (i == 17) {
		printf(" [한국] ");
		return;
	}
	else if (i == 18) {
		printf(" [일본] ");
		return;
	}
	else if (i == 19) {
		printf(" [미국] ");
		return;
	}
	else if (i == 20) {
		printf(" [외국] ");
		return;
	}
	else if (i == 21) {
		printf(" [에로] ");
		return;
	}
	else if (i == 22) {
		printf(" [기타] ");
		return;
	}
	else if ((i>22)||(i<0)){
		printf("잘못된 값을 입력하였습니다.\n");
		return;
	}
}