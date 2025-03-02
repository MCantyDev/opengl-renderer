#ifndef SPHERE_H
#define SPHERE_H

#ifndef M_PI
#define M_PI 3.14159265358979323846 // Used to Form the SPHERE
#endif

#include "mesh/Primitive.h"

#include "buffers/VAO.h"
#include "buffers/VBO.h"
#include "buffers/EBO.h"

#include "shaders/Shader.h"

#include "Structures.h"

#include <vector>
#include <cmath>

/* 
How to do it
--------------------
Right so when creating Spherical Geometry we need to take the Spherical Coordinates (Radius, Theta, Phi) and Convert them into Cartesian Coordinates (x, y, z)

The formulas for this are: 
--------
x = radius * sin(phi) * cos(theta)
y = radius * cos(phi)
z = radius * sin(phi) * sin(theta)

Where:
--------
radius is the radius of the sphere
theta is the longitude angle (0 to 2PI) (2 PI as you can travel 360deg in terms of longitude)
Formula for finding Theta:
--------
Theta = j * (2PI / horizontalDivisions) -> Where J is 1 of the horizontal divisions

phi is the latitude angle (0 to PI) (PI as only 180deg are required to effectively navigate a sphere)
Formula for finding Phi:
--------
Phi = i * (PI / verticalDivisions) -> Where I is 1 of the vertical divisions

Textures:
--------
To find the Texture Coordinates of a Sphere all you need to do is find the UV mapping.
The forumulas for this are:
--------
u = theta / 2PI
v = phi / PI

Indices:
-------
Indices are quite important when creating spherical geometry as unlike a cube which only has 36 vertices, spherical geometry grows INCREDIBLY fast. 
For example a (1.0f, 50, 50) sphere would have 2601 vertices (Formula is (sectors + 1) * (stacks + 1) or (50 + 1) * (50 + 1) = 2601)
*/  

/* @class Sphere */
class Sphere : public Primitive
{
public:
	Sphere(int ID, float r, int vd, int hd);
	virtual void generateMesh() override;
private:

	float radius;
	int verticalDivisions;
	int horizonalDivisions;

	std::vector<Vertex> generateVertices(float r, int vd, int hd);
	std::vector<GLuint> generateIndices(int vd, int hd);
};

#endif // SPHERE_H