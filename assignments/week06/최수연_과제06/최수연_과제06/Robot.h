#pragma once
#include "Mesh.h"

class Robot {
public:
	// Mesh Ŭ���� ��ü ����
	Mesh Head, Body, RightArm, RightHand, LeftArm, LeftHand;
	Mesh RightLeg, RightFoot, LeftLeg, LeftFoot;
	Mesh Hat, HammerHead, HammerHandle;
	float scale; // ���� ������

	Robot() {
		scale = 100; // ��ǥ���� -100 ~ 100 ����

		// ȭ�鿡 �κ� ��ǰ���� �ε��Ǿ����� Ȯ���ϴ� ���� ���
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
		if (flag) scale *= 1.05f; // Z�� ������ ���� ũ���� 1.05�谡 ��
		else scale *= 0.95; // z�� ������ ���� ũ���� 0.95�谡 ��
	}
	void draw() {
		Body.draw(0.5, 0.8, 0.8, scale, true); // ���� �׸���

		glPushMatrix(); // ���� ��ǥ�� ����
		glTranslated(0.0, -0.08, 0.0);
		glScalef(1.1f, 1.1f, 1.1f);
		Head.draw(0.8, 0.7, 0.7, scale); // �Ӹ� �׸���

		glPushMatrix(); // �Ӹ� ��ǥ�� ����
		glTranslated(0.0, -0.1, 0.0);
		glScalef(1.1f, 1.1f, 1.1f);
		Hat.draw(0.8, 0.7, 0.7, scale); // ���� �׸���
		glPopMatrix(); // �Ӹ� ��ǥ��� ���ư���
		glPopMatrix(); // ���� ��ǥ��� ���ư���

		glPushMatrix(); // ���� ��ǥ�� ����
		RightArm.draw(0.4, 0.4, 0.8, scale); // �����ʾ�� �׸���

		glPushMatrix(); // �����ʾ�� ��ǥ�� ����
		RightHand.draw(0.8, 0.8, 0.8, scale); // ������ �׸���

		glPushMatrix(); // ������ ��ǥ�� ����
		HammerHandle.draw(0.8, 0.8, 0.8, scale); // �ظ� ������ �׸���
		
		glPushMatrix(); // �ظ� ������ ��ǥ�� ����
		HammerHead.draw(0.8, 0.8, 0.8, scale); // �ظӸӸ� �׸���

		glPopMatrix(); // �ظ� ������ ��ǥ��� ���ư���
		glPopMatrix(); // ������ ��ǥ��� ���ư���
		glPopMatrix(); // �����ʾ�� ��ǥ��� ���ư���
		glPopMatrix(); // ���� ��ǥ��� ���ư���

		glPushMatrix(); // ���� ��ǥ�� ����
		LeftArm.draw(0.4, 0.4, 0.8, scale); // ���ʾ�� �׸���

		glPushMatrix(); // ���ʾ�� ��ǥ�� ����
		LeftHand.draw(0.8, 0.8, 0.8, scale); // �޼� �׸���
		glPopMatrix(); // ���ʾ�� ��ǥ��� ���ư���
		glPopMatrix(); // ���� ��ǥ��� ���ư���

		glPushMatrix(); // ���� ��ǥ�� ����
		RightLeg.draw(0.4, 0.4, 0.8, scale); // �����ʴٸ� �׸���

		glPushMatrix(); // �����ʴٸ� ��ǥ�� ����
		RightFoot.draw(0.8, 0.8, 0.8, scale); // ������ �׸���
		glPopMatrix(); // �����ʴٸ� ��ǥ��� ���ư���
		glPopMatrix(); // ���� ��ǥ��� ���ư���

		glPushMatrix(); // ���� ��ǥ�� ����
		LeftLeg.draw(0.4, 0.4, 0.8, scale); // ���ʴٸ� �׸���

		glPushMatrix(); // ���ʴٸ� ��ǥ�� ����
		LeftFoot.draw(0.8, 0.8, 0.8, scale); // �޹� �׸���
		glPopMatrix(); // ���ʴٸ� ��ǥ��� ���ư���
		glPopMatrix(); // ���� ��ǥ��� ���ư���
	}
};
