#include "Robot.h"
#include <gl/glut.h>
#include "glk.h"

//static Mesh obj3D; 
static Robot robot; // Robot 클래스 객체 robot 생성
static bool bCamRot = false;
static bool bRobotRun = false;
static bool bColdRun = false; // 나만의 동작
static double tSpeed = 100;
static float RotX = 0.0f;
static float RotY = 0.0f;

void DrawScene() { // 모델의 바닥 표현
	glPushMatrix(); // 현재 좌표계 저장
	glTranslatef(0.0, -1.0, 0.0); // y축으로 -1만큼 이동, 로봇의 발밑에 사각형이 그려지도록 함
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // 앞뒷면 채움
	glBegin(GL_POLYGON); // 사각형 그리기 시작
	glVertex3f(0.6, 0.0, 0.6);
	glVertex3f(0.6, 0.0, -0.6);
	glVertex3f(-0.6, 0.0, -0.6);
	glVertex3f(-0.6, 0.0, 0.6);
	glEnd(); // 사각형 그리기 종료
	glPopMatrix();
}

//void display() {
//	glClearColor(0.99, 0.97, 0.97, 1.0); // 배경 색상 설정
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 버퍼 초기화
//
//	glMatrixMode(GL_MODELVIEW); // 시점 변환
//	glLoadIdentity(); // 모델뷰 행렬을 항등행렬로 바꿈
//	gluLookAt(0, 0, 0, -SIN(RotY), -0.01 * RotX, -COS(RotY), 0, 1, 0); // 시점 좌표계 정의 함수
//	robot.draw();
//	glutSwapBuffers();
//	glFlush();
//}

void display() {
	glClearColor(0.99, 0.97, 0.97, 1.0); // 배경 색상 설정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 버퍼 초기화

	// 왼쪽 아래 화면, 정면도
	glViewport(-20, 10, 350, 350);
	glMatrixMode(GL_MODELVIEW); // 시점 변환
	glPushMatrix();
	glLoadIdentity(); // 모델뷰 행렬을 항등행렬로 바꿈
	gluLookAt(0, 0, 0, -SIN(RotY), -0.01 * RotX, -COS(RotY), 0, 1, 0); // 시점 좌표계 정의 함수
	DrawScene();
	robot.draw();
	glPopMatrix();

	// 오른쪽 아래 화면, 측면도
	glViewport(330, 10, 350, 350);
	glPushMatrix();
	gluLookAt(0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	DrawScene();
	robot.draw();
	glPopMatrix();

	// 왼쪽 위 화면, 평면도
	glViewport(-20, 360, 350, 350);
	glPushMatrix();
	gluLookAt(0.0, -0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 2.0);
	DrawScene();
	robot.draw();
	glPopMatrix();

	// 오른쪽 위 화면, 측면도(glFrustum() 사용하여 원근투상 표현)
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

	glMatrixMode(GL_MODELVIEW); // 시점 변환
	glLoadIdentity(); // 모델뷰 행렬을 항등행렬로 바꿈
	//gluLookAt(0, 0, 0, -SIN(RotY), -0.01 * RotX, -COS(RotY), 0, 1, 0); // 시점 좌표계 정의 함수

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
	/*if (key == 'l') { // 파일 다이얼로그 열기
		char* filename = glkFileDlg(FILTER_ASE);
		if (filename != NULL)
			obj3D.readAse(filename);
	}
	else*/ if (key == 'i') { // 단위행렬로 초기화
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
			glutTimerFunc(40, timerCallback, 2); // 타이머 시작
		else robot.stop();
	}
	else if (key == 'c') {
		bColdRun = !bColdRun; // Toggle Run
		if (bRobotRun == true && bColdRun == true)
			bRobotRun = false;
		if (bColdRun)
			glutTimerFunc(40, timerCallback, 3); // 타이머 시작
		else robot.stop();
	}
	else if (key == 'f' || key == 'F') { // f 누르면 현재 속도의 0.9배, F 누르면 현재 속도의 1.1배
		tSpeed *= ((key == 'f') ? 0.9 : 1.1);
	}
	else if (key == 'w') { // 모델 외부 표면을 선으로 채우고, 내부 표면을 점으로 채움
		glPolygonMode(GL_FRONT, GL_LINE); // 폴리곤모드: 도형이 그려지는 모드
		glPolygonMode(GL_BACK, GL_POINT);
	}
	else if (key == 's') { // 모델 외부 표면을 모두 채우고, 내부를 선으로 채움
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_LINE);
	}
	else if (key == 'z' || key == 'Z') { // z를 누르거나 Z를 누르면 크기 변환
		robot.resize(key == 'z'); // Robot 클래스의 resize 함수 사용
	}
	else if (key == 'q') // q를 누르면 실행 종료
		exit(0);
	glutPostRedisplay(); // 화면에 모델을 다시 그리도록 요청
}

static int PrevX, PrevY;
void mouseClick(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) { // 만약 마우스 왼쪽 버튼을 눌러 드래그하면
		PrevX = x; // 마우스의 x, y의 위치를 현재 위치로 변경
		PrevY = y;
	}
}
void mouseMotion(GLint x, GLint y) {
	RotX += (PrevY - y); // 각각 움직인 x, y만큼 회전되도록 설정
	RotY += (PrevX - x);
	PrevX = x;
	PrevY = y; // 다시 motion이 동작한만큼 PrevX와 PrevY에 각각 값을 저장
	glutPostRedisplay(); // 화면에 모델을 다시 그리도록 요청
}

void InitRendering() {
	// mesh의 재질 색, 광원 값
	GLfloat mat_specular[] = { 0.5f, 1.0f, 0.5f, 1.0f };
	GLfloat mat_shininess[] = { 700.0f };
	// 조명의 색, 광원값
	GLfloat light_specular[] = { 0.8f, 0.5f, 0.8f, 1.0f };
	GLfloat light_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat light_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat light_position[] = { 0.f, -2.5f, 2.5f, 0.0f };
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING); // 조명 사용 설정
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE); // 정규화

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

	glkSetColor(0.5, 0.5, 0.5, 1.0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);

	glEnable(GL_DEPTH_TEST); // depth 검사(z-버퍼 사용)
	glShadeModel(GL_SMOOTH);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv); // GLUT 초기화
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(700, 700); // 윈도우 크기
	glutCreateWindow("RobotWorld"); // 윈도우 생성

	glutDisplayFunc(display); // 디스플레이 콜백 등록
	glutKeyboardFunc(keyboard); // 키보드 콜백 등록
	glutMouseFunc(mouseClick); // 마우스 클릭 콜백 등록
	glutMotionFunc(mouseMotion); // 마우스 모션 콜백 등록

	InitRendering(); // 조명값 설정
	keyboard('s', 0, 0);
	keyboard('l', 0, 0);
	//glFrontFace(GL_CW);

	glutMainLoop(); // GLUT event processing loop.
	return 0;
}
