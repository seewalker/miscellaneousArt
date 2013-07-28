#include <GL/gl.h>
#include <GL/glut.h>
#include <cstdlib>
#include <math.h>

//cpp is an appropriate file extension because the bool type is present.
const double angle = 0.20;
const double window_s = 600;
const double init_length = 0.5 * window_s;
const double iteration_ratio = 0.85;
const double height_ratio = 0.5;
const double pi_over_two_radians = 1.57079632679;
const size_t depth_max = 2;

void init(void) {
  glClearColor(0.0,0.0,0.0,0.0);
  glShadeModel(GL_FLAT);
}

void colorify(bool mode, size_t depth) {
  const int period = 6;
  if (mode == 0) {
        if      (depth % period == 0) { glColor3f(1.0,0.0,0.0); }
        else if (depth % period == 1) { glColor3f(0.0,1.0,0.0); } 
        else if (depth % period == 2) { glColor3f(0.0,0.0,1.0); }
        else if (depth % period == 3) { glColor3f(1.0,1.0,0.0); }
        else if (depth % period == 4) { glColor3f(1.0,0.0,1.0); }
        else                          { glColor3f(0.0,1.0,1.0); }
  }
    else {
        if      (depth % period == 0) { glColor3f(0.0,1.0,1.0); }
        else if (depth % period == 1) { glColor3f(1.0,0.0,1.0); }
        else if (depth % period == 2) { glColor3f(1.0,1.0,0.0); }
        else if (depth % period == 3) { glColor3f(0.0,0.0,1.0); }
        else if (depth % period == 4) { glColor3f(0.0,1.0,0.0); }
        else                          { glColor3f(1.0,0.0,0.0); }
    }
}
void draw_triangle_l(size_t depth, double l_vertex_x, double l_vertex_y, double angle, bool mode) {

  if (depth < 32) {
      double edge_length = init_length * pow(iteration_ratio, depth);
      double horiz_adjust = edge_length * height_ratio * cos(depth * angle + pi_over_two_radians);
      double vert_adjust = edge_length * height_ratio * sin(depth * angle + pi_over_two_radians);
      double r_vertex_x = l_vertex_x + cos(depth * angle) * edge_length;
      double r_vertex_y = l_vertex_y + sin(depth * angle) * edge_length;
      double mid_vertex_x = 0.5 * (l_vertex_x + r_vertex_x);
      double mid_vertex_y = 0.5 * (l_vertex_y + r_vertex_y);
      colorify(mode, depth);
      glBegin(GL_POLYGON);
      glVertex2f(l_vertex_x, l_vertex_y);
      glVertex2f(r_vertex_x, r_vertex_y);
      glVertex2f(mid_vertex_x + horiz_adjust, mid_vertex_y + vert_adjust);
      glEnd();

      draw_triangle_l(++depth, l_vertex_x, l_vertex_y, angle, mode);
    }
}


  void draw_triangle_r(size_t depth, double r_vertex_x, double r_vertex_y, double angle, bool mode) {
  if (depth < 32) {
      double edge_length = init_length * pow(iteration_ratio, depth);
      double horiz_adjust = edge_length * height_ratio * cos(depth * angle + pi_over_two_radians);
      double vert_adjust = edge_length * height_ratio * sin(depth * angle + pi_over_two_radians);
      double l_vertex_x = r_vertex_x - cos(depth * angle) * edge_length;
      double l_vertex_y = r_vertex_y - sin(depth * angle) * edge_length;
      double mid_vertex_x = 0.5 * (l_vertex_x + r_vertex_x);
      double mid_vertex_y = 0.5 * (l_vertex_y + r_vertex_y);

      colorify(mode, depth);
      glBegin(GL_POLYGON);
      glVertex2f(l_vertex_x, l_vertex_y);
      glVertex2f(r_vertex_x, r_vertex_y);
      glVertex2f(mid_vertex_x + horiz_adjust, mid_vertex_y + vert_adjust);
      glEnd();

      draw_triangle_r(++depth, r_vertex_x, r_vertex_y, angle, mode);
    }
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    draw_triangle_l(0, 0.5 * window_s, 0.5 * window_s, angle, 0);
    draw_triangle_r(0, 0.5 * window_s, 0.5 * window_s, angle, 1);
    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,(GLdouble) w, 0.0, (GLdouble) h);
}

void processMouse(int button, int state, int x, int y)
{
    glClear(GL_COLOR_BUFFER_BIT);
    if (state == GLUT_DOWN) {
        draw_triangle_l(0, 0.5 * window_s, 0.5 * window_s, angle, 1); 
        draw_triangle_r(0, 0.5 * window_s, 0.5 * window_s, angle, 0); 
    }
    else {
        display();
    }
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(window_s,window_s);
    glutInitWindowPosition(0,0);
    glutCreateWindow(argv[1]);

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(processMouse);
    glutMainLoop();
}
