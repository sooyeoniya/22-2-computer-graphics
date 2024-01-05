#include <stdio.h>
#include <GL/glut.h>

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);

    /*최*/
    glBegin(GL_POLYGON);
    glVertex2f(-0.05, 0.5);
    glVertex2f(-0.05, 0.25);
    glVertex2f(0.05, 0.25);
    glVertex2f(0.05, 0.5);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-0.3, 0.3);
    glVertex2f(-0.3, 0.2);
    glVertex2f(0.3, 0.2);
    glVertex2f(0.3, 0.3);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-0.07, 0.27);
    glVertex2f(-0.3, 0.07);
    glVertex2f(-0.23, 0.0);
    glVertex2f(0.0, 0.2);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0.0, 0.2);
    glVertex2f(0.23, 0.0);
    glVertex2f(0.3, 0.07);
    glVertex2f(0.07, 0.27);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-0.05, 0.1);
    glVertex2f(-0.05, -0.15);
    glVertex2f(0.05, -0.15);
    glVertex2f(0.05, 0.1);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-0.3, -0.1);
    glVertex2f(-0.3, -0.2);
    glVertex2f(0.3, -0.2);
    glVertex2f(0.3, -0.1);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0.3, 0.4);
    glVertex2f(0.3, -0.28);
    glVertex2f(0.4, -0.28);
    glVertex2f(0.4, 0.4);
    glEnd();

    glFinish();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(200, 200);
    glutCreateWindow("최수연_과제3.4");
    glutDisplayFunc(MyDisplay);
    glutMainLoop();
    return 0;
}