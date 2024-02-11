#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <gl/glut.h>
#endif

#include <iostream>

void init()
{
    glClearColor(0.3, 0.3, 0.3, 0);
    gluOrtho2D(0, 512, 512, 0);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutSwapBuffers();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(512, 512);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("VindelEngien");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
