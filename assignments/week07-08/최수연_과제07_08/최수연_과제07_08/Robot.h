#pragma once
#include "Mesh.h"

class Robot {
public:
    // Mesh Ŭ���� ��ü ����
    Mesh Head, Body, RightArm, RightHand, LeftArm, LeftHand;
    Mesh RightLeg, RightFoot, LeftLeg, LeftFoot;
    float scale; // ���� ������

    Robot() {
        reset();
        scale = 100; // ��ǥ���� -100 ~ 100 ����

        // ȭ�鿡 �κ� ��ǰ���� �ε��Ǿ����� Ȯ���ϴ� ���� ���
        printf("Loading Robot Models.....\n");
        Head.readAse("S_Head.ASE");            printf("loading Head...........OK.\n");
        Body.readAse("S_Body.ASE");            printf("loading Body...........OK.\n");
        RightArm.readAse("S_RightArm.ASE");      printf("loading RightArm.......OK.\n");
        RightHand.readAse("S_RightHand.ASE");   printf("loading RightHand......OK.\n");
        LeftArm.readAse("S_LeftArm.ASE");      printf("loading LeftArm........OK.\n");
        LeftHand.readAse("S_LeftHand.ASE");      printf("loading LeftHand.......OK.\n");
        RightLeg.readAse("S_RightLeg.ASE");      printf("loading RightLeg.......OK.\n");
        RightFoot.readAse("S_RightFoot.ASE");   printf("loading RightFoot......OK.\n");
        LeftLeg.readAse("S_LeftLeg.ASE");      printf("loading LeftLeg........OK.\n");
        LeftFoot.readAse("S_LeftFoot.ASE");      printf("loading LeftFoot.......OK.\n");
    }
    // ������ ����
    void resize(bool flag = true) {
        if (flag) scale *= 1.05f; // Z�� ������ ���� ũ���� 1.05�谡 ��
        else scale *= 0.95; // z�� ������ ���� ũ���� 0.95�谡 ��
    }
    void draw() {
        glPushMatrix();
        bRun ? animateBody() : coldBody();
        Body.draw(0.5, 0.8, 0.8, scale, true); // ���� �׸���

        glPushMatrix(); // ���� ��ǥ�� ����
        glTranslated(0.0, 0.45, -0.07);
        glScalef(1.1f, 1.1f, 1.1f);
        bRun ? animateHead() : coldHead();
        Head.draw(0.8, 0.7, 0.7, scale); // �Ӹ� �׸���
        glPopMatrix(); // ���� ��ǥ��� ���ư���

        glPushMatrix(); // ���� ��ǥ�� ����
        glTranslated(-0.25, 0.32, 0.0);
        glScalef(1.0f, 1.0f, 1.0f);
        bRun ? animateRightArm() : coldRightArm();
        RightArm.draw(0.4, 0.4, 0.8, scale); // �����ʾ�� �׸���

        glPushMatrix(); // �����ʾ�� ��ǥ�� ����
        glTranslated(-0.05, -0.3, 0.0);
        glScalef(1.0f, 1.0f, 1.0f);
        bRun ? animateRightHand() : coldRightHand();
        RightHand.draw(0.8, 0.8, 0.8, scale); // ������ �׸���
        glPopMatrix(); // �����ʾ�� ��ǥ��� ���ư���
        glPopMatrix(); // ���� ��ǥ��� ���ư���

        glPushMatrix(); // ���� ��ǥ�� ����
        glTranslated(0.25, 0.32, 0.0);
        bRun ? animateLeftArm() : coldLeftArm();
        LeftArm.draw(0.4, 0.4, 0.8, scale); // ���ʾ�� �׸���

        glPushMatrix(); // ���ʾ�� ��ǥ�� ����
        glTranslated(0.05, -0.3, 0.0);
        bRun ? animateLeftHand() : coldLeftHand();
        LeftHand.draw(0.8, 0.8, 0.8, scale); // ���ʼ� �׸���
        glPopMatrix(); // ���ʼ� ��ǥ��� ���ư���
        glPopMatrix(); // ���� ��ǥ��� ���ư���

        glPushMatrix(); // ���� ��ǥ�� ����
        glTranslated(-0.12, -0.1, 0.0);
        glScalef(1.0f, 1.0f, 1.0f);
        bRun ? animateRightLeg() : coldRightLeg();
        RightLeg.draw(0.8, 0.8, 0.8, scale); // �����ʴٸ� �׸���

        glPushMatrix(); // �����ʴٸ� ��ǥ�� ����
        glTranslated(0.0, -0.40, 0.0);
        glScalef(1.0f, 1.0f, 1.0f);
        bRun ? animateRightFoot() : coldRightFoot();
        RightFoot.draw(0.5, 0.5, 0.6, scale); // ������ �׸���
        glPopMatrix(); // �����ʴٸ� ��ǥ��� ���ư���
        glPopMatrix(); // ���� ��ǥ��� ���ư���

        glPushMatrix(); // ���� ��ǥ�� ����
        glTranslated(0.12, -0.1, 0.0);
        glScalef(1.0f, 1.0f, 1.0f);
        bRun ? animateLeftLeg() : coldLeftLeg();
        LeftLeg.draw(0.8, 0.8, 0.8, scale); // ���ʴٸ� �׸���

        glPushMatrix(); // ���ʴٸ� ��ǥ�� ����
        glTranslated(0.0, -0.40, 0.0);
        glScalef(1.0f, 1.0f, 1.0f);
        bRun ? animateLeftFoot() : coldLeftFoot();
        LeftFoot.draw(0.5, 0.5, 0.6, scale);  // �޹� �׸���
        glPopMatrix(); // ���ʴٸ� ��ǥ��� ���ư���
        glPopMatrix(); // ���� ��ǥ��� ���ư���
        glPopMatrix();
    }
    /*----------------------------------------------*/
    // �ִϸ��̼� �ڵ�
    double tAngle, sin_t = 0, sin_t2 = 0, cos_t = 0;
    bool bRun, bCold;
    void reset() {
        bRun = false;
        bCold = false;
        scale = 100;
        tAngle = 0;
    }
    void stop() { bRun = false; bCold = false; }
    void run() {
        bRun = true;
        bCold = false;
        tAngle += 20;
        if (tAngle >= 360)
            tAngle -= 360;
        sin_t = SIN(tAngle);
        cos_t = COS(tAngle);
        sin_t2 = SIN(2 * tAngle);
    }
    void coldRun() {
        bRun = false;
        bCold = true;
        tAngle += 20;
        if (tAngle >= 360)
            tAngle -= 360;
        sin_t = SIN(tAngle);
        cos_t = COS(tAngle);
        sin_t2 = SIN(2 * tAngle);
    }
    // �� ��ǰ�� ���� �ִϸ��̼� �� ��ȯ: RUN
    void animateBody() {
        glTranslated(0.0, (sin_t2 * 0.08), 0);
        glRotatef(-sin_t2 * 15 - 10, 1, 0, 0);
        glRotatef(-sin_t * 13, 0, 1, 0);
    }
    void animateHead() {
        glRotatef(-cos_t * 20, 0, 1, 0);
    }
    void animateRightArm() {
        glRotatef(-cos_t * 65, 1, 0, 0);
    }
    void animateRightHand() {
        glRotatef(-cos_t * 45 + 70, 1, 0, 0);
        glRotatef(-sin_t * 20 - 20, 0, 1, 0);
    }
    void animateLeftArm() {
        glRotatef(cos_t * 65, 1, 0, 0);
    }
    void animateLeftHand() {
        glRotatef(cos_t * 45 + 70, 1, 0, 0);
        glRotatef(sin_t * 20 + 20, 0, 1, 0);
    }
    void animateRightLeg() {
        glRotatef(cos_t * 45 + 35, 1, 0, 0);
    }
    void animateRightFoot() {
        glRotatef(sin_t * 50 - 55, 1, 0, 0);
        glRotatef(tAngle / 20, 0, -1, 0);
    }
    void animateLeftLeg() {
        glRotatef(-cos_t * 45 + 35, 1, 0, 0);
    }
    void animateLeftFoot() {
        glRotatef(-sin_t * 50 - 55, 1, 0, 0);
        glRotatef(-1 * (tAngle / 20), 0, -1, 0);
    }

    // �� ��ǰ�� ���� �ִϸ��̼� �� ��ȯ: COLD
    void coldBody() {
        glTranslated(0.0, sin_t2 * 0.02, 0); // ���� ���� �̵�
        glRotatef(-sin_t * 13, 0, 1, 0); // ���� �¿� ȸ��
    }
    void coldHead() {
        glRotatef(-cos_t * 20, 0, 1, 0); // �Ӹ� �¿� ȸ��
    }
    void coldRightArm() {
        glRotatef(-sin_t2 * 5, 0, 0, 1);
    }
    void coldRightHand() {
        glRotatef(sin_t2 * 5 + 130, 1, 0, 0);
        glRotatef(-sin_t2 * 5, 0, 0, 1);
    }
    void coldLeftArm() {
        glRotatef(sin_t2 * 5, 0, 0, 1);
    }
    void coldLeftHand() {
        glRotatef(sin_t2 * 5 + 130, 1, 0, 0);
        glRotatef(sin_t2 * 5, 0, 0, 1);
    }
    void coldRightLeg() {
        glRotatef(cos_t * 25 + 15, 1, 0, 0);
    }
    void coldRightFoot() {
        glRotatef(-cos_t * 45 - 45, 1, 0, 0);
    }
    void coldLeftLeg() {
        glRotatef(-cos_t * 25 + 15, 1, 0, 0);
    }
    void coldLeftFoot() {
        glRotatef(cos_t * 45 - 45, 1, 0, 0);
    }
};