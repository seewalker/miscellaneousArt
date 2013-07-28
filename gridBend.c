#include <GL/gl.h>
#include <GL/glut.h>

const int window_w = 400;
const int window_h = 400;

void init(void) {
    glClearColor(0.0,0.0,0.0,0.0);
    glShadeModel(GL_FLAT);
}

void display(void) {
    const int line_space = 20;
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    glColor3f(1.0,0.0,1.0);
    for (int count = 0; count <= (window_w / line_space); ++count) {
        glVertex2f(0.0, line_space * count);
        glVertex2f(window_w, line_space * count);
    }
    glColor3f(1.0,1.0,0.0);
    for (int count = 0; count <= (window_h / line_space); ++count) {
        glVertex2f(line_space * count, 0);
        glVertex2f(line_space * count, window_h);
    }
    glColor3f(0.0,1.0,1.0);
    for (int count = 0; count <= (window_h / line_space); ++count) {
        glVertex2f(0, line_space * count);
        glVertex2f((window_w - line_space * count), 0);
    }
    glEnd();
    glFlush();
}

void reshape(int w, int h) {
    glViewport(0,0,(GLsizei) w, (GLsizei) h);
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
