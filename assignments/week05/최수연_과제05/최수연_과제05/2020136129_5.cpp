#include "2020136129_5.h"
#include <windows.h>
// ������ǥ��� ǥ��
static double P[12] = { 0.3, 0.2, 0.1, 1,	0.7, 0.2, 0.1, 1,	0.5, 0.7, 0.1, 1 }; // ���� P�ﰢ��
static double Q[12]; // ��ȯ�� Q�ﰢ��
static double R[12]; // ��ȯ�� R�ﰢ��
static double S[12]; // ��ȯ�� S�ﰢ��
static double T[12]; // ��ȯ�� T�ﰢ��
static double U[12]; // ��ȯ�� U�ﰢ��

void display() {
	glClear(GL_COLOR_BUFFER_BIT); // ȭ�� �ʱ�ȭ
	glColor3f(1.0, 0.0, 0.0); // ����
	glkTriangle4d(P); // P�ﰢ��
	glColor3f(0.0, 0.0, 1.0); // �Ķ�
	glkTriangle4d(Q); // Q�ﰢ��
	glColor3f(0.0, 1.0, 0.0); // ����
	glkTriangle4d(R); // R�ﰢ��
	glColor3f(1.0, 0.0, 1.0); // ���
	glkTriangle4d(T); // T�ﰢ��
	glColor3f(1.0, 1.0, 0.0); // ��ȫ
	glkTriangle4d(S); // S�ﰢ��
	glColor3f(0.0, 1.0, 1.0); // �ϴ�
	glkTriangle4d(U); // U�ﰢ��
	glkCoord(); // ��ǥ��
	glFlush(); // ȭ�� ����
}
void transformTri(double* m, double* p, double* q) { // ���� ��ȯ ó��
	glkTransform(m, p, q);
	glkTransform(m, p + 4, q + 4);
	glkTransform(m, p + 8, q + 8);
}
void keyboard(unsigned char key, int x, int y) {
	double m1[16], m2[16], m3[16];

	if (key == 'i') { // �ʱ�ȭ(i)
		printf("�ʱ�ȭ(i)\n");
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
	else if (key == 't') { // �̵�(t)
		printf("�̵�(t)\n");
		glkMatTrans(m1, -1, -0.5, 0);
		glkMatPrint(m1);
		transformTri(m1, P, Q);
	}
	else if (key == 's') { // ����(s)
		printf("����(s)\n");
		glkMatScale(m1, 1.5, 1.2, 1.4);
		glkMatPrint(m1);
		transformTri(m1, P, Q);
	}
	else if (key == 'x') { // X�� ȸ��(x)
		printf("X�� ȸ��(x)\n");
		glkMatRotateX(m1, 60);
		glkMatPrint(m1);
		transformTri(m1, P, Q);
	}
	else if (key == 'y') { // Y�� ȸ��(y)
		printf("Y�� ȸ��(y)\n");
		glkMatRotateY(m1, 60);
		glkMatPrint(m1);
		transformTri(m1, P, Q);
	}
	else if (key == 'z') { // Z�� ȸ��(z)
		printf("Z�� ȸ��(z)\n");
		glkMatRotateZ(m1, 60);
		glkMatPrint(m1);
		transformTri(m1, P, Q);
	}
	else if (key == 'Z') { // ���պ�ȯ: ȸ��(Z)
		printf("���պ�ȯ: ȸ��(Z)\n");
		glkMatTrans(m1, -P[0], -P[1], -P[2]);
		glkMatRotateZ(m2, 60);
		glkMatTrans(m3, P[0], P[1], P[2]);
		glkMatMult(m3, m2);
		glkMatMult(m3, m1);
		glkMatPrint(m3);
		transformTri(m3, P, Q);

		//glkMatTrans(m1, -P[0], -P[1], -P[2]);
		//printf("m1\n");
		//glkMatPrint(m1);
		//glkMatRotateZ(m2, 60);
		//printf("m2\n");
		//glkMatPrint(m2);
		//glkMatTrans(m3, P[0], P[1], P[2]);
		//printf("m3\n");
		//glkMatPrint(m3);
		//glkMatMult(m3, m2);
		//printf("m3<-m2\n");
		//glkMatPrint(m3);
		//glkMatMult(m3, m1);
		//printf("m3<-m1\n");
		//glkMatPrint(m3);
		//transformTri(m3, P, Q);
	}
	else if (key == 'c') { // ���պ�ȯ: ����(c)
		printf("���պ�ȯ: ����(c)\n");
		glkMatTrans(m1, P[0], P[1], P[2]);
		glkMatScale(m2, 1.5, 1.2, 1.4);
		glkMatTrans(m3, -P[0], -P[1], -P[2]);
		glkMatPrint(m3);
		glkMatPrint(m2);
		glkMatPrint(m1);
		glkMatMult(m1, m2);
		glkMatMult(m1, m3);
		glkMatPrint(m1);
		transformTri(m1, P, Q);
	}
	else if (key == 'h') { // �и�(h)
		printf("�и�(h)\n");
		glkMatShearX(m1, 0.3, 0);
		glkMatPrint(m1);
		transformTri(m1, P, Q);
	}
	else if (key == 'k') { // �ڽŸ��� ���պ�ȯ(k): �� �׸���
		printf("�ڽŸ��� ���պ�ȯ: �� �׸���(k)\n");
		glkMatTrans(m1, -P[0], -P[1], -P[2]);
		glkMatRotateZ(m2, 60);
		glkMatTrans(m3, P[0], P[1], P[2]);
		glkMatMult(m3, m2);
		glkMatMult(m3, m1);
		glkMatTrans(m2, -0.4, 0, 0);
		glkMatMult(m3, m2);
		glkMatPrint(m3);

		transformTri(m3, P, Q);
		transformTri(m3, Q, R);
		transformTri(m3, R, S);
		transformTri(m3, S, T);
		transformTri(m3, T, U);
	}
	else if (key == 'q') exit(0); // ����(q)
	glutPostRedisplay();
}
static double PrevX, PrevY; // ���콺 ��ġ ����
void mouseClick(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		PrevX = x;
		PrevY = y;
	}
	glutAttachMenu(GLUT_RIGHT_BUTTON); // ��Ŭ��
}
void mouseMotion(GLint x, GLint y) { // ���콺�� ���� ȭ�� ��ȯ
	glMatrixMode(GL_MODELVIEW);
	glRotated(x - PrevX, 0, 1, 0);
	glRotated(y - PrevY, 1, 0, 0);
	PrevX = x;
	PrevY = y;
	glutPostRedisplay();
}

void myMenu(int id) { // �˾� �޴� �׸���
	if (id == 0) keyboard('i', 0, 0);
	else if (id == 1) keyboard('t', 0, 0);
	else if (id == 2) keyboard('s', 0, 0);
	else if (id == 3) keyboard('x', 0, 0);
	else if (id == 4) keyboard('y', 0, 0);
	else if (id == 5) keyboard('z', 0, 0);
	else if (id == 6) keyboard('Z', 0, 0);
	else if (id == 7) keyboard('c', 0, 0);
	else if (id == 8) keyboard('h', 0, 0);
	else if (id == 9) keyboard('k', 0, 0);
	else if (id == 10) exit(0);
	glutPostRedisplay();
}

void initMenu(void) {	// ��Ŭ�� �� �˾� �޴�
	GLint MyMainMenuID = glutCreateMenu(myMenu);
	glutAddMenuEntry("Reset(i)", 0);
	glutAddMenuEntry("t", 1);
	glutAddMenuEntry("s", 2);
	glutAddMenuEntry("x", 3);
	glutAddMenuEntry("y", 4);
	glutAddMenuEntry("z", 5);
	glutAddMenuEntry("Z", 6);
	glutAddMenuEntry("c", 7);
	glutAddMenuEntry("h", 8);
	glutAddMenuEntry("k", 9);
	glutAddMenuEntry("Exit(q)", 10);
}

void reshape(int width, int height) { // ������ ũ�� ���� �ÿ��� ��ü ���� ������ ���� �Լ�
	glViewport(0, 0, width, height); // ����Ʈ ����
	double wScale = (double)width / 500; // �ʺ� ����
	double hScale = (double)height / 500; // ���� ����
	glMatrixMode(GL_PROJECTION); // ȭ�� ��ġ ��� �� ����
	glLoadIdentity(); // ���� ��ķ� �ʱ�ȭ
	glOrtho(-wScale, wScale, -hScale, hScale, -1, 1); // ����ü�� ���ú��� ����
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);					// GULT �ʱ�ȭ
	glutInitWindowSize(500, 500);			// ������ ũ��
	glutInitWindowPosition(0, 0);			// ������ ��ġ
	glutCreateWindow("2020136129 �ּ���");	// ������ ����
	glClearColor(1.0, 1.0, 1.0, 1.0);		// ���� ����
	initMenu();								// �˾� �޴� ���
	glutDisplayFunc(display);				// ���÷��� �ݹ� ���
	glutReshapeFunc(reshape);				// ������ ȭ�� ���� �ݹ� ���
	glutKeyboardFunc(keyboard);				// Ű���� �ݹ� ���
	glutMouseFunc(mouseClick);				// ���콺 Ŭ�� �ݹ� ���
	glutMotionFunc(mouseMotion);			// ���콺 ��� �ݹ� ���
	glutMainLoop();							// GLUT event processing loop.
	return 0;
}