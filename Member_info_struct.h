#pragma once

struct membership_info {
	char membership_name[20]; //ȸ����
	char membership_phonenum[12]; //ȸ�� ��ȭ��ȣ
	char membership_socialnum[9]; //ȸ�� �������
	int membership_number; // ȸ����ȣ
	char Rental_Video_List[30]; //�뿩���� ��ȣ�� ����ϸ� �ǳ�
	int rental_fee;
};
struct video_info {
	char video_name[50]; //�����̸�
	int video_num; //������ȣ
	int video_genre[23];//�����帣
	char video_production_company[50];//�������ۻ�
	int same_video_num;//���� ���� �̸��� ����
	int video_rental_fee;//������ �뿩����
};