#include "Robot.h"
#include <gl/glut.h>
#include "glk.h"

//static Mesh obj3D; 
static Robot robot; // Robot Ŭ���� ��ü robot ����
static bool bRobotRun = false;

void display() {
	glClearColor(0.8, 0.9, 0.8, 1.0); // ��� ���� ����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ���� �ʱ�ȭ

	robot.draw(); 
	//obj3D.draw(80.0f, true); 
	glutSwapBuffers();
	glFlush();
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
		PrevX = x;  // ���콺�� x, y�� ��ġ�� ���� ��ġ�� ����
		PrevY = y;
	}
}
void mouseMotion(GLint x, GLint y) {
	glMatrixMode(GL_MODELVIEW); // ȭ�鿡 ������ �׸��ٸ� GL_MODELVIEW ����� ���ؼ� ������ ��ġ�� ���Ѵ�.
	glRotated(x - PrevX, 0, -1, 0);
	glRotated(y - PrevY, -1, 0, 0); // ���� ������ x, y��ŭ ȸ���ǵ��� ����
	PrevX = x;
	PrevY = y; // �ٽ� motion�� �����Ѹ�ŭ PrevX�� PrevY�� ���� ���� ����
	glutPostRedisplay(); // �� �����찡 ����Ǿ�� ���� ǥ��
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
	glutInitWindowSize(600, 600); // ������ ũ��
	glutCreateWindow("RobotWorld"); // ������ ����

	glutDisplayFunc(display); // ���÷��� �ݹ� ���
	glutKeyboardFunc(keyboard); // Ű���� �ݹ� ���
	glutMouseFunc(mouseClick); // ���콺 Ŭ�� �ݹ� ���
	glutMotionFunc(mouseMotion); // ���콺 ��� �ݹ� ���

	InitRendering(); // ���� ����
	keyboard('s', 0, 0);
	keyboard('l', 0, 0);
	// glFrontFace(GL_CW);

	glutMainLoop(); // GLUT event processing loop.
	return 0;
}