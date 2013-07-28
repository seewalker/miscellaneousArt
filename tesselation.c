#include <GL/gl.h>
#include <GL/glut.h>

/* Hexagons are drawn in proportions such that the negative space between them 
 * consists of squares. */
 
#define INV_SQRT_TWO 0.70710678118
const double hex_scale = 50.0;
const double hex_width = (hex_scale * (1.0 + 2.0 * INV_SQRT_TWO));
const double hex_height = hex_scale * (2.0 * INV_SQRT_TWO);
const double num_horiz_hex = 5;
const double num_vert_hex = 5;
const int WINDOW_W  = (num_horiz_hex * hex_width) + 1;
const int WINDOW_H = (num_vert_hex * hex_height) + 1;

void init(void) {
  glClearColor(0.0,0.0,0.0,0.0);
  glShadeModel(GL_FLAT);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,1.0,1.0);

    for (int i = 0; hex_height * (i + 1) < WINDOW_H; ++i) {
        for (int j = 0; hex_width * (j + 1) < WINDOW_W; ++j) {
            if ((i + j) % 3 == 0) { glColor3f(0.0,1.0,1.0); }
            else if ((i + j) % 3 == 1) { glColor3f(1.0,1.0,0.0); }
            else { glColor3f(1.0,0.0,1.0); }
            glBegin(GL_POLYGON);
            glVertex2f(j * hex_width + (hex_scale * 0), 
                       i * hex_height + (hex_scale * INV_SQRT_TWO));
            glVertex2f(j * hex_width + (hex_scale * INV_SQRT_TWO), 
                       i * hex_height + (hex_scale * 2 * INV_SQRT_TWO));
            glVertex2f(j * hex_width + (hex_scale * (1 + INV_SQRT_TWO)), 
                       i * hex_height + (hex_scale * 2 * INV_SQRT_TWO));
            glVertex2f(j * hex_width + (hex_scale * (1 + 2 * INV_SQRT_TWO)), 
                       i * hex_height + (hex_scale * INV_SQRT_TWO));
            glVertex2f(j * hex_width + (hex_scale * (1 + INV_SQRT_TWO)), 
                       i * hex_height + (hex_scale * 0));
            glVertex2f(j * hex_width + (hex_scale * INV_SQRT_TWO), 
                       i * hex_height + (hex_scale * 0));
            glEnd();
        }
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
    glutInitWindowSize(WINDOW_W ,WINDOW_H);
    glutInitWindowPosition(0,0);
    glutCreateWindow(argv[0]);

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
}
