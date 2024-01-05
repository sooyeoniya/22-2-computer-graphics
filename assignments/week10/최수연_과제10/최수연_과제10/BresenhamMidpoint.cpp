#include <stdio.h>
#include <gl/glut.h>
#include <math.h>

inline int abs(int k) { return (k >= 0) ? k : -k; }
inline int max(int i, int j) { return (i > j) ? i : j; }
inline int ROUND(double v) { return (int)(v + 0.5); }
inline double dist(double dx, double dy) { return sqrt(dx * dx + dy * dy); }
inline void swap(int* a, int* b) { int tmp = *a; *a = *b; *b = tmp; }

static int winW = 500, winH = 500; // 윈도우 크기
static int nGrid = 30; // 픽셀 개수
static double pixelW, pixelH; // 픽셀 하나의 크기
static int px, py, qx, qy;
static int mode = 0;

void draw2DGrid() { // 전체 화면 그리드 그리기
	glLineWidth(1); // line 두께: 1
	glBegin(GL_LINES);
	for (int i = 0; i <= nGrid; i++) {
		glVertex2d(i * pixelW, 0);
		glVertex2d(i * pixelW, winH);
		glVertex2d(0, i * pixelH);
		glVertex2d(winW, i * pixelH);
	}
	glEnd();
}
void drawPixel(GLint x, GLint y) { // 그리드 안에 픽셀 하나를 색칠함
	int xi = x * pixelW;
	int yi = y * pixelH;
	glRectd(xi, yi, xi + pixelW, yi + pixelH);
}
void lineBresenham(GLint x1, GLint y1, GLint x2, GLint y2);
void lineDDA(GLint x1, GLint y1, GLint x2, GLint y2);
void lineBasic(GLint x1, GLint y1, GLint x2, GLint y2);
void circleMidPoint(GLint radius);
void display() {
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5, 0.5, 0.5);
	draw2DGrid(); // 화소 그리드
	glColor3f(0, 0, 0); // Bresenham 선분
	switch (mode) {
	case 1: lineBasic(px / pixelW, py / pixelH, qx / pixelW, qy / pixelH);
			break;
	case 2: lineDDA(px / pixelW, py / pixelH, qx / pixelW, qy / pixelH);
			break;
	case 3: lineBresenham(px / pixelW, py / pixelH, qx / pixelW, qy / pixelH);
			break;
	case 4: int radius= ROUND(dist(px / pixelW - qx / pixelW, py / pixelH - qy / pixelH));
			circleMidPoint(radius);
			break;
	}
	glColor3f(1.0, 0.0, 1.0); // 원래의 선분
	glLineWidth(5); // 움직이는 분홍색 선 출력
	glBegin(GL_LINES);
	glVertex2f(px, py);
	glVertex2f(qx, qy);
	glEnd();
	glFlush();
}
void mouseClick(int button, int state, int x, int y) { // 마우스 클릭할 때는 px, py에 저장
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		px = x;
		py = winH - y;
	}
}
void mouseMotion(GLint x, GLint y) { // 마우스 움직일 때는 qx, qy에 저장
	qx = x;
	qy = (winH - y);
	glutPostRedisplay();
}
void lineBresenham(GLint x1, GLint y1, GLint x2, GLint y2) {
	int dX = abs(x2 - x1), dY = abs(y2 - y1);
	int p, const1, const2;
	int x, y;
	if (dX >= dY) {
		p = 2 * dY - dX;
		const1 = 2 * dY;
		const2 = 2 * (dY - dX);
		if (x1 < x2) { x = x1; y = y1; }
		else { x = x2; y = y2; x2 = x1; y2 = y1; }
		drawPixel(x, y);
		while (x < x2) {
			if (p < 0) p += const1;
			else {
				if (y < y2) { p += const2; y++; }
				else { p += const2; y--; }
			}
			x++;
			drawPixel(x, y);
		}
	}
	else {
		p = 2 * dX - dY;
		const1 = 2 * dX;
		const2 = 2 * (dX - dY);
		if (y1 < y2) { x = x1; y = y1; }
		else { x = x2; y = y2; x2 = x1; y2 = y1; }
		drawPixel(x, y);
		while (y < y2) {
			if (p < 0) p += const1;
			else {
				if (x > x2) { p += const2; x--; }
				else { p += const2; x++; }
			}
			y++;
			drawPixel(x, y);
		}
	}
}
void lineBasic(GLint x1, GLint y1, GLint x2, GLint y2) {
	double m = (double)(y2 - y1) / (x2 - x1);
	if (-1 <= m && m <= 1) {
		if ((x2 - x1) <= 0) { swap(&x1, &x2); swap(&y1, &y2); }
		for (int x = x1; x <= x2; x++) {
			double y = m * (x - x1) + y1;
			drawPixel(x, ROUND(y));
		}
	}
	else {
		if ((y2 - y1) <= 0) { swap(&x1, &x2); swap(&y1, &y2); }
		for (int y = y1; y <= y2; y++) {
			double x = (y - y1) / m + x1;
			drawPixel(ROUND(x), y);
		}
	}
}
void lineDDA(GLint x1, GLint y1, GLint x2, GLint y2) {
	int dX = abs(x2 - x1);
	int dY = abs(y2 - y1);
	int steps = max(dX, dY); // (dX > dY) ? dX : dY;
	double incX = (double)(x2 - x1) / steps;
	double incY = (double)(y2 - y1) / steps;
	double x = x1;
	double y = y1;
	for (int i = 0; i <= steps; i++, x += incX, y += incY)
		drawPixel(ROUND(x), ROUND(y));
}
void drawCirclePoint(int x, int y) {
	drawPixel(x + px / pixelW, y + py / pixelH);
	drawPixel(x + px / pixelW, -y + py / pixelH);
	drawPixel(-x + px / pixelW, y + py / pixelH);
	drawPixel(-x + px / pixelW, -y + py / pixelH);
	drawPixel(y + px / pixelW, x + py / pixelH);
	drawPixel(y + px / pixelW, -x + py / pixelH);
	drawPixel(-y + px / pixelW, x + py / pixelH);
	drawPixel(-y + px / pixelW, -x + py / pixelH);
}
void circleMidPoint(GLint radius) { // 중심이 (0, 0)이고 반지름이 R인 원
	int x = 0;
	int y = radius;
	int d = 1 - radius;
	drawCirclePoint(x, y);
	for (; y > x; x++) {
		if (d < 0)
			d = d + 2 * x + 3;
		else {
			d = d + 2 * (x - y) + 5;
			y = y - 1;
		}
		drawCirclePoint(x, y);
	}
}
void keyboard(unsigned char key, int x, int y) {
	if (key >= '0' && key <= '9')
		mode = key - '0';
	else if (key == 'q') exit(0);
	if(mode == 1) printf("mode 1: Basic Line Drawing\n");
	else if(mode ==2) printf("mode 2: DDA Line Drawing\n");
	else if(mode ==3) printf("mode 3: Bresenham Line Drawing\n");
	else if(mode ==4) printf("mode 4: Midpoint circle Drawing\n");
	glutPostRedisplay();
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(winW, winH);
	glutCreateWindow("Line Drawing");
	pixelW = winW / nGrid;
	pixelH = winH / nGrid;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, winW, 0, winH, -1, 1);

	glutDisplayFunc(display);
	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseMotion);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
	return 0;
}