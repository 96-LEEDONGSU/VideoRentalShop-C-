#include <stdio.h>
#include <windows.h>
#include <string.h>
#include "Member_info_struct.h"
#include "Main_UI.h"
#include "New_member.h"
#include "New_video.h"
#include "Video_num_trans.h"
#include "Rental_Video.h"
#include "print_all.h"
#include "Member_Delete.h"
#include "Video_Return.h"

int main(void) {
	//system("mode con:cols=80 lines=30");//콘솔창의 크기를 설정

	for (;;) {
		int User_select_num = main_page();/*메인페이지를 띄우는 함수 main_page
											return 값은 사용자 선택 번호
											[Main_UI.h에 위치한 함수] */
		Sleep(1000);//1초간 대기
		system("cls");//화면 초기화
		switch (User_select_num) {
		case 1: {
			new_member();//1번메뉴 : 신규 회원 등록 [New_member.h에 위치한 함수]
			break;
		}
		case 2: {
			new_video();//2번메뉴 : 신규 비디오 등록 [New_video.h에 위치한 함수]
			break;
		}
		case 3: {
			rental_video();//3번메뉴 : 비디오 대여 [Rental_Video.h에 위치한 함수]
			break;
		}
		case 4: {
			video_print();//4번메뉴 : 저장된 비디오 출력 [print_all.h에 위치한 함수]
			break;
		}
		case 5: {
			member_print();//5번 메뉴 : 저장된 회원 출력 [print_all.h에 위치한 함수]
			break;
		}
		case 6: {
			delete_member();//6번 메뉴 : 저장된 회원 삭제 [Member_Delete.h에 위치한 함수]
			break;
		}
		case 7: {
			video_return();//7번 메뉴 : 대여한 비디오 반납 [Video_Return.h에 위치한 함수]
			break;
		}
		case 11: {
			printf("11 : 화면 초기화");
			system("cls");
			break;
		}
		default:
			printf("잘못된 번호를 입력하셨습니다.\n");
			printf("프로그램을 종료합니다.\n");
			exit(1);
		}

	}
	return 0;
}