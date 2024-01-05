#include <iostream>
#include <gl/glut.h>
#include <gl/freeglut.h>
using namespace std;
typedef struct myPoint { double x; double y; } Point2D;
float g_u1 = 0, g_u2 = 1;

// Cohen-Sutherland
enum Boundary { LEFT = 1, RIGHT = 2, BOTTOM = 6, TOP = 8 };
char Encode(Point2D p, Point2D min, Point2D max) {
    unsigned char code = 0x00;
    if (p.x < min.x) code = code | LEFT;
    if (p.x > max.x) code = code | RIGHT;
    if (p.y < min.y) code = code | BOTTOM;
    if (p.y > max.y) code = code | TOP;
    //printf("code: %u\n", code);
    return (code);
}
void SwapIfNeeded(char& c1, char& c2, Point2D& p, Point2D& q) {
    if (c1 == 0) {
        Point2D r = p; p = q; q = r;
        char tmp = c1; c1 = c2; c2 = tmp;
    }
}
inline bool Accept(char a, char b) { return (a | b) == 0; }
inline bool Reject(char a, char b) { return (a & b) != 0; }
inline void drawLine(Point2D p, Point2D q) {
    printf("\t절단후: (%4.2lf, %4.2lf)--(%4.2lf, %4.2lf)\n", p.x, p.y, q.x, q.y);
}
void clipLine_CS(Point2D min, Point2D max, Point2D p, Point2D q) {
    char code1, code2;
    bool done = false, draw = false;
    float m = 0;
    while (!done) {
        code1 = Encode(p, min, max);
        code2 = Encode(q, min, max);
        if (Accept(code1, code2)) {
            done = draw = true;
        }
        else if (Reject(code1, code2)) done = true;
        else {
            SwapIfNeeded(code1, code2, p, q);
            if (p.x != q.x) m = (q.y - p.y) / (q.x - p.x);
            if (code1 & LEFT) {
                p.y += (min.x - p.x) * m;
                p.x = min.x;
            }
            else if (code1 & RIGHT) {
                p.y += (max.x - p.x) * m;
                p.x = max.x;
            }
            else if (code1 & BOTTOM) {
                if (q.x != p.x) q.x += (min.y - p.y) / m;
                q.y = min.y;
            }
            else if (code1 & TOP) {
                if (q.x != p.x) q.x += (max.y - p.y) / m;
                q.y = max.y;
            }
        }
    }
    if (draw) drawLine(p, q);
}

// Liang Barsky
bool clipTest(float p, float q, float u1, float u2) {
    float r;
    bool result = true;
    if (p < 0) {           // 외부에서 내부로 들어감
        r = q / p;
        //printf("\nr<: %4.2lf\n", r);
        if (r > u2) result = false;
        else if (r > u1) {
            u1 = r;
            g_u1 = u1;
        }
    }
    else if (p > 0) {      // 내부에서 외부로 나감
        r = q / p;
        //printf("\nr>: %4.2lf\n", r);
        if (r < u1) result = false;
        else if (r < u2) {
            u2 = r;
            g_u2 = u2;
        }
    }
    else {                 // 수직 또는 수평선 (평행선)
        if (q < 0) result = false;
    }
    //printf("g_u1: %4.2lf\n", g_u1);
    //printf("g_u2: %4.2lf\n", g_u2);
    return result;
}
void clipLine_LB(Point2D min, Point2D max, Point2D p, Point2D q) {
    float dx = q.x - p.x, dy = q.y - p.y;
    if (clipTest(-dx, p.x - min.x, g_u1, g_u2)) {               // left
        if (clipTest(dx, max.x - p.x, g_u1, g_u2)) {            // right
            if (clipTest(-dy, p.y - min.y, g_u1, g_u2)) {       // lower
                if (clipTest(dy, max.y - p.y, g_u1, g_u2)) {    // upper
                    if (g_u2 < 1) {
                        q.x = p.x + g_u2 * dx;
                        q.y = p.y + g_u2 * dy;
                    }
                    if (g_u1 > 0) {
                        p.x = p.x + g_u1 * dx;
                        p.y = p.y + g_u1 * dy;
                    }
                }
            }
        }
    }
    if((g_u1 != 0) || (g_u2 != 1)) drawLine(p, q);
}
void lineClipTest(Point2D min, Point2D max, Point2D p, Point2D q) {
    g_u1 = 0;
    g_u2 = 1;
    printf("\n원선분 : (%4.2lf, %4.2lf), (%4.2lf, %4.2lf)\n", p.x, p.y, q.x, q.y);
    printf("clipLine_CS: ");
    clipLine_CS(min, max, p, q);
    printf("clipLine_LB: ");
    clipLine_LB(min, max, p, q);
    printf("\n");
}
int main(int argc, char** argv) {
    Point2D min = { -1, -1 };
    Point2D max = {  1,  1 };
    Point2D p[8] = {{   -2, 0 }, {   2,    0 },
                    { -0.3, 0 }, {   2,  1.5 },
                    {   -2, 0 }, { 0.5, -0.2 },
                    { -1.3, 0 }, {  -2,  1.5 }};
    lineClipTest(min, max, p[0], p[1]);
    lineClipTest(min, max, p[2], p[3]);
    lineClipTest(min, max, p[4], p[5]);
    lineClipTest(min, max, p[6], p[7]);
    getchar();
    return 0;
}