#include <windows.h> 
#include <GL/glut.h> 
#include <math.h> 
void bresenhamsLine(int x1, int y1, int x2, int y2) { 
    if (x1 > x2) { 
        int tempX = x1; 
        int tempY = y1; 
        x1 = x2; 
        y1 = y2; 
        x2 = tempX; 
        y2 = tempY; 
    } 
    float m = (x2 - x1) == 0 ? 999 : (float)(y2 - y1) / (float)(x2 - x1); 
    int pk, x, y; 
    if (m >= 0 && m <= 1) { 
        int dx = x2 - x1; 
        int dy = y2 - y1; 
        pk = (2 * dy) - dx; 
        x = x1; 
        y = y1; 
        glBegin(GL_POINTS); 
        glColor3f(1.0f, 0.0f, 0.0f); 
        for (int i = 0; i < dx; i++) { 
            glVertex2f(x, y); 
            if (pk < 0) 
                pk = pk + 2 * dy; 
            else { 
                pk = pk + 2 * dy - 2 * dx; 
                y = y + 1; 
            } 
            x = x + 1; 
        } 
        glEnd(); 
    } 
    else if (m > 1) { 
        int dx = x2 - x1; 
        int dy = y2 - y1; 
        pk = (2 * dx) - dy; 
        x = x1; 
        y = y1; 
        glBegin(GL_POINTS); 
        glColor3f(1.0f, 0.0f, 0.0f); 
        for (int i = 0; i < dy; i++) { 
            glVertex2f(x, y); 
            if (pk < 0) 
                pk = pk + 2 * dx; 
            else { 
                pk = pk + 2 * dx - 2 * dy; 
                x = x + 1; 
            } 
            y = y + 1; 
        } 
        glEnd(); 
    } 
    else if (m < 0 && m >= -1) { 
        int dx = x2 - x1; 
        int dy = y1 - y2; 
        pk = (2 * dy) - dx; 
        x = x1; 
        y = y1; 
        glBegin(GL_POINTS); 
        glColor3f(1.0f, 0.0f, 0.0f); 
        for (int i = 0; i < dx; i++) { 
            glVertex2f(x, y); 
            if (pk < 0) 
                pk = pk + 2 * dy; 
            else { 
                pk = pk + 2 * dy - 2 * dx; 
                y = y - 1; 
            } 
            x = x + 1; 
        } 
        glEnd(); 
    } 
    else if (m < -1) { 
        int dx = x2 - x1; 
        int dy = y1 - y2; 
        pk = (2 * dx) - dy; 
        x = x1; 
        y = y1; 
        glBegin(GL_POINTS); 
        glColor3f(1.0f, 0.0f, 0.0f); 
        for (int i = 0; i < dy; i++) { 
            glVertex2f(x, y); 
            if (pk < 0) 
                pk = pk + 2 * dx; 
            else { 
                pk = pk + 2 * dx - 2 * dy; 
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
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity(); 
    glOrtho(-500.0, 500.0, -500.0, 500.0, -500.0, 500.0); 
    glMatrixMode(GL_MODELVIEW); 
    // --- Fill Star using 8 GL_POLYGON triangles --- 
    glColor3f(0.0f, 1.0f, 3.0f); //  color for fill 
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
    // --- Draw Bresenham's Outline --- 
    bresenhamsLine(0, 300, 100, 100); 
    bresenhamsLine(100, 100, 300, 0); 
    bresenhamsLine(300, 0, 100, -100); 
    bresenhamsLine(100, -100, 0, -300); 
    bresenhamsLine(0, -300, -100, -100); 
    bresenhamsLine(-100, -100, -300, 0); 
    bresenhamsLine(-300, 0, -100, 100); 
    bresenhamsLine(-100, 100, 0, 300); 
 
    glFlush(); 
} 
int main(int argc, char** argv) { 
    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
    glutInitWindowSize(500, 500); 
    glutInitWindowPosition(50, 50); 
    glutCreateWindow("Star - Bresenham Outline"); 
    glutDisplayFunc(display); 
    glutMainLoop(); 
    return 0; 
} 