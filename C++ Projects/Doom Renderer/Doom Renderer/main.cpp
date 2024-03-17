#include <iostream>
#include <GLUT/glut.h>

#define res 1
#define SW 160*res
#define SH 120*res
#define SW2 (SW/2)
#define SH2 (SH/2)
#define pixelScale 4/res
#define GLSW (SW*pixelScale)
#define GLSH (SH*pixelScale)

typedef struct
{
    int f1, f2;
} Time;

Time T;

typedef struct
{
    int w, a, s, d;
    int sl, sr;
    int m;
} Keys;

Keys K;

void pixel(int x, int y, int c)
{
    int rgb[3];
    if (c == 0)
    {
        rgb[0] = 255;
        rgb[1] = 255;
        rgb[2] = 0;
    }
    if (c == 1)
    {
        rgb[0] = 160;
        rgb[1] = 160;
        rgb[2] = 0;
    }
    if (c == 2)
    {
        rgb[0] = 0;
        rgb[1] = 255;
        rgb[2] = 0;
    }
    if (c == 3)
    {
        rgb[0] = 0;
        rgb[1] = 160;
        rgb[2] = 0;
    }
    if (c == 4)
    {
        rgb[0] = 0;
        rgb[1] = 255;
        rgb[2] = 255;
    }
    if (c == 5)
    {
        rgb[0] = 0;
        rgb[1] = 160;
        rgb[2] = 160;
    }
    if (c == 6)
    {
        rgb[0] = 160;
        rgb[1] = 100;
        rgb[2] = 0;
    }
    if (c == 7)
    {
        rgb[0] = 110;
        rgb[1] = 50;
        rgb[2] = 0;
    }
    if (c == 8)
    {
        rgb[0] = 0;
        rgb[1] = 60;
        rgb[2] = 130;
    }
    glColor3ub(rgb[0], rgb[1], rgb[2]);
    glBegin(GL_POINTS);
    glVertex2i(x*pixelScale + 2, y*pixelScale + 2);
    glEnd();
}

void movePlayer()
{
    if (K.a == 1 && K.m == 0)
        printf("left\n");
    if (K.d == 1 && K.m == 0)
        printf("right\n");
    if (K.w == 1 && K.m == 0)
        printf("up\n");
    if (K.s == 1 && K.m == 0)
        printf("down\n");
    
    if (K.sr == 1)
        printf("strafe left\n");
    if (K.sl == 1)
        printf("strafe right\n");
    
    if (K.a == 1 && K.m == 1)
        printf("look up\n");
    if (K.d == 1 && K.m == 1)
        printf("look down\n");
    if (K.w == 1 && K.m == 1)
        printf("look up\n");
    if (K.s == 1 && K.m == 1)
        printf("look down\n");
}

void clearBackground()
{
    for (int y = 0; y < SH; y++)
    {
        for (int x = 0; x < SW; x++)
        {
            pixel(x, y, 8);
        }
    }
}

int tick;
void draw3D()
{
    int x, y, c = 0;
    for (y = 0; y < SH2; y++)
    {
        for (x = 0; x < SW2; x++)
        {
            pixel(x, y, c);
            c += 1;
            if (c > 8)
                c = 0;
        }
    }
    tick += 1;
    if (tick > 20)
        tick = 0;
    pixel(SW2, SW2 + tick, 0);
}

void display()
{
    int x, y;
    if (T.f1 - T.f2 >= 50)
    {
        clearBackground();
        movePlayer();
        draw3D();
        
        T.f2 = T.f1;
        glutSwapBuffers();
        glutReshapeWindow(GLSW, GLSH);
    }
    
    T.f1 = glutGet(GLUT_ELAPSED_TIME);
    glutPostRedisplay();
}

void KeysDown(unsigned char key, int x, int y)
{
    if (key == 'w')
        K.w = 1;
    if (key == 's')
        K.s = 1;
    if (key == 'a')
        K.a = 1;
    if (key == 'd')
        K.d = 1;
    if (key == 'm')
        K.m = 1;
    if (key == ',')
        K.sr = 1;
    if (key == '.')
        K.sl = 1;
}

void KeysUp(unsigned char key, int x, int y)
{
    if (key == 'w')
        K.w = 0;
    if (key == 's')
        K.s = 0;
    if (key == 'a')
        K.a = 0;
    if (key == 'd')
        K.d = 0;
    if (key == 'm')
        K.m = 0;
    if (key == ',')
        K.sr = 0;
    if (key == '.')
        K.sl = 0;
}

void init()
{
    
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(GLSW/2, GLSH/2);
    glutInitWindowSize(GLSW, GLSH);
    glutCreateWindow("");
    glPointSize(pixelScale);
    gluOrtho2D(0, GLSW, 0, GLSH);
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(KeysDown);
    glutKeyboardUpFunc(KeysUp);
    glutMainLoop();
    return 0;
}
