void tras_video(int video_num) {//비디오 번호를 받으면 이름으로 출력해주는 함수
	FILE* VIF;
	fopen_s(&VIF, "Vinfo.txt", "r");
	struct video_info VI;

	if (VIF == 0) {
		printf("파일에 대한 오류가 발생하였습니다.\n");
		printf("메뉴로 돌아갑니다.\n");
		return;
	}

	memset(&VI, 0, sizeof(VI));
	fseek(VIF, 0, SEEK_SET);

	while (feof(VIF) == 0){
		fread(&VI, sizeof(VI), 1, VIF);
		if (VI.video_num == video_num) {
			printf("[%d]", VI.video_num);
			printf(" %s ", VI.video_name);
		}
	}
	fclose(VIF);
}