#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>

const int window_w = 800;
const int window_h = 800;

void init(void)
{
    glClearColor(0.0,0.0,0.0,0.0);
    glShadeModel(GL_FLAT);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,1.0,1.0);
    double theta = 0.2;
    double line_length, init_x = 0, init_y = window_w / 8.0;
    double current_x = init_x, current_y = init_y;

    current_x = window_w / 2.0;
    theta = 0.2;
    current_y = window_h / 2.0;
    for (line_length = 3; current_x <= window_w ; line_length *= 1.25) {
        double delta_x = line_length * cosf(theta);
        double delta_y = line_length * sinf(theta);
        glBegin(GL_LINES);
        glVertex2f(current_x, current_y);
        glVertex2f(current_x + delta_x, current_y + delta_y);
        glEnd();
        current_x += delta_x;
        current_y += delta_y;
        theta *= -1.2;
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
    glutInitWindowSize(window_w,window_h);
    glutInitWindowPosition(0,0);
    glutCreateWindow(argv[0]);

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
}
