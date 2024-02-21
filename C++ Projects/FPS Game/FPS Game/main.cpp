#include <GLUT/glut.h>

float angle = 0.0;

int px, py, pz, pa;

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void drawCube(int x, int y)
{
    glLoadIdentity();
    glTranslatef(x, y, -5.0);
    glRotatef(angle, 1.0, 1.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);
    glutWireCube(2.0);

}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for(int i = 0; i < 10; i++)
        drawCube(i, 0);
    glutSwapBuffers();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
}

void idle()
{
    angle += 0.5;
    if(angle > 360.0)
        angle -= 360.0;
    glutPostRedisplay();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Glut Vindel Test");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    init();
    glutMainLoop();
    return 0;
}
