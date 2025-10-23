#include <windows.h>
#include <GL/glut.h>
#include <cstdlib>

void bresenhamsLine(int x1, int y1, int x2, int y2) {
    float m = (float)(y2 - y1) / (float)(x2 - x1);
    int pk, x, y;

    if (m >= 0 && m <= 1) {
        pk = (2 * (y2 - y1)) - (x2 - x1);
        x = x1;
        y = y1;
        glBegin(GL_POINTS);
        glColor3f(1.0f, 0.0f, 0.0f);
        for (int i = 0; i < x2 - x1; i++) {
            glVertex2f((float)x, (float)y);
            if (pk < 0) {
                pk = pk + 2 * (y2 - y1);
            }
            else {
                pk = pk + 2 * (y2 - y1) - 2 * (x2 - x1);
                y = y + 1;
            }
            x = x + 1;
        }
        glEnd();
    }
    else if (m > 1) {
        pk = (2 * (x2 - x1)) - (y2 - y1);
        x = x1;
        y = y1;
        glBegin(GL_POINTS);
        glColor3f(0.0f, 1.0f, 0.0f);
        for (int i = 0; i < y2 - y1; i++) {
            glVertex2f((float)x, (float)y);
            if (pk < 0) {
                pk = pk + 2 * (x2 - x1);
            }
            else {
                pk = pk + 2 * (x2 - x1) - 2 * (y2 - y1);
                x = x + 1;
            }
            y = y + 1;
        }
        glEnd();
    }
    else if (m < 0 && m >= -1) {
        pk = (2 * (y1 - y2)) + (x2 - x1);
        x = x1;
        y = y1;
        glBegin(GL_POINTS);
        glColor3f(0.0f, 0.0f, 1.0f);
        for (int i = 0; i < abs(x2 - x1); i++) {
            glVertex2f((float)x, (float)y);
            if (pk < 0) {
                pk = pk + 2 * (y1 - y2);
            }
            else {
                pk = pk + 2 * (y1 - y2) + 2 * (x2 - x1);
                y = y - 1;
            }
            x = x + 1;
        }
        glEnd();
    }
    else if (m < -1) {
        pk = (2 * (x1 - x2)) + (y2 - y1);
        x = x1;
        y = y1;
        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 0.0f);
        for (int i = 0; i < abs(y2 - y1); i++) {
            glVertex2f((float)x, (float)y);
            if (pk < 0) {
                pk = pk + 2 * (x1 - x2);
            }
            else {
                pk = pk + 2 * (x1 - x2) + 2 * (y2 - y1);
                x = x + 1;
            }
            y = y - 1;
        }
        glEnd();
    }
}

void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Reset projection and modelview matrices so repeated calls to display()
    // won't accumulate additional transforms (which caused the diamond to shrink
    // on every redisplay/click).
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-500.0, 500.0, -500.0, 500.0, -500.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // (reshape is defined at file scope below)
    bresenhamsLine(-400, 0, 0, 400);
    bresenhamsLine(0, 400, 400, 0);
    bresenhamsLine(-400, 0, 0, -400);
    bresenhamsLine(0, -400, 400, 0);

    glFlush();
}

// Reshape callback: set viewport and projection when the window size changes.
void reshape(int w, int h) {
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Keep a fixed orthographic volume so the drawn coordinates map consistently.
    glOrtho(-500.0, 500.0, -500.0, 500.0, -500.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 500);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Applying Bresenham's Line Drawing Algorithm");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}