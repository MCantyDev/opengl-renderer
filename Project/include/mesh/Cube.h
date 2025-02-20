#ifndef CUBE_H
#define CUBE_H

#include "mesh/Primitive.h"

#include "shaders/Shader.h"
#include "buffers/VAO.h"
#include "buffers/VBO.h"

#include <vector>

class Cube : public Primitive
{
public:
	Cube();

	virtual void draw(Shader& shader) override;

private:
	VBO vbo;
	
	// Standard Vertices for the 
    std::vector<GLfloat> vertices = {
        // Positions            // Normals             // UVs
        // Front face
        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, -1.0f,    0.0f, 0.0f,  // Vertex 1
         0.5f, -0.5f, -0.5f,   0.0f, 0.0f, -1.0f,    1.0f, 0.0f,  // Vertex 2
         0.5f,  0.5f, -0.5f,   0.0f, 0.0f, -1.0f,    1.0f, 1.0f,  // Vertex 3
        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, -1.0f,    0.0f, 0.0f,  // Vertex 4
         0.5f,  0.5f, -0.5f,   0.0f, 0.0f, -1.0f,    1.0f, 1.0f,  // Vertex 5
        -0.5f,  0.5f, -0.5f,   0.0f, 0.0f, -1.0f,    0.0f, 1.0f,  // Vertex 6

        // Back face
        -0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,     0.0f, 0.0f,  // Vertex 7
         0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,     1.0f, 0.0f,  // Vertex 8
         0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,     1.0f, 1.0f,  // Vertex 9
        -0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,     0.0f, 0.0f,  // Vertex 10
         0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,     1.0f, 1.0f,  // Vertex 11
        -0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,     0.0f, 1.0f,  // Vertex 12

        // Top face
        -0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,     0.0f, 0.0f,  // Vertex 13
         0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,     1.0f, 0.0f,  // Vertex 14
         0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f,     1.0f, 1.0f,  // Vertex 15
        -0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,     0.0f, 0.0f,  // Vertex 16
         0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f,     1.0f, 1.0f,  // Vertex 17
        -0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f,     0.0f, 1.0f,  // Vertex 18

        // Bottom face
        -0.5f, -0.5f, -0.5f,   0.0f, -1.0f, 0.0f,    0.0f, 0.0f,  // Vertex 19
         0.5f, -0.5f, -0.5f,   0.0f, -1.0f, 0.0f,    1.0f, 0.0f,  // Vertex 20
         0.5f, -0.5f,  0.5f,   0.0f, -1.0f, 0.0f,    1.0f, 1.0f,  // Vertex 21
        -0.5f, -0.5f, -0.5f,   0.0f, -1.0f, 0.0f,    0.0f, 0.0f,  // Vertex 22
         0.5f, -0.5f,  0.5f,   0.0f, -1.0f, 0.0f,    1.0f, 1.0f,  // Vertex 23
        -0.5f, -0.5f,  0.5f,   0.0f, -1.0f, 0.0f,    0.0f, 1.0f,  // Vertex 24

        // Left face
        -0.5f, -0.5f, -0.5f,   -1.0f, 0.0f, 0.0f,    0.0f, 0.0f,  // Vertex 25
        -0.5f,  0.5f, -0.5f,   -1.0f, 0.0f, 0.0f,    1.0f, 0.0f,  // Vertex 26
        -0.5f,  0.5f,  0.5f,   -1.0f, 0.0f, 0.0f,    1.0f, 1.0f,  // Vertex 27
        -0.5f, -0.5f, -0.5f,   -1.0f, 0.0f, 0.0f,    0.0f, 0.0f,  // Vertex 28
        -0.5f,  0.5f,  0.5f,   -1.0f, 0.0f, 0.0f,    1.0f, 1.0f,  // Vertex 29
        -0.5f, -0.5f,  0.5f,   -1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // Vertex 30

        // Right face
         0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,    0.0f, 0.0f,  // Vertex 31
         0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 0.0f,    1.0f, 0.0f,  // Vertex 32
         0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,  // Vertex 33
         0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,    0.0f, 0.0f,  // Vertex 34
         0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,  // Vertex 35
         0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f,    0.0f, 1.0f   // Vertex 36
        };
};

#endif // CUBE_H