#include <stdio.h>

// 메뉴 선택화면을 출력하는 함수
int main_page() {
	system("title 비디오 대여 프로그램");
	printf("==============================비디오 대여 프로그램==============================\n");
	printf("1. 회원 신규등록\n");
	printf("2. 비디오 신규등록\n");
	printf("3. 비디오 대여\n");
	printf("4. 전체 비디오 출력\n");
	printf("5. 전체 회원 출력\n");
	printf("6. 회원 삭제\n");
	printf("7. 비디오 반납\n");
	printf("11. 화면초기화\n");

	int select_num;
	printf(">");
	scanf_s("%d", &select_num);

	return select_num;
}