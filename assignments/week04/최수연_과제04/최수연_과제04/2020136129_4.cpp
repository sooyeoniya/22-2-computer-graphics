#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <GL/glut.h>

static int objNum = 0;
static bool bAuto = true;

void MyNameDisplay() {
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

void SierpinskiDisplay() {
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

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    switch (objNum) {
    case 0: glutWireCube(1); break;
    case 1: glutWireSphere(0.8, 16, 10); break;
    case 2: glutWireCone(0.8, 1, 20, 10); break;
    case 3: glutWireTorus(0.1, 0.8, 10, 20); break;
    case 4: glutWireTetrahedron(); break;
    case 5: glutWireIcosahedron(); break;
    case 6: glutWireTeapot(0.6); break;
    case 7: MyNameDisplay(); break;
    case 8: SierpinskiDisplay(); break;
    }
    glFlush();
}
void myTimer(int Value) {
    glutPostRedisplay();
    if (bAuto) {
        objNum = (objNum + 1) % 9;
        glutTimerFunc(500, myTimer, 1);
    }
}
void keyboard(unsigned char key, int x, int y) {
    if (key >= '0' && key <= '8') {
        objNum = key - '0';
        bAuto = false;
    }
    else if (key == 'i') {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }
    else if (key == 'a') {
        bAuto = !bAuto;
        if (bAuto) glutTimerFunc(500, myTimer, 1);
    }
    else if (key == 'q') exit(0);
    glutPostRedisplay();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    double wScale = (double)width / 500;
    double hScale = (double)height / 500;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-wScale, wScale, -hScale, hScale, -1, 1);
}

static int PrevX, PrevY;

void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        PrevX = x;
        PrevY = y;
    }
}

void mouseMotion(GLint x, GLint y) {
    glMatrixMode(GL_MODELVIEW);
    glRotated(x - PrevX, 0, 1, 0);
    glRotated(y - PrevX, 1, 0, 0);
    PrevX = x;
    PrevY = y;
    glutPostRedisplay();
}

void myMenu(int id) {
    if (id >= 0 && id <= 8)
        keyboard(id + '0', 0, 0);
    else if (id == 9) exit(0);
}

void initMenu() {
    GLint MyMainMenuID = glutCreateMenu(myMenu);
    glutAddMenuEntry("Draw WireCube", 0);
    glutAddMenuEntry("Draw WireSphere", 1);
    glutAddMenuEntry("Draw WireTorus", 2);
    glutAddMenuEntry("Draw WireCone", 3);
    glutAddMenuEntry("Draw WireTetrahedron", 4);
    glutAddMenuEntry("Draw Wirelcosahdron", 5);
    glutAddMenuEntry("Draw WireTeapot", 6);
    glutAddMenuEntry("Draw MyName", 7);
    glutAddMenuEntry("Draw Sierpinski Gasket", 8);
    glutAddMenuEntry("Exit", 9);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("2020136129 최수연");
    initMenu();
    glClearColor(1.0, 1.0, 1.0, 1.0);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouseClick);
    glutMotionFunc(mouseMotion);
    glutTimerFunc(500, myTimer, 1);
    glutMainLoop();
    return 0;
}