#include "glk.h"
#ifdef XXX
#include <stdio.h>
#include <memory.h>
#include <gl/glut.h>
// (x1,y1,z1)���� (x2,y2,z2)���� ���� �׸���
void glkLine(double x1, double y1, double z1, double x2, double y2, double z2)
{
	glBegin(GL_LINES);
	glVertex3d(x1, y1, z1);
	glVertex3d(x2, y2, z2);
	glEnd();
}
// ���� ��ǥ��� ��Ÿ�� �ﰢ�� ���, �迭 p�� ���̴� 12 �̻�
void glkTriangle4d(double* p) {
	glBegin(GL_TRIANGLES);
	glVertex4dv(p);
	glVertex4dv(p + 4);
	glVertex4dv(p + 8);
	glEnd();
}
// ������ǥ����� ���� ��ȯ
// �� p�� ���� ��ȯ m�� �����Ͽ� �� q�� ����. [q] = [M] [p]
void glkTransform(double* m, double* p, double* q)
{
	q[0] = q[1] = q[2] = q[3] = 0;
	for (int i = 0; i < 4; i++) {
		q[0] += m[i] * p[i];
		q[1] += m[i + 4] * p[i];
		q[2] += m[i + 8] * p[i];
		q[3] += m[i + 12] * p[i];
	}
}
// ������ǥ�迡�� ��ȯ��� �ʱ�ȭ, ��� m = 4*4
void glkMatSet(double* m,
	double m00, double m01, double m02, double m03,
	double m10, double m11, double m12, double m13,
	double m20, double m21, double m22, double m23,
	double m30, double m31, double m32, double m33)
{
	double mat[16] = { m00,m01,m02,m03, m10,m11,m12,m13, m20,m21,m22,m23, m30,m31,m32,m33 };
	memcpy(m, mat, sizeof(double) * 16);
} // ��ȯ��� ����
// ������ǥ�迡�� ��ȯ ���ϱ�, [m1] = [m1] * [m2]
void glkMatMult(double* m1, double* m2)
{
	double n[16];
	for (int k = 0; k < 16; k++) {
		n[k] = 0;
		double* p = m1 + (k / 4) * 4;
		double* q = m2 + (k % 4);
		for (int i = 0; i < 4; i++)
			n[k] += p[i] * q[i * 4];
	}
	memcpy(m1, n, sizeof(double) * 16);

}
// ��ȯ����� �ܼ� ȭ�鿡 ���
void glkMatPrint(double* m) {
	for (int i = 0; i < 4; i++) {
		printf("\t[");
		for (int j = 0; j < 4; j++)
			printf("%6.2f", m[i * 4 + j]);
		printf(" ]\n");
	}
	printf("\n");
}
// Identity ��� �����
void glkMatIdentity(double* m) {
	glkMatSet(m, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
}
// �̵���ȯ ��� �����
void glkMatTrans(double* m, double tx, double ty, double tz) {
	glkMatSet(m, 1, 0, 0, tx, 0, 1, 0, ty, 0, 0, 1, tz, 0, 0, 0, 1);
}
// ���ຯȯ ��� �����
void glkMatScale(double* m, double sx, double sy, double sz) {
	glkMatSet(m, sx, 0, 0, 0, 0, sy, 0, 0, 0, 0, sz, 0, 0, 0, 0, 1);
}

#define _USE_MATH_DEFINES // M_PI ���� ����ϱ� ����, math.h ���Զ��� ���� �־�� ��
#include <math.h>
#define SIN(x) sin(x*M_PI / 180.) // degree ���� �̿��� sin �Լ�
#define COS(x) cos(x*M_PI / 180.) // degree ���� �̿��� cos �Լ�

void glkMatRotateZ(double* m, double a)
{
	glkMatSet(m, COS(a), -SIN(a), 0, 0, SIN(a), COS(a), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
} // Z�� �߽� ȸ��

void glkMatRotateY(double* m, double a)
{
	glkMatSet(m, 1, 0, 0, 0, 0, COS(a), -SIN(a), 0, 0, -SIN(a), COS(a), 0, 0, 0, 0, 1);
} // Y�� �߽� ȸ��

void glkMatRotateX(double* m, double a)
{
	glkMatSet(m, COS(a), 0, SIN(a), 0, 0, 1, 0, 0, -SIN(a), 0, COS(a), 0, 0, 0, 0, 1);
} // X�� �߽� ȸ��

void glkMatShareX(double* m, double dy, double dz) {
	glkMatSet(m, 1, dy, dz, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
} // X�� ���� �и�

void glkMatShareY(double* m, double dx, double dz) {
	glkMatSet(m, dx, 1, dz, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
} // Y�� ���� �и�

void glkMatShareZ(double* m, double dx, double dy) {
	glkMatSet(m, dx, dy, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
} // Z�� ���� �и�

#endif
//====================================================================
// GLUT�� �̿��� ���ڿ� ���
#include <string.h>
void glkString(const char* s) { // � ���ڿ��� ȭ�鿡 �׸�
	unsigned int i;
	for (i = 0; i < strlen(s); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
}
// ������ ���� ����
void glkSetColor(float r, float g, float b, float a) {
	float color[4] = { r, g, b, a };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color);
}
// ��ǥ�� �׸���. �������� +x(red), +y(blue), +z(gray)�� ���� len�� ����
void glkDrawCoord(double len) {
	glDisable(GL_LIGHTING); // ���� ��� ����
	glColor3f(1.0f, 0, 0);
	glkLine(0, 0, 0, len, 0, 0); // RED ==> +x axis
	glRasterPos3f(len, 0, 0);
	glkString("x");

	glColor3f(0, 1.0, 0);
	glkLine(0, 0, 0, 0, len, 0);  // GREEN ==> +y axis
	glRasterPos3f(0, len, 0);
	glkString("y");

	glColor3f(0, 0, 1.0f);
	glkLine(0, 0, 0, 0, 0, -len);  // BLUE ==> +z axis
	glRasterPos3f(0, 0, -len);
	glkString("z");
	glEnable(GL_LIGHTING); // ���� ��� ����
}

void glkMessage(int line_no, const char* message) {}
void glkGridPlaneChess() {}