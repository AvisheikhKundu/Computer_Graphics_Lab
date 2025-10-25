#include <windows.h>
#include <GL/glut.h>
#include <math.h>

// Function to draw symmetric points
void drawCirclePoints(int xc, int yc, int x, int y) {
    glBegin(GL_POINTS);
    glVertex2f(xc + x, yc + y);
    glVertex2f(xc - x, yc + y);
    glVertex2f(xc + x, yc - y);
    glVertex2f(xc - x, yc - y);
    glVertex2f(xc + y, yc + x);
    glVertex2f(xc - y, yc + x);
    glVertex2f(xc + y, yc - x);
    glVertex2f(xc - y, yc - x);
    glEnd();
}

// Bresenham's (Midpoint) Circle Algorithm
void bresenhamCircle(int xc, int yc, int r) {
    int x = 0;
    int y = r;
    int d = 3 - (2 * r);
    glColor3f(1.0f, 0.0f, 0.0f); // Red color for border
    while (x <= y) {
        drawCirclePoints(xc, yc, x, y);
        if (d < 0)
            d = d + (4 * x) + 6;
        else {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

// Display function
void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-500, 500, -500, 500, -1, 1);

    // Fill the circle using GL_POLYGON
    glColor3f(0.0f, 1.0f, 4.0f); // Green fill
    glBegin(GL_POLYGON);
    int xc = 0, yc = 0, r = 200;
    for (int angle = 0; angle <= 360; angle++) {
        float rad = angle * 3.1416 / 180;
        glVertex2f(xc + r * cos(rad), yc + r * sin(rad));
    }
    glEnd();

    // Circle border using Bresenham's algorithm
    bresenhamCircle(0, 0, 200);
    glFlush();
}

// Main
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Circle - Bresenham's Algorithm");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}