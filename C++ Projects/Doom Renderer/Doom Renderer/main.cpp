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
    int s1, sr;
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
}
