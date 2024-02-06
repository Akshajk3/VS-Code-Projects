#include <gl/glut.h>
#include <iostream>
#include <math.h>
#include <cmath>

#define PI 3.1415926535
#define P2 PI / 2
#define P3 3 * PI / 2
#define M_PI (3.141592653589793238462643383279502884L)
#define DR 0.0174533 // one degree in radians

float px, py, pdx, pdy, pa;

typedef struct
{
    int w, a, d, s;
} ButtonKeys;

ButtonKeys Keys;

void drawPlayer()
{
    glColor3f(1, 1, 0);
    glPointSize(8);
    glBegin(GL_POINTS);
    glVertex2i(px, py);
    glEnd();

    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2i(px, py);
    glVertex2i(px + pdx * 5, py + pdy * 5);
    glEnd();
}

int mapX = 8;
int mapY = 8;
int mapS = 64;
int map[] =
{
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 1, 0, 0, 0, 0, 1,
    1, 0, 1, 0, 0, 0, 0, 1,
    1, 0, 1, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
};

void drawMap2D()
{
    int x, y, xo, yo;
    for(y = 0; y < mapY; y++)
    {
        for(x = 0; x < mapX; x++)
        {
            if(map[y * mapX + x] == 1)
            {
                glColor3f(1, 1, 1);
            }
            else
            {
                glColor3f(0, 0, 0);
            }
            xo = x*mapS;
            yo = y*mapS;
            glBegin(GL_QUADS);
            glVertex2i(xo + 1, yo + 1);
            glVertex2i(xo + 1, yo+mapS - 1);
            glVertex2i(xo+mapS - 1, yo+mapS - 1);
            glVertex2i(xo+mapS - 1, yo + 1);
            glEnd();
        }
    }
}

float degToRad(float a)
{
    return a * M_PI / 180.0;
}

float FixAng(float a)
{
    if (a > 359)
    {
        a -= 360;
    }
    if (a < 0)
    {
        a += 360;
    }

    return a;
}

float dist(float ax, float ay, float bx, float by, float ang)
{
    return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

float frame1, frame2, fps;

void drawRays2D()
{
    glColor3f(0,1,1);
    glBegin(GL_QUADS);
    glVertex2i(526, 0);
    glVertex2i(1006, 0);
    glVertex2i(1006, 160);
    glVertex2i(526, 160);
    glEnd();
    
    glColor3f(0,0,1);
    glBegin(GL_QUADS);
    glVertex2i(526, 160);
    glVertex2i(1006, 160);
    glVertex2i(1006, 320);
    glVertex2i(526, 320);
    glEnd();
    
    int r, mx, my, mp, dof;
    float rx, ry, ra, xo, yo, disT;
    ra = pa - DR * 30;
    if (ra < 0)
        ra += 2 * PI;
    if (ra > 2 * PI)
        ra -= 2 * PI;

    for (r = 0; r < 60; r++)
    {
        // Check Horizontal Lines
        dof = 0;
        float disH = 1000000;
        float hx = px;
        float hy = py;
        float aTan = -1 / tan(ra);
        if (ra > PI) // looking up
        {
            ry = (((int)py >> 6) << 6) - 0.0001;
            rx = (py - ry) * aTan + px;
            yo = -64;
            xo = -yo * aTan;
        }
        if (ra < PI) // looking down
        {
            ry = (((int)py >> 6) << 6) + 64;
            rx = (py - ry) * aTan + px;
            yo = 64;
            xo = -yo * aTan;
        }
        if (ra == 0 | ra == PI)
        {
            rx = px;
            ry = py;
            dof = 8;
        }
        while (dof < 8)
        {
            mx = (int)(rx) >> 6;
            my = (int)(ry) >> 6;
            mp = my * mapX + mx;
            if (mp > 0 && mp < mapX * mapY && map[mp] > 0) // hit a wall
            {
                hx = rx;
                hy = ry;
                disH = dist(px, py, hx, hy, ra);
                dof = 8;
            }
            else // next line
            {
                rx += xo;
                ry += yo;
                dof += 1;
            }
        }

        // Check Vertical Lines
        dof = 0;
        float nTan = -tan(ra);
        float disV = 1000000;
        float vx = px;
        float vy = py;
        if (ra > P2 && ra < P3) // looking left
        {
            rx = (((int)px >> 6) << 6) - 0.0001;
            ry = (px - rx) * nTan + py;
            xo = -64;
            yo = -xo * nTan;
        }
        if (ra < P2 || ra > P3) // looking right
        {
            rx = (((int)px >> 6) << 6) + 64;
            ry = (px - rx) * nTan + py;
            xo = 64;
            yo = -xo * nTan;
        }
        if (ra == 0 | ra == PI)
        {
            rx = px;
            ry = py;
            dof = 8;
        }
        while (dof < 8)
        {
            mx = (int)(rx) >> 6;
            my = (int)(ry) >> 6;
            mp = my * mapX + mx;
            if (mp > 0 && mp < mapX * mapY && map[mp] > 0) // hit a wall
            {
                vx = rx;
                vy = ry;
                disV = dist(px, py, vx, vy, ra);
                dof = 8;
            }
            else // next line
            {
                rx += xo;
                ry += yo;
                dof += 1;
            }
        }
        if (disV < disH) // vertical Wall Hit
        {
            rx = vx;
            ry = vy;
            disT = disV;
            glColor3f(0, 0.9, 0);
        }
        else // horizontal Wall Hit
        {
            rx = hx;
            ry = hy;
            disT = disH;
            glColor3f(0, 0.7, 0);
        }
        glLineWidth(3);
        glBegin(GL_LINES);
        glVertex2i(px, py);
        glVertex2i(rx, ry);
        glEnd();

        // Draw 3d Walls
        float ca = pa - ra;
        if (ca < 0)
            ca += 2 * PI;
        if (ca > 2 * PI)
            ca -= 2 * PI;
        disT = disT * cos(ca); // fix fisheye
        float lineH = (mapS * 320) / disT;
        if (lineH > 320)
            lineH = 320;
        float lineO = 160 - lineH / 2;
        glLineWidth(8);
        glBegin(GL_LINES);
        glVertex2i(r * 8 + 530, lineO);
        glVertex2i(r * 8 + 530, lineH + lineO);
        glEnd();

        ra += DR;
        if (ra < 0)
            ra += 2 * PI;
        if (ra > 2 * PI)
            ra -= 2 * PI;
    }
}

void display()
{
    frame2 = glutGet(GLUT_ELAPSED_TIME);
    fps = (frame2 - frame1);
    frame1 = glutGet(GLUT_ELAPSED_TIME);

    if(Keys.a == 1)
    {
        pa += 0.2 * fps;
        pa = FixAng(pa);
        pdx = cos(degToRad(pa));
        pdy = -sin(degToRad(pa));
    }
    if (Keys.d == 1)
    {
        pa -= 0.2 * fps;
        pa = FixAng(pa);
        pdx = cos(degToRad(pa));
        pdy = -sin(degToRad(pa));
    }
    if (Keys.w == 1)
    {
        px += pdx * 0.2 * fps;
        py += pdy * 0.2 * fps;

    }
    if (Keys.s == 1)
    {
        px -= pdx * 0.2 * fps;
        py -= pdy * 0.2 * fps;
    }
    glutPostRedisplay();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawMap2D();
    drawRays2D();
    drawPlayer();
    glutSwapBuffers();
}

void ButtonDown(unsigned char key, int x, int y)
{
    if(key == 'a')
    {
        Keys.a = 1;
    }
    if(key == 'd')
    {
        Keys.d = 1;
    }
    if (key == 'w')
    {
        Keys.w = 1;
    }
    if (key == 's')
    {
        Keys.s = 1;
    }
    glutPostRedisplay();
}

void ButtonUp(unsigned char key, int x, int y)
{
    if(key == 'a')
    {
        Keys.a = 0;
    }
    if(key == 'd')
    {
        Keys.d = 0;
    }
    if(key == 'w')
    {
        Keys.w = 0;
    }
    if(key == 's')
    {
        Keys.s = 0;
    }
    glutPostRedisplay();
}

void init()
{
    glClearColor(0.3, 0.3, 0.3, 0);
    gluOrtho2D(0, 1024, 512, 0);
    px = 300;
    py = 300;
    pa = 90;
    pdx = cos(degToRad(pa));
    pdy = -sin(degToRad(pa));
}

void resize(int w, int h)
{
    glutReshapeWindow(1024, 512);
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1024, 512);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Vindelcaster");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutKeyboardFunc(ButtonDown);
    glutKeyboardUpFunc(ButtonUp);
    glutMainLoop();
    return 0;
}
