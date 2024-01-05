#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <GL/glut.h>
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    GLfloat vertices[3][2] = { {-0.9, -0.9}, {0.9, -0.9}, {0, 0.9} };
    GLfloat p[2] = { 0.3, 0.1 };

    glBegin(GL_POINTS);
    for (int k = 0; k < 500000; k++) {
        int v = rand() % 3;
        p[0] = (p[0] + vertices[v][0]) / 2.0;

        p[1] = (p[1] + vertices[v][1]) / 2.0;
        glVertex2fv(p);
    }
    glEnd();
    glFinish();
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("최수연_과제3.5");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}