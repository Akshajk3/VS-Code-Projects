#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <gl/glut.h>
#endif
#include <iostream>

const int window_width = 800;
const int window_height = 600;

const int tile_size = 50;

int rows = window_width / tile_size;
int cols = window_height / tile_size;

int tiles[15][11] =
{
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

void place_tile(int mouseX, int mouseY)
{
    int row = mouseY / tile_size;
    int col = mouseX / tile_size;
    tiles[row][col] = 1;
}

void remove_tile(int mouseX, int mouseY)
{
    int row = mouseY / tile_size;
    int col = mouseX / tile_size;
    tiles[row][col] = 0;
}

void draw_tiles()
{
    glColor3f(1.0f, 1.0f, 1.0f);

    for (int y = 0; y < 12; y++)
    {
        for (int x = 0; x < 16; x++)
        {
            if (tiles[y][x] == 1) // Check if the tile should be drawn
            {
                glBegin(GL_QUADS);
                glVertex2i(x * tile_size, y * tile_size);
                glVertex2i((x + 1) * tile_size, y * tile_size);
                glVertex2i((x + 1) * tile_size, (y + 1) * tile_size);
                glVertex2i(x * tile_size, (y + 1) * tile_size);
                glEnd();
            }
        }
    }
}


void draw_grid()
{
    glColor3f(1.0f, 1.0f, 1.0f);
    
    for(int y = 0; y < cols; y++)
    {
        glBegin(GL_LINES);
        glVertex2i(0, y * tile_size);
        glVertex2i(window_width, y * tile_size);
        glEnd();
    }
    
    for(int x = 0; x < rows; x++)
    {
        glBegin(GL_LINES);
        glVertex2i(x * tile_size, 0);
        glVertex2i(x * tile_size, window_height);
        glEnd();
    }
}

void mouse(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        place_tile(x, y);
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        remove_tile(x, y);
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw_grid();
    draw_tiles();
    //std::cout << rows << "," << cols << std::endl;
    glutSwapBuffers();
}

void init()
{
    glClearColor(0, 0, 0, 0);
    gluOrtho2D(0, window_width, window_height, 0);
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(window_width, window_height);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Vindel's Game of Life");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
