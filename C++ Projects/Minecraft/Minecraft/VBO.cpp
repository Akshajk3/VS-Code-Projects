#include "VBO.h"

VBO::VBO(std::vector<GLfloat> vertices)
{
    int n = vertices.size();
    
    GLfloat* verts = new GLfloat[n];
    for (int i = 0; i < n; i++)
    {
        verts[i] = vertices[i];
    }
    
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
    
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * n, verts, GL_STATIC_DRAW);
    
    delete[] verts;
}

void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}
