#include "Robot.h"
#include <gl/glut.h>
#include "glk.h"

//static Mesh obj3D; 
static Robot robot; // Robot 클래스 객체 robot 생성
static bool bRobotRun = false;

void display() {
	glClearColor(0.8, 0.9, 0.8, 1.0); // 배경 색상 설정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 버퍼 초기화

	robot.draw(); 
	//obj3D.draw(80.0f, true); 
	glutSwapBuffers();
	glFlush();
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
		PrevX = x;  // 마우스의 x, y의 위치를 현재 위치로 변경
		PrevY = y;
	}
}
void mouseMotion(GLint x, GLint y) {
	glMatrixMode(GL_MODELVIEW); // 화면에 형상을 그린다면 GL_MODELVIEW 행렬을 곱해서 실제적 위치를 정한다.
	glRotated(x - PrevX, 0, -1, 0);
	glRotated(y - PrevY, -1, 0, 0); // 각각 움직인 x, y만큼 회전되도록 설정
	PrevX = x;
	PrevY = y; // 다시 motion이 동작한만큼 PrevX와 PrevY에 각각 값을 저장
	glutPostRedisplay(); // 현 윈도우가 재생되어야 함을 표시
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
	glutInitWindowSize(600, 600); // 윈도우 크기
	glutCreateWindow("RobotWorld"); // 윈도우 생성

	glutDisplayFunc(display); // 디스플레이 콜백 등록
	glutKeyboardFunc(keyboard); // 키보드 콜백 등록
	glutMouseFunc(mouseClick); // 마우스 클릭 콜백 등록
	glutMotionFunc(mouseMotion); // 마우스 모션 콜백 등록

	InitRendering(); // 조명값 설정
	keyboard('s', 0, 0);
	keyboard('l', 0, 0);
	// glFrontFace(GL_CW);

	glutMainLoop(); // GLUT event processing loop.
	return 0;
}