void tras_video(int video_num) {//���� ��ȣ�� ������ �̸����� ������ִ� �Լ�
	FILE* VIF;
	fopen_s(&VIF, "Vinfo.txt", "r");
	struct video_info VI;

	if (VIF == 0) {
		printf("���Ͽ� ���� ������ �߻��Ͽ����ϴ�.\n");
		printf("�޴��� ���ư��ϴ�.\n");
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