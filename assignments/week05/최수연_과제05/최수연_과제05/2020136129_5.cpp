#include "2020136129_5.h"
#include <windows.h>
// 동차좌표계로 표시
static double P[12] = { 0.3, 0.2, 0.1, 1,	0.7, 0.2, 0.1, 1,	0.5, 0.7, 0.1, 1 }; // 기존 P삼각형
static double Q[12]; // 변환된 Q삼각형
static double R[12]; // 변환된 R삼각형
static double S[12]; // 변환된 S삼각형
static double T[12]; // 변환된 T삼각형
static double U[12]; // 변환된 U삼각형

void display() {
	glClear(GL_COLOR_BUFFER_BIT); // 화면 초기화
	glColor3f(1.0, 0.0, 0.0); // 빨강
	glkTriangle4d(P); // P삼각형
	glColor3f(0.0, 0.0, 1.0); // 파랑
	glkTriangle4d(Q); // Q삼각형
	glColor3f(0.0, 1.0, 0.0); // 연두
	glkTriangle4d(R); // R삼각형
	glColor3f(1.0, 0.0, 1.0); // 노랑
	glkTriangle4d(T); // T삼각형
	glColor3f(1.0, 1.0, 0.0); // 분홍
	glkTriangle4d(S); // S삼각형
	glColor3f(0.0, 1.0, 1.0); // 하늘
	glkTriangle4d(U); // U삼각형
	glkCoord(); // 좌표계
	glFlush(); // 화면 갱신
}
void transformTri(double* m, double* p, double* q) { // 정점 변환 처리
	glkTransform(m, p, q);
	glkTransform(m, p + 4, q + 4);
	glkTransform(m, p + 8, q + 8);
}
void keyboard(unsigned char key, int x, int y) {
	double m1[16], m2[16], m3[16];

	if (key == 'i') { // 초기화(i)
		printf("초기화(i)\n");
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
	else if (key == 't') { // 이동(t)
		printf("이동(t)\n");
		glkMatTrans(m1, -1, -0.5, 0);
		glkMatPrint(m1);
		transformTri(m1, P, Q);
	}
	else if (key == 's') { // 신축(s)
		printf("신축(s)\n");
		glkMatScale(m1, 1.5, 1.2, 1.4);
		glkMatPrint(m1);
		transformTri(m1, P, Q);
	}
	else if (key == 'x') { // X축 회전(x)
		printf("X축 회전(x)\n");
		glkMatRotateX(m1, 60);
		glkMatPrint(m1);
		transformTri(m1, P, Q);
	}
	else if (key == 'y') { // Y축 회전(y)
		printf("Y축 회전(y)\n");
		glkMatRotateY(m1, 60);
		glkMatPrint(m1);
		transformTri(m1, P, Q);
	}
	else if (key == 'z') { // Z축 회전(z)
		printf("Z축 회전(z)\n");
		glkMatRotateZ(m1, 60);
		glkMatPrint(m1);
		transformTri(m1, P, Q);
	}
	else if (key == 'Z') { // 복합변환: 회전(Z)
		printf("복합변환: 회전(Z)\n");
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
	else if (key == 'c') { // 복합변환: 신축(c)
		printf("복합변환: 신축(c)\n");
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
	else if (key == 'h') { // 밀림(h)
		printf("밀림(h)\n");
		glkMatShearX(m1, 0.3, 0);
		glkMatPrint(m1);
		transformTri(m1, P, Q);
	}
	else if (key == 'k') { // 자신만의 복합변환(k): 별 그리기
		printf("자신만의 복합변환: 별 그리기(k)\n");
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
	else if (key == 'q') exit(0); // 종료(q)
	glutPostRedisplay();
}
static double PrevX, PrevY; // 마우스 위치 저장
void mouseClick(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		PrevX = x;
		PrevY = y;
	}
	glutAttachMenu(GLUT_RIGHT_BUTTON); // 우클릭
}
void mouseMotion(GLint x, GLint y) { // 마우스에 따라 화면 전환
	glMatrixMode(GL_MODELVIEW);
	glRotated(x - PrevX, 0, 1, 0);
	glRotated(y - PrevY, 1, 0, 0);
	PrevX = x;
	PrevY = y;
	glutPostRedisplay();
}

void myMenu(int id) { // 팝업 메뉴 그리기
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

void initMenu(void) {	// 우클릭 시 팝업 메뉴
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

void reshape(int width, int height) { // 윈도우 크기 변경 시에도 객체 비율 고정을 위한 함수
	glViewport(0, 0, width, height); // 뷰포트 설정
	double wScale = (double)width / 500; // 너비 설정
	double hScale = (double)height / 500; // 높이 설정
	glMatrixMode(GL_PROJECTION); // 화면 위치 계산 및 설정
	glLoadIdentity(); // 단위 행렬로 초기화
	glOrtho(-wScale, wScale, -hScale, hScale, -1, 1); // 육면체의 가시부피 설정
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);					// GULT 초기화
	glutInitWindowSize(500, 500);			// 윈도우 크기
	glutInitWindowPosition(0, 0);			// 윈도우 위치
	glutCreateWindow("2020136129 최수연");	// 윈도우 생성
	glClearColor(1.0, 1.0, 1.0, 1.0);		// 배경색 설정
	initMenu();								// 팝업 메뉴 등록
	glutDisplayFunc(display);				// 디스플레이 콜백 등록
	glutReshapeFunc(reshape);				// 윈도우 화면 고정 콜백 등록
	glutKeyboardFunc(keyboard);				// 키보드 콜백 등록
	glutMouseFunc(mouseClick);				// 마우스 클릭 콜백 등록
	glutMotionFunc(mouseMotion);			// 마우스 모션 콜백 등록
	glutMainLoop();							// GLUT event processing loop.
	return 0;
}