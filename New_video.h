void genre();
void genre_translation(int);

void new_video() {
	system("title ���� �뿩 ���α׷� - ���� ���");
	FILE* VIFp;//Video Information File
	fopen_s(&VIFp, "Vinfo.txt", "a+");//������ ���� ��� �����ϱ� ���Ͽ� ���
	/*
	* "a+"���� ���� �ٷ� ���� ������ ���� ����� ������ ���� ��쿡
	* ����ڰ� ���� ������ ���ɼ��� �ſ� �ٺ��ϹǷ� ������ ���� ��� ������
	* �����ϰ� �� �� �����ϵ��� "a+"���� ���� �ٷ� �ݾ���.
	*/
	fclose(VIFp);

	fopen_s(&VIFp, "Vinfo.txt", "r+");//���� ������ ���� ������ ����.
	/*"r+"���� ����� �ش� ���� ������ ��� �����ϸ� ��ġ�����ڸ� �̵���Ű�� ���Ͽ� 
	+��� ���.*/
	fseek(VIFp, 0, SEEK_SET);

	if (VIFp == NULL) {
		printf("���Ͽ� ���� ������ �߻��Ͽ����ϴ�.\n");
		printf("�޴��� ���ư��ϴ�.\n");
		return;
	}

	struct video_info VI;
	struct video_info temporary_VI;
	memset(&VI, NULL, sizeof(VI));
	memset(&temporary_VI, NULL, sizeof(temporary_VI));

	printf("===============================�ű� ���� ���================================\n");

	printf("[���� �̸��� �Է��ϼ���.]\n");
	printf("(���� �̸��� 49���̳��� �ۼ��ϼ���.)\n");
	rewind(stdin);
	fgets(VI.video_name, sizeof(VI.video_name), stdin);

	while ((VI.video_name[0] == 10) || (VI.video_name[0] == 0)) {
		printf("�ں��� �̸��� �ʼ� �Է� �����Դϴ�.\n");
		printf("[���� �̸��� �Է��ϼ���.]");
		rewind(stdin);
		fgets(VI.video_name, sizeof(VI.video_name), stdin);
	}

	rewind(stdin);
	char temporary_char[2];//Y/N�� �޾ƾ��ϹǷ� �ӽú���
	while (feof(VIFp) == 0) {

		fpos_t pos;
		fgetpos(VIFp, &pos);
		fread(&temporary_VI, sizeof(temporary_VI), 1, VIFp);

		if (strcmp(VI.video_name, temporary_VI.video_name) == 0) {
			printf("===============================================================================\n");
			printf("���� �̸��� ���� [%s]�� �ֽ��ϴ�.\n", VI.video_name);
			printf("[�����Ͻðڽ��ϱ�?](Y/N)\n");
			printf(">");
			rewind(stdin);
			fgets(temporary_char, sizeof(temporary_char), stdin);
			if ((strcmp(temporary_char, "Y") == 0)||(strcmp(temporary_char, "y"))) {
				printf("���� �̸��� ������ �����մϴ�.\n");
				temporary_VI.same_video_num = temporary_VI.same_video_num + 1;//���� ���� ���� 1 ����
				fsetpos(VIFp, &pos);
				fwrite(&temporary_VI, sizeof(temporary_VI), 1, VIFp);
				fclose(VIFp);
				return;
			}
			if ((strcmp(temporary_char, "N") == 0)||((strcmp(temporary_char, "n") == 0))) {
				printf("���� ����� �����մϴ�\n");
				fclose(VIFp);
				return;
			}
		}
		else if ( (feof(VIFp) != 0) && (strcmp(VI.video_name, temporary_VI.video_name) == 0) ){
			printf("���� �̸��� ������ �����ϴ�.\n");
			printf("��� �����մϴ�.\n");
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
		printf("=============================�ű� ���� �帣 ���=============================\n");
		genre();//�帣 �޴��� ����ϴ� �Լ� [New_video.h�� ��ġ�� �Լ�]
		printf("[���ϴ� �帣 ��ȣ�� �Է��ϼ���.]\n");
		printf("(0���� �Է��ϸ� �����մϴ�.)\n");
		rewind(stdin);
		printf(">");
		scanf_s("%d", &i);
		VI.video_genre[k] = i;
		if (i == 0)
			break;																						
	}

	//printf("===============================================================================\n");//UI�� �����ؼ� ����Ͻÿ�

	system("cls");
	printf("===========================�ű� ���� ���ۻ� ���=============================\n");
	printf("[������ ���ۻ縦 �Է��ϼ���.]\n");
	printf("(������ ���ۻ�� 49���̳��� �ۼ��ϼ���.)\n");
	rewind(stdin);
	printf(">");
	fgets(VI.video_production_company, sizeof(VI.video_production_company), stdin);

	if ((VI.video_production_company[0] == 10) || (VI.video_production_company[0] == 0)) {
		printf("���� ���ۻ縦 �Է����� �ʾҽ��ϴ�.\n");
		printf("���� ���ۻ�� �ʼ� �Է� ������ �ƴմϴ�.\n");
	}

	system("cls");
	printf("===========================�ű� ���� �뿩���� ���===========================\n");
	printf("[������ �뿩������ �Է��ϼ���.]\n");
	printf("(������ �뿩������ 21����� ���� �� �����ϴ�.)\n");
	rewind(stdin);
	printf(">");
	scanf_s("%d", &VI.video_rental_fee);

	if ((VI.video_rental_fee <= 0) || VI.video_rental_fee >= 2100000000 ) {
		printf("���� �뿩������ �ʼ� �Է� �����Դϴ�.\n");
		printf("[���� �뿩������ �Է��ϼ���.]\n");
		rewind(stdin);
		printf(">");
		scanf_s("%d", &VI.video_rental_fee);
	}

	int VN = 0;//���� ��ȣ�� �����ϴ� ����
	struct video_info VI_vn;
	memset(&VI_vn, NULL, sizeof(VI_vn));
	fseek(VIFp, 0, SEEK_SET);//������ ó������ �б�����
	while (feof(VIFp) == 0) {//������ ������ �д� ���� while�� ����
		fread(&VI_vn, sizeof(VI_vn), 1, VIFp);//VIũ��� VIFp�� �о�
		///printf("ȸ����ȣ �����б� while�� �����׽�Ʈ��\n");
		if (VI_vn.video_num >= 0) {
			VN++;
			//printf("if�� �����׽�Ʈ�� %d\n", VN);
		}
	}
	VI.video_num = VN;
	VI.same_video_num = VI.same_video_num++;

	system("cls");

	printf("===========================�ű� ���� ��� ����================================\n");
	printf("���� ��ȣ : [%d]\n", VI.video_num);
	printf("���� �̸� : %s", VI.video_name);
	printf("���� �帣 : ");
	for (int L = 0; L <= 22; L++) {
		genre_translation(VI.video_genre[L]); //�帣��ȣ�� �帣������ ��ȯ[New_video.h�� ��ġ�� �Լ�]
	}
	printf("\n���� �뿩���� : %d ��\n", VI.video_rental_fee);
	printf("���� ���ۻ� : %s", VI.video_production_company);
	printf("�뿩 ������ ���� ���� : %d\n", VI.same_video_num);

	int k=-1;
	printf("[�̴�� �Է��Ϸ��� 1�� �Է��ϰ�, �ٽ� �Է��Ϸ��� 0�� �Է��ϼ���.]\n");
	printf(">");
	scanf_s("%d", &k);
	if(k == 1){
		fwrite(&VI, sizeof(VI), 1, VIFp);//MI����ü ���Ͽ� ����
		fclose(VIFp);
		printf("\n");
	}
	else if(k == 0){
		fclose(VIFp);
		printf("\n");
	}
	else {
		printf("���ƽ��ϱ� �޸�?\n");
		printf("1�� �Ŀ� ���Ͽ� �ۼ��մϴ�.\n");
		Sleep(1000);
		fwrite(&VI, sizeof(VI), 1, VIFp);
		fclose(VIFp);
	}
}

void genre() {
	printf("������ �帣�� �����ϼ���\n");
	printf("1. �׼�\n");
	printf("2. �ڹ̵�\n");
	printf("3. ����\n");
	printf("4. ��ť\n");
	printf("5. ���\n");
	printf("6. ����\n");
	printf("7. ����/������\n");
	printf("8. �θǽ�/���\n");
	printf("9. �������\n");
	printf("10. �̽��͸�/�����潺\n");
	printf("11. ������\n");
	printf("12. �ִϸ��̼�\n");
	printf("13. ����\n");
	printf("14. ����\n");
	printf("15. ����\n");
	printf("16. �ε�\n");
	printf("17. �ѱ�\n");
	printf("18. �Ϻ�\n");
	printf("19. �̱�\n");
	printf("20. �ܱ�\n");
	printf("21. ����\n");
	printf("22. ��Ÿ\n");
}

void genre_translation(int i) {
	if (i == 1) {
		printf(" [�׼�] ");
		return;
	}
	else if (i == 2) {
		printf(" [�ڹ̵�] ");
		return;
	}
	else if (i == 3) {
		printf(" [����] ");
		return;
	}
	else if (i == 4) {
		printf(" [��ť] ");
		return;
	}
	else if (i == 5) {
		printf(" [���] ");
		return;
	}
	else if (i == 6) {
		printf(" [����] ");
		return;
	}
	else if (i == 7) {
		printf(" [����/������] ");
		return;
	}
	else if (i == 8) {
		printf(" [�θǽ�/���] ");
		return;
	}
	else if (i == 9) {
		printf(" [�������] ");
		return;
	}
	else if (i == 10) {
		printf(" [�̽��͸�/�����潺] ");
		return;
	}
	else if (i == 11) {
		printf(" [������] ");
		return;
	}
	else if (i == 12) {
		printf(" [�ִϸ��̼�] ");
		return;
	}
	else if (i == 13) {
		printf(" [����] ");
		return;
	}
	else if (i == 14) {
		printf(" [����] ");
		return;
	}
	else if (i == 15) {
		printf(" [����] ");
		return;
	}
	else if (i == 16) {
		printf(" [�ε�] ");
		return;
	}
	else if (i == 17) {
		printf(" [�ѱ�] ");
		return;
	}
	else if (i == 18) {
		printf(" [�Ϻ�] ");
		return;
	}
	else if (i == 19) {
		printf(" [�̱�] ");
		return;
	}
	else if (i == 20) {
		printf(" [�ܱ�] ");
		return;
	}
	else if (i == 21) {
		printf(" [����] ");
		return;
	}
	else if (i == 22) {
		printf(" [��Ÿ] ");
		return;
	}
	else if ((i>22)||(i<0)){
		printf("�߸��� ���� �Է��Ͽ����ϴ�.\n");
		return;
	}
}