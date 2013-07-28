#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#define pi 3.14159
#define e 2.71828

const double window_w = 800, window_h = 600;

void init(void) {
    glClearColor(0.0,0.0,0.0,0.0);
    glShadeModel(GL_FLAT);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    double theta = 0.2, line_length = 25;
    double current_x = 0.0, current_y = window_h / 2.0;
    double i = 4.0;
    int count = 0;
    while(current_x < window_w && count < 200) {
        theta = (pi / 2.0) / (pow(e,i));
        if (count % 2 == 0) { theta *= -1; }
        double delta_x = line_length * cosf(theta);
        double delta_y = line_length * sinf(theta);
        glBegin(GL_LINES);
        glVertex2f(current_x, current_y);
        glVertex2f(current_x + delta_x, current_y + delta_y);
        glEnd();
        current_x += delta_x;
        current_y += delta_y;
        i *= 0.7;
        ++count;
        line_length *= 1.15;
    }
    glFlush();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,(GLdouble) w, 0.0, (GLdouble) h);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(window_w, window_h);
    glutInitWindowPosition(0,0);
    glutCreateWindow(argv[0]);

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
}
