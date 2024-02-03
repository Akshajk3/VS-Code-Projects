#pragma once

#include <iostream>
#include <GLUT/glut.h>

class Raytracer
{
public:
    Raytracer();
    ~Raytracer();
    
    void init();
    void display();
    void drawPlayer();
};
