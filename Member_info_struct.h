#pragma once

struct membership_info {
	char membership_name[20]; //회원명
	char membership_phonenum[12]; //회원 전화번호
	char membership_socialnum[9]; //회원 생년월일
	int membership_number; // 회원번호
	char Rental_Video_List[30]; //대여비디오 번호로 등록하면 되네
	int rental_fee;
};
struct video_info {
	char video_name[50]; //비디오이름
	int video_num; //비디오번호
	int video_genre[23];//비디오장르
	char video_production_company[50];//비디오제작사
	int same_video_num;//같은 비디오 이름의 갯수
	int video_rental_fee;//비디오의 대여가격
};