#pragma once
#include <stdio.h>
#include <memory.h>
#include <gl/glut.h>

#define _USE_MATH_DEFINES // M_PI 등을 사용하기 위함
#include <math.h>
#define SIN(x) sin(x*M_PI / 180.) // degree 각을 이용한 sin 함수
#define COS(x) cos(x*M_PI / 180.) // degree 각을 이용한 cos 함수

// 변환행렬 생성
inline void glkMatSet(double* m,
	double m00, double m01, double m02, double m03,
	double m10, double m11, double m12, double m13,
	double m20, double m21, double m22, double m23,
	double m30, double m31, double m32, double m33)
{
	double mat[16] = { m00,m01,m02,m03, m10,m11,m12,m13, m20,m21,m22,m23, m30,m31,m32,m33 };
	memcpy(m, mat, sizeof(double) * 16); // mat를 m에 복사
}

// 변환행렬 곱하기(m1 *= m2)
inline void glkMatMult(double* m1, double* m2)
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

// 행렬 출력
inline void glkMatPrint(double* m) {
	for (int i = 0; i < 4; i++) {
		printf("\t[");
		for (int j = 0; j < 4; j++)
			printf("%6.2f", m[i * 4 + j]);
		printf(" ]\n");
	}
	printf("\n");
}

inline void glkMatIdentity(double* m) {
	glkMatSet(m, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
} // 항등행렬

inline void glkMatTrans(double* m, double tx, double ty, double tz) {
	glkMatSet(m, 1, 0, 0, tx, 0, 1, 0, ty, 0, 0, 1, tz, 0, 0, 0, 1);
} // 이동

inline void glkMatScale(double* m, double sx, double sy, double sz) {
	glkMatSet(m, sx, 0, 0, 0, 0, sy, 0, 0, 0, 0, sz, 0, 0, 0, 0, 1);
} // 신축

inline void glkMatRotateZ(double* m, double a)
{
	glkMatSet(m, COS(a), -SIN(a), 0, 0, SIN(a), COS(a), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
} // Z축 중심 회전

inline void glkMatRotateY(double* m, double a)
{
	glkMatSet(m, 1, 0, 0, 0, 0, COS(a), -SIN(a), 0, 0, -SIN(a), COS(a), 0, 0, 0, 0, 1);
} // Y축 중심 회전

inline void glkMatRotateX(double* m, double a)
{
	glkMatSet(m, COS(a), 0, SIN(a), 0, 0, 1, 0, 0, -SIN(a), 0, COS(a), 0, 0, 0, 0, 1);
} // X축 중심 회전

inline void glkMatShareX(double* m, double dy, double dz) {
	glkMatSet(m, 1, dy, dz, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
} // X축 방향 밀림

inline void glkMatShareY(double* m, double dx, double dz) {
	glkMatSet(m, dx, 1, dz, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
} // Y축 방향 밀림

inline void glkMatShareZ(double* m, double dx, double dy) {
	glkMatSet(m, dx, dy, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
} // Z축 방향 밀림

// 정점의 변환함수 [q] = [M] [p]
inline void glkTransform(double* m, double* p, double* q)
{
	q[0] = q[1] = q[2] = q[3] = 0;
	for (int i = 0; i < 4; i++) {
		q[0] += m[i] * p[i];
		q[1] += m[i + 4] * p[i];
		q[2] += m[i + 8] * p[i];
		q[3] += m[i + 12] * p[i];
	}
}

// 간단한 그리기 함수들 : 선분, 삼각형, 좌표축
// 선분
inline void glkLine(double x1, double y1, double z1, double x2, double y2, double z2)
{
	glBegin(GL_LINES);
	glVertex3d(x1, y1, z1);
	glVertex3d(x2, y2, z2);
	glEnd();
}
// 삼각형
inline void glkTriangle4d(double* p) {
	glBegin(GL_TRIANGLES);
	glVertex4dv(p);
	glVertex4dv(p + 4);
	glVertex4dv(p + 8);
	glEnd();
}
// 좌표계
inline void glkCoord() {
	glBegin(GL_LINES);
	glColor3d(1, 0, 0); glVertex3d(-0.1, 0, 0); glVertex3d(1, 0, 0);
	glColor3d(0, 1, 0); glVertex3d(0, -0.1, 0); glVertex3d(0, 1, 0);
	glColor3d(0, 0, 1); glVertex3d(0, 0, -0.1); glVertex3d(0, 0, 1);
	glEnd();
}

extern void glkString(const char* s);
extern void glkSetColor(float r, float g, float b, float a);
extern void glkDrawCoord(double len);
extern void glkMessage(int line_no, const char* message);
extern void glkGridPlaneChess();

#define FILTER_ASE "ASE 3D data (*.ase)\0*.ase\0A11 (*.*)\0*.*\0"
#define FILTER_BVH "BVH Motion Data (*.bvh)\0*.bvh\0A11 (*.*)\0*.*\0"
#ifdef WIN32
extern char* glkFileDlg(const char*);
#endif