#pragma once
#include "Mesh.h"

class Robot {
public:
	// Mesh 클래스 객체 생성
	Mesh Head, Body, RightArm, RightHand, LeftArm, LeftHand;
	Mesh RightLeg, RightFoot, LeftLeg, LeftFoot;
	Mesh Hat, HammerHead, HammerHandle;
	float scale; // 모델의 스케일

	Robot() {
		scale = 100; // 좌표값이 -100 ~ 100 범위

		// 화면에 로봇 부품들이 로딩되었음을 확인하는 문자 출력
		printf("Loading Robot Models.....\n");

		Head.readAse("Head.ASE");				printf("loading Head...........OK.\n");
		Body.readAse("Body.ASE");				printf("loading Body...........OK.\n");
		RightArm.readAse("RightArm.ASE");		printf("loading RightArm.......OK.\n");
		RightHand.readAse("RightHand.ASE");		printf("loading RightHand......OK.\n");
		LeftArm.readAse("LeftArm.ASE");			printf("loading LeftArm........OK.\n");
		LeftHand.readAse("LeftHand.ASE");		printf("loading LeftHand.......OK.\n");
		RightLeg.readAse("RightLeg.ASE");		printf("loading RightLeg.......OK.\n");
		RightFoot.readAse("RightFoot.ASE");		printf("loading RightFoot......OK.\n");
		LeftLeg.readAse("LeftLeg.ASE");			printf("loading LeftLeg........OK.\n");
		LeftFoot.readAse("LeftFoot.ASE");		printf("loading LeftFoot.......OK.\n");
		Hat.readAse("Hat.ASE");					printf("loading Hat.......OK.\n");
		HammerHead.readAse("HammerHead.ASE");			printf("loading HammerHead.......OK.\n");
		HammerHandle.readAse("HammerHandle.ASE");		printf("loading HammerHandle.......OK.\n");

		//Head.readAse("S_Head.ASE");				printf("loading Head...........OK.\n");
		//Body.readAse("S_Body.ASE");				printf("loading Body...........OK.\n");
		//RightArm.readAse("S_RightArm.ASE");		printf("loading RightArm.......OK.\n");
		//RightHand.readAse("S_RightHand.ASE");		printf("loading RightHand......OK.\n");
		//LeftArm.readAse("S_LeftArm.ASE");			printf("loading LeftArm........OK.\n");
		//LeftHand.readAse("S_LeftHand.ASE");		printf("loading LeftHand.......OK.\n");
		//RightLeg.readAse("S_RightLeg.ASE");		printf("loading RightLeg.......OK.\n");
		//RightFoot.readAse("S_RightFoot.ASE");		printf("loading RightFoot......OK.\n");
		//LeftLeg.readAse("S_LeftLeg.ASE");		    printf("loading LeftLeg........OK.\n");
		//LeftFoot.readAse("S_LeftFoot.ASE");		printf("loading LeftFoot.......OK.\n");
	}
	void resize(bool flag = true) {
		if (flag) scale *= 1.05f; // Z를 누르면 원래 크기의 1.05배가 됨
		else scale *= 0.95; // z를 누르면 원래 크기의 0.95배가 됨
	}
	void draw() {
		Body.draw(0.5, 0.8, 0.8, scale, true); // 몸통 그리기

		glPushMatrix(); // 몸통 좌표계 저장
		glTranslated(0.0, -0.08, 0.0);
		glScalef(1.1f, 1.1f, 1.1f);
		Head.draw(0.8, 0.7, 0.7, scale); // 머리 그리기

		glPushMatrix(); // 머리 좌표계 저장
		glTranslated(0.0, -0.1, 0.0);
		glScalef(1.1f, 1.1f, 1.1f);
		Hat.draw(0.8, 0.7, 0.7, scale); // 모자 그리기
		glPopMatrix(); // 머리 좌표계로 돌아가기
		glPopMatrix(); // 몸통 좌표계로 돌아가기

		glPushMatrix(); // 몸통 좌표계 저장
		RightArm.draw(0.4, 0.4, 0.8, scale); // 오른쪽어깨 그리기

		glPushMatrix(); // 오른쪽어깨 좌표계 저장
		RightHand.draw(0.8, 0.8, 0.8, scale); // 오른손 그리기

		glPushMatrix(); // 오른손 좌표계 저장
		HammerHandle.draw(0.8, 0.8, 0.8, scale); // 해머 손잡이 그리기
		
		glPushMatrix(); // 해머 손잡이 좌표계 저장
		HammerHead.draw(0.8, 0.8, 0.8, scale); // 해머머리 그리기

		glPopMatrix(); // 해머 손잡이 좌표계로 돌아가기
		glPopMatrix(); // 오른손 좌표계로 돌아가기
		glPopMatrix(); // 오른쪽어깨 좌표계로 돌아가기
		glPopMatrix(); // 몸통 좌표계로 돌아가기

		glPushMatrix(); // 몸통 좌표계 저장
		LeftArm.draw(0.4, 0.4, 0.8, scale); // 왼쪽어깨 그리기

		glPushMatrix(); // 왼쪽어깨 좌표계 저장
		LeftHand.draw(0.8, 0.8, 0.8, scale); // 왼손 그리기
		glPopMatrix(); // 왼쪽어깨 좌표계로 돌아가기
		glPopMatrix(); // 몸통 좌표계로 돌아가기

		glPushMatrix(); // 몸통 좌표계 저장
		RightLeg.draw(0.4, 0.4, 0.8, scale); // 오른쪽다리 그리기

		glPushMatrix(); // 오른쪽다리 좌표계 저장
		RightFoot.draw(0.8, 0.8, 0.8, scale); // 오른발 그리기
		glPopMatrix(); // 오른쪽다리 좌표계로 돌아가기
		glPopMatrix(); // 몸통 좌표계로 돌아가기

		glPushMatrix(); // 몸통 좌표계 저장
		LeftLeg.draw(0.4, 0.4, 0.8, scale); // 왼쪽다리 그리기

		glPushMatrix(); // 왼쪽다리 좌표계 저장
		LeftFoot.draw(0.8, 0.8, 0.8, scale); // 왼발 그리기
		glPopMatrix(); // 왼쪽다리 좌표계로 돌아가기
		glPopMatrix(); // 몸통 좌표계로 돌아가기
	}
};
