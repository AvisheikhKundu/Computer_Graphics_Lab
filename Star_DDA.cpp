#include <windows.h>
#include <GL/glut.h>
#include <math.h>

void ddaLine(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float xInc = dx / (float)steps;
    float yInc = dy / (float)steps;
    float x = x1, y = y1;
    glBegin(GL_POINTS);
    glColor3f(1.0f, 0.0f, 0.0f);
    for (int i = 0; i <= steps; i++) {
        glVertex2f(x, y);
        x += xInc;
        y += yInc;
    }
    glEnd();
}

void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-500.0, 500.0, -500.0, 500.0, -500.0, 500.0);
    glMatrixMode(GL_MODELVIEW);

    // --- Fill Star using 8 GL_POLYGON triangles ---
    glColor3f(0.0f, 1.0f, 0.0f); // Green color for fill
    glBegin(GL_POLYGON);
    glVertex2f(0, 0);
    glVertex2f(0, 300);
    glVertex2f(100, 100);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0, 0);
    glVertex2f(100, 100);
    glVertex2f(300, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0, 0);
    glVertex2f(300, 0);
    glVertex2f(100, -100);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0, 0);
    glVertex2f(100, -100);
    glVertex2f(0, -300);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0, 0);
    glVertex2f(0, -300);
    glVertex2f(-100, -100);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0, 0);
    glVertex2f(-100, -100);
    glVertex2f(-300, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0, 0);
    glVertex2f(-300, 0);
    glVertex2f(-100, 100);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0, 0);
    glVertex2f(-100, 100);
    glVertex2f(0, 300);
    glEnd();

    // --- Draw DDA Outline ---
    ddaLine(0, 300, 100, 100);
    ddaLine(100, 100, 300, 0);
    ddaLine(300, 0, 100, -100);
    ddaLine(100, -100, 0, -300);
    ddaLine(0, -300, -100, -100);
    ddaLine(-100, -100, -300, 0);
    ddaLine(-300, 0, -100, 100);
    ddaLine(-100, 100, 0, 300);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Star - DDA Outline");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
