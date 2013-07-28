#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>

#define pi 3.14159
const int window_w = 600, window_h = 600;

void init(void) {
    glClearColor(0.0,0.0,0.0,0.0);
    glShadeModel(GL_FLAT);
}

void display(void) {
    glColor3f(1.0,1.0,1.0);
    int num_segments = 72;
    double r = 100;
    glClear(GL_COLOR_BUFFER_BIT);
    for (int k = 0; k <= (window_h / r) + 2 * r; ++k) {
        for (int j = 0; j <= (window_w / r) + 2 * r; ++j) { 
            glBegin(GL_LINE_LOOP);
            for (int i = 0; i < num_segments; ++i) {
                float theta = 2.0 * pi * float(i) / num_segments;
                float x = ((j - 1)* r) + r * cosf(theta);
                float y = ((k - 1) * r ) + r * sinf(theta);
                glVertex2f( 100 + x, 100 + y);
            }
            glEnd();
        }
        glFlush();
    }
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
    glutInitWindowSize(window_w,window_h);
    glutInitWindowPosition(0,0);
    glutCreateWindow(argv[0]);

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
}
