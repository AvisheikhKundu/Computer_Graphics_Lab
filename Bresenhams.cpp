#include <windows.h>
#include <GL/glut.h>
#include <math.h>

void bresenhamsLine(int x1, int y1, int x2, int y2) {
    if (x1 > x2) { int tx = x1, ty = y1; x1 = x2; y1 = y2; x2 = tx; y2 = ty; }
    float m = (x2 - x1) == 0 ? 999 : (float)(y2 - y1) / (float)(x2 - x1);
    int pk, x, y;
    if (m >= 0 && m <= 1) {
        int dx = x2 - x1, dy = y2 - y1; pk = 2 * dy - dx; x = x1; y = y1;
        glBegin(GL_POINTS); glColor3f(1, 0, 0);
        for (int i = 0;i < dx;i++) { glVertex2f(x, y); if (pk < 0) pk += 2 * dy; else { pk += 2 * dy - 2 * dx; y++; } x++; }
        glEnd();
    }
    else if (m > 1) {
        int dx = x2 - x1, dy = y2 - y1; pk = 2 * dx - dy; x = x1; y = y1;
        glBegin(GL_POINTS); glColor3f(1, 0, 0);
        for (int i = 0;i < dy;i++) { glVertex2f(x, y); if (pk < 0) pk += 2 * dx; else { pk += 2 * dx - 2 * dy; x++; } y++; }
        glEnd();
    }
    else if (m < 0 && m >= -1) {
        int dx = x2 - x1, dy = y1 - y2; pk = 2 * dy - dx; x = x1; y = y1;
        glBegin(GL_POINTS); glColor3f(1, 0, 0);
        for (int i = 0;i < dx;i++) { glVertex2f(x, y); if (pk < 0) pk += 2 * dy; else { pk += 2 * dy - 2 * dx; y--; } x++; }
        glEnd();
    }
    else if (m < -1) {
        int dx = x2 - x1, dy = y1 - y2; pk = 2 * dx - dy; x = x1; y = y1;
        glBegin(GL_POINTS); glColor3f(1, 0, 0);
        for (int i = 0;i < dy;i++) { glVertex2f(x, y); if (pk < 0) pk += 2 * dx; else { pk += 2 * dx - 2 * dy; x++; } y--; }
        glEnd();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 1, 0);
    glBegin(GL_POLYGON);
    glVertex2f(0, 150);
    glVertex2f(150, 0);
    glVertex2f(0, -150);
    glVertex2f(-150, 0);
    glEnd();

    bresenhamsLine(0, 150, 150, 0);
    bresenhamsLine(150, 0, 0, -150);
    bresenhamsLine(0, -150, -150, 0);
    bresenhamsLine(-150, 0, 0, 150);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Diamond - Bresenham");
    glClearColor(0, 0, 0, 1);
    glOrtho(-300, 300, -300, 300, -1, 1);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
