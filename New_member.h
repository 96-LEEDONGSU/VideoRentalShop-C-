#include <stdio.h>
#include <windows.h>
#include "Member_info_struct.h"//회원정보 구조체

void new_member() {
	system("title 비디오 대여 프로그램 - 회원 등록");
	FILE* MIF;
	fopen_s(&MIF, "MSinfo.txt", "a+");//Member information

	if (MIF == NULL) {
		printf("파일에 대한 오류가 발생하였습니다.\n");
		printf("메뉴로 돌아갑니다.\n");
		return;
	}

	struct membership_info MI;//MI라는 이름의 구조체 변수를 선언
	memset(&MI, NULL, sizeof(MI));//구조체변수의 0으로 초기화

	//printf("%d", MI.membership_name[0]); //이름 초기화 테스트문
	//printf("%d", MI.membership_phonenum[0]); //전화번호 초기화 테스트문
	//printf("%d", MI.membership_socialnum[0]); // 생년월일 초기화 테스트문


	//printf("구조체내부 초기화확인테스트문\n");
	//printf("%d\n", MI.membership_name[0]);
	
	/*while (getchar() != '\n') rewind 문으로 대체하였음.
		continue;*/

	rewind(stdin);

	printf("================================신규 회원 등록=================================\n");

	printf("[회원 이름을 입력하세요.]\n");
	printf("(회원 이름은 19자이하로 작성하세요.)\n");
	printf(">");
	fgets(MI.membership_name, sizeof(MI.membership_name), stdin);

	//printf("%d", MI.membership_name[0]);
	while (MI.membership_name[0] == NULL || MI.membership_name[0] == 10) {
		printf("회원 이름은 필수 입력 사항입니다. \n");
		printf("회원 이름을 입력하세요. \n");
		fgets(MI.membership_name, sizeof(MI.membership_name), stdin);
	}

	printf("회원 이름 입력을 완료하였습니다.");

	rewind(stdin);
	system("cls");
	printf("===============================================================================\n");

	//printf("%d\n", MI.membership_phonenum[0]);

	printf("[회원의 전화번호를 11자리 모두 입력하세요.]\n");
	printf("(하이폰 (-) 입력시 전화번호가 올바르게 입력되지 않습니다.) \n");
	printf(">");
	fgets(MI.membership_phonenum, sizeof(MI.membership_phonenum), stdin);

		while ((MI.membership_phonenum[0] == NULL) || (MI.membership_phonenum[0] == 10)) {
			printf("아무것도 입력되지 않았습니다.\n");
			printf("회원의 전화번호는 필수 입력 사항입니다. \n");
			printf("회원의 전화번호를 입력하세요. \n");
			printf(">");
			fgets(MI.membership_phonenum, sizeof(MI.membership_phonenum), stdin);
		}

	int k = 0;
	for (int i = 0; i < 11; i++) {//전화번호 변수에 숫자가 아닌 값이 입력되었는지 판별, 확인된 경우 k에 1을 입력
		if (!(MI.membership_phonenum[i] >= 48) && (MI.membership_phonenum[i] <= 57))
			k = 1;
		else if ( (MI.membership_phonenum[i] >= 48) && (MI.membership_phonenum[i] <= 57) )
			k = 0;
	}

	while (k == 1) {
		printf("[전화번호는 숫자로 입력하십시오.]\n");
		rewind(stdin);
		printf(">");
		fgets(MI.membership_phonenum, sizeof(MI.membership_phonenum), stdin);
		for (int i = 0; i < 11; i++) {//전화번호 변수에 숫자가 아닌 값이 입력되었는지 판별, 확인된 경우 k에 1을 입력
			if ( !( ( MI.membership_phonenum[i] >= 48 ) && ( MI.membership_phonenum[i] <= 57 ) ) ) {
				k = 1;
				break;
			}
			else if ( ( MI.membership_phonenum[i] >= 48 ) && ( MI.membership_phonenum[i] <= 57 ) ) {
				k = 0;
			}
		}
	}
	if (k == 0)
		printf("전화번호가 올바르게 입력되었습니다.\n");

	

	rewind(stdin);
	system("cls");
	printf("===============================================================================\n");
	printf("[회원의 생년월일을 입력하세요.]\n");
	printf("(회원의 생년월일은 성인용 비디오를 대여하기 위하여 사용됩니다.)\n");
	printf(">");
	fgets(MI.membership_socialnum, sizeof(MI.membership_socialnum), stdin);
	while ((MI.membership_socialnum[0] == NULL) || (MI.membership_socialnum[0] == 10)) {//아무것도 입력되지 않은경우
		printf("아무것도 입력되지 않았습니다.\n");
		printf("회원의 생년월일은 필수 입력 사항입니다. \n");
		printf("회원의 생년월일을 입력하세요. \n");
		printf(">");
		fgets(MI.membership_socialnum, sizeof(MI.membership_socialnum), stdin);
	}

	printf("생년월일이 올바르게 입력되었습니다.\n");

	rewind(stdin);

	printf("회원등록이 완료되었습니다.\n");
	printf("===============================================================================\n");

	struct membership_info IMI;
	memset(&IMI, NULL, sizeof(IMI));
	
	int i=0;//회원번호를 저장하는 변수
	fseek(MIF, 0, SEEK_SET);//파일을 처음부터 읽기위함
	while (feof(MIF) == 0) {//파일을 끝까지 읽는 동안 while문 실행
		fread(&IMI, sizeof(IMI), 1, MIF);//MI크기로 MIF를 읽어 
		if (IMI.membership_number >= 0) { //MI.membership_number이 0보다 큰게 존재하는 경우 i를 1 증가함.
			i++;
		}
	}//파일을 끝까지 읽어가며 MI.membership_number가 한번 존재하면 i++가 1회 실행, 두번 존재하면 i++가 2회 실행...
	MI.membership_number = i;//i의 갯수가 곧 파일내에 존재하는 번호보다 하나 큰 수를 입력함.

	printf("회원 이름 : %s", MI.membership_name);
	printf("회원 번호 : %d\n", MI.membership_number);
	printf("회원 전화번호 : %s\n", MI.membership_phonenum);
	printf("회원 생년월일 : %s\n", MI.membership_socialnum);

	fwrite(&MI, sizeof(MI), 1, MIF);//MI구조체 파일에 쓰기
	fclose(MIF);
	printf("\n");
}