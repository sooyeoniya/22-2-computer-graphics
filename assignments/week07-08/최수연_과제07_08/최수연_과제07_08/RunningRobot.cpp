#include "Robot.h"
#include <gl/glut.h>
#include "glk.h"

//static Mesh obj3D; 
static Robot robot; // Robot Ŭ���� ��ü robot ����
static bool bCamRot = false;
static bool bRobotRun = false;
static bool bColdRun = false; // ������ ����
static double tSpeed = 100;
static float RotX = 0.0f;
static float RotY = 0.0f;

void DrawScene() { // ���� �ٴ� ǥ��
	glPushMatrix(); // ���� ��ǥ�� ����
	glTranslatef(0.0, -1.0, 0.0); // y������ -1��ŭ �̵�, �κ��� �߹ؿ� �簢���� �׷������� ��
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // �յ޸� ä��
	glBegin(GL_POLYGON); // �簢�� �׸��� ����
	glVertex3f(0.6, 0.0, 0.6);
	glVertex3f(0.6, 0.0, -0.6);
	glVertex3f(-0.6, 0.0, -0.6);
	glVertex3f(-0.6, 0.0, 0.6);
	glEnd(); // �簢�� �׸��� ����
	glPopMatrix();
}

//void display() {
//	glClearColor(0.99, 0.97, 0.97, 1.0); // ��� ���� ����
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ���� �ʱ�ȭ
//
//	glMatrixMode(GL_MODELVIEW); // ���� ��ȯ
//	glLoadIdentity(); // �𵨺� ����� �׵���ķ� �ٲ�
//	gluLookAt(0, 0, 0, -SIN(RotY), -0.01 * RotX, -COS(RotY), 0, 1, 0); // ���� ��ǥ�� ���� �Լ�
//	robot.draw();
//	glutSwapBuffers();
//	glFlush();
//}

void display() {
	glClearColor(0.99, 0.97, 0.97, 1.0); // ��� ���� ����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ���� �ʱ�ȭ

	// ���� �Ʒ� ȭ��, ���鵵
	glViewport(-20, 10, 350, 350);
	glMatrixMode(GL_MODELVIEW); // ���� ��ȯ
	glPushMatrix();
	glLoadIdentity(); // �𵨺� ����� �׵���ķ� �ٲ�
	gluLookAt(0, 0, 0, -SIN(RotY), -0.01 * RotX, -COS(RotY), 0, 1, 0); // ���� ��ǥ�� ���� �Լ�
	DrawScene();
	robot.draw();
	glPopMatrix();

	// ������ �Ʒ� ȭ��, ���鵵
	glViewport(330, 10, 350, 350);
	glPushMatrix();
	gluLookAt(0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	DrawScene();
	robot.draw();
	glPopMatrix();

	// ���� �� ȭ��, ��鵵
	glViewport(-20, 360, 350, 350);
	glPushMatrix();
	gluLookAt(0.0, -0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 2.0);
	DrawScene();
	robot.draw();
	glPopMatrix();

	// ������ �� ȭ��, ���鵵(glFrustum() ����Ͽ� �������� ǥ��)
	glViewport(330, 360, 350, 350);
	//glPushMatrix();
	//gluLookAt(0.1, -0.1, 0.0, -5.0, 5.0, -5.0, 1.0, 1.0, 1.0);
	//DrawScene();
	//robot.draw();
	//glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glFrustum(-1.0f, 1.0f, -1.0f, 1.0f, 8.0f, 30.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	gluLookAt(-5.0, 5.0, -5.0,    0.1, -0.1, 0.0,    0.0, 1.0, 0.0);
	DrawScene();
	robot.draw();
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW); // ���� ��ȯ
	glLoadIdentity(); // �𵨺� ����� �׵���ķ� �ٲ�
	//gluLookAt(0, 0, 0, -SIN(RotY), -0.01 * RotX, -COS(RotY), 0, 1, 0); // ���� ��ǥ�� ���� �Լ�

	glutSwapBuffers();
	glFlush();
}

void timerCallback(int tId) {
	if (bCamRot && tId == 1) {
		RotY += 5;
		if (RotY > 360) RotY = 0;
		glutTimerFunc(50, timerCallback, 1);
	}
	if (bRobotRun && tId == 2) {
		robot.run();
		glutTimerFunc((int)(tSpeed), timerCallback, 2);
	}
	if (bColdRun && tId == 3) {
		robot.coldRun();
		glutTimerFunc((int)(tSpeed), timerCallback, 3);
	}
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	/*if (key == 'l') { // ���� ���̾�α� ����
		char* filename = glkFileDlg(FILTER_ASE);
		if (filename != NULL)
			obj3D.readAse(filename);
	}
	else*/ if (key == 'i') { // ������ķ� �ʱ�ȭ
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		RotX = RotY = 0.0f;
	}
	else if (key == 'v') {
		bCamRot = !bCamRot;
		glutTimerFunc(100, timerCallback, 1);
	}
	else if (key == 'r') {
		bRobotRun = !bRobotRun; // Toggle Run
		if (bRobotRun == true && bColdRun == true)
			bColdRun = false;
		if (bRobotRun)
			glutTimerFunc(40, timerCallback, 2); // Ÿ�̸� ����
		else robot.stop();
	}
	else if (key == 'c') {
		bColdRun = !bColdRun; // Toggle Run
		if (bRobotRun == true && bColdRun == true)
			bRobotRun = false;
		if (bColdRun)
			glutTimerFunc(40, timerCallback, 3); // Ÿ�̸� ����
		else robot.stop();
	}
	else if (key == 'f' || key == 'F') { // f ������ ���� �ӵ��� 0.9��, F ������ ���� �ӵ��� 1.1��
		tSpeed *= ((key == 'f') ? 0.9 : 1.1);
	}
	else if (key == 'w') { // �� �ܺ� ǥ���� ������ ä���, ���� ǥ���� ������ ä��
		glPolygonMode(GL_FRONT, GL_LINE); // ��������: ������ �׷����� ���
		glPolygonMode(GL_BACK, GL_POINT);
	}
	else if (key == 's') { // �� �ܺ� ǥ���� ��� ä���, ���θ� ������ ä��
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_LINE);
	}
	else if (key == 'z' || key == 'Z') { // z�� �����ų� Z�� ������ ũ�� ��ȯ
		robot.resize(key == 'z'); // Robot Ŭ������ resize �Լ� ���
	}
	else if (key == 'q') // q�� ������ ���� ����
		exit(0);
	glutPostRedisplay(); // ȭ�鿡 ���� �ٽ� �׸����� ��û
}

static int PrevX, PrevY;
void mouseClick(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) { // ���� ���콺 ���� ��ư�� ���� �巡���ϸ�
		PrevX = x; // ���콺�� x, y�� ��ġ�� ���� ��ġ�� ����
		PrevY = y;
	}
}
void mouseMotion(GLint x, GLint y) {
	RotX += (PrevY - y); // ���� ������ x, y��ŭ ȸ���ǵ��� ����
	RotY += (PrevX - x);
	PrevX = x;
	PrevY = y; // �ٽ� motion�� �����Ѹ�ŭ PrevX�� PrevY�� ���� ���� ����
	glutPostRedisplay(); // ȭ�鿡 ���� �ٽ� �׸����� ��û
}

void InitRendering() {
	// mesh�� ���� ��, ���� ��
	GLfloat mat_specular[] = { 0.5f, 1.0f, 0.5f, 1.0f };
	GLfloat mat_shininess[] = { 700.0f };
	// ������ ��, ������
	GLfloat light_specular[] = { 0.8f, 0.5f, 0.8f, 1.0f };
	GLfloat light_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat light_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat light_position[] = { 0.f, -2.5f, 2.5f, 0.0f };
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING); // ���� ��� ����
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE); // ����ȭ

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

	glkSetColor(0.5, 0.5, 0.5, 1.0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);

	glEnable(GL_DEPTH_TEST); // depth �˻�(z-���� ���)
	glShadeModel(GL_SMOOTH);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv); // GLUT �ʱ�ȭ
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(700, 700); // ������ ũ��
	glutCreateWindow("RobotWorld"); // ������ ����

	glutDisplayFunc(display); // ���÷��� �ݹ� ���
	glutKeyboardFunc(keyboard); // Ű���� �ݹ� ���
	glutMouseFunc(mouseClick); // ���콺 Ŭ�� �ݹ� ���
	glutMotionFunc(mouseMotion); // ���콺 ��� �ݹ� ���

	InitRendering(); // ���� ����
	keyboard('s', 0, 0);
	keyboard('l', 0, 0);
	//glFrontFace(GL_CW);

	glutMainLoop(); // GLUT event processing loop.
	return 0;
}
