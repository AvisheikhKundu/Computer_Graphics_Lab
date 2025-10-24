// dda_shapes.c
#include <GL/glut.h>
#include <math.h>

// Function to plot a single pixel
void plotPixel(int x, int y) {
    glBegin(GL_POINTS);
        glVertex2i(x, y);
    glEnd();
}

// DDA Line Drawing Algorithm
void drawLineDDA(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    float steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);

    float xInc = dx / steps;
    float yInc = dy / steps;

    float x = x1;
    float y = y1;

    for (int i = 0; i <= steps; i++) {
        plotPixel(round(x), round(y));
        x += xInc;
        y += yInc;
    }
}

// Draw a square using 4 DDA lines
void drawSquare(int cx, int cy, int size) {
    int h = size / 2;
    int x1 = cx - h, y1 = cy - h;
    int x2 = cx + h, y2 = cy - h;
    int x3 = cx + h, y3 = cy + h;
    int x4 = cx - h, y4 = cy + h;

    drawLineDDA(x1, y1, x2, y2);
    drawLineDDA(x2, y2, x3, y3);
    drawLineDDA(x3, y3, x4, y4);
    drawLineDDA(x4, y4, x1, y1);
}

// Draw a triangle using DDA
void drawTriangle(int cx, int cy, int size) {
    int h = size;
    int x1 = cx, y1 = cy + h;
    int x2 = cx - h, y2 = cy - h;
    int x3 = cx + h, y3 = cy - h;

    drawLineDDA(x1, y1, x2, y2);
    drawLineDDA(x2, y2, x3, y3);
    drawLineDDA(x3, y3, x1, y1);
}

// Draw a star using 10 points connected by DDA
void drawStar(int cx, int cy, int r) {
    float angle, x[10], y[10];
    for (int i = 0; i < 10; i++) {
        angle = i * 36 * M_PI / 180.0; // 36° step
        if (i % 2 == 0) {
            x[i] = cx + r * cos(angle);
            y[i] = cy + r * sin(angle);
        } else {
            x[i] = cx + (r / 2.5) * cos(angle);
            y[i] = cy + (r / 2.5) * sin(angle);
        }
    }
    for (int i = 0; i < 10; i++)
        drawLineDDA(x[i], y[i], x[(i + 1) % 10], y[(i + 1) % 10]);
}

// Draw a polygon (hexagon example)
void drawPolygon(int cx, int cy, int r, int sides) {
    float angleStep = 2 * M_PI / sides;
    float xPrev = cx + r * cos(0);
    float yPrev = cy + r * sin(0);
    for (int i = 1; i <= sides; i++) {
        float x = cx + r * cos(i * angleStep);
        float y = cy + r * sin(i * angleStep);
        drawLineDDA(xPrev, yPrev, x, y);
        xPrev = x;
        yPrev = y;
    }
}

// Draw a circle using small DDA line segments
void drawCircle(int cx, int cy, int r) {
    int segments = 360; // smaller steps → smoother circle
    for (int i = 0; i < segments; i++) {
        float theta1 = i * M_PI / 180;
        float theta2 = (i + 1) * M_PI / 180;
        float x1 = cx + r * cos(theta1);
        float y1 = cy + r * sin(theta1);
        float x2 = cx + r * cos(theta2);
        float y2 = cy + r * sin(theta2);
        drawLineDDA(x1, y1, x2, y2);
    }
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(2.0f);

    // Square
    glColor3f(1, 0, 0);
    drawSquare(100, 400, 100);

    // Triangle
    glColor3f(0, 0, 1);
    drawTriangle(300, 400, 60);

    // Star
    glColor3f(0, 1, 0);
    drawStar(500, 400, 60);

    // Polygon (Hexagon)
    glColor3f(1, 0, 1);
    drawPolygon(200, 200, 60, 6);

    // Circle (approximation)
    glColor3f(1, 0.5, 0);
    drawCircle(400, 200, 60);

    glFlush();
}

// Initialization
void init() {
    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 600, 0, 600);
}

// Main function
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("DDA Shapes: Square, Triangle, Star, Polygon, Circle");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
