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
	//system("mode con:cols=80 lines=30");//�ܼ�â�� ũ�⸦ ����

	for (;;) {
		int User_select_num = main_page();/*������������ ���� �Լ� main_page
											return ���� ����� ���� ��ȣ
											[Main_UI.h�� ��ġ�� �Լ�] */
		Sleep(1000);//1�ʰ� ���
		system("cls");//ȭ�� �ʱ�ȭ
		switch (User_select_num) {
		case 1: {
			new_member();//1���޴� : �ű� ȸ�� ��� [New_member.h�� ��ġ�� �Լ�]
			break;
		}
		case 2: {
			new_video();//2���޴� : �ű� ���� ��� [New_video.h�� ��ġ�� �Լ�]
			break;
		}
		case 3: {
			rental_video();//3���޴� : ���� �뿩 [Rental_Video.h�� ��ġ�� �Լ�]
			break;
		}
		case 4: {
			video_print();//4���޴� : ����� ���� ��� [print_all.h�� ��ġ�� �Լ�]
			break;
		}
		case 5: {
			member_print();//5�� �޴� : ����� ȸ�� ��� [print_all.h�� ��ġ�� �Լ�]
			break;
		}
		case 6: {
			delete_member();//6�� �޴� : ����� ȸ�� ���� [Member_Delete.h�� ��ġ�� �Լ�]
			break;
		}
		case 7: {
			video_return();//7�� �޴� : �뿩�� ���� �ݳ� [Video_Return.h�� ��ġ�� �Լ�]
			break;
		}
		case 11: {
			printf("11 : ȭ�� �ʱ�ȭ");
			system("cls");
			break;
		}
		default:
			printf("�߸��� ��ȣ�� �Է��ϼ̽��ϴ�.\n");
			printf("���α׷��� �����մϴ�.\n");
			exit(1);
		}

	}
	return 0;
}