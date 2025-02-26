#include "mesh/Sphere.h"

Sphere::Sphere(float r, int vd, int hd)
{
	vao.bind();
	
	std::vector<Vertex> vertices = generateVertices(r, vd, hd);
	indices = generateIndices(vd, hd);

	vbo = VBO(vertices);
	ebo = EBO(indices);

	linkToVAO(vbo);

	vao.unbind();
	vbo.unbind();
	ebo.unbind();
}

void Sphere::draw(Shader& s)
{
	s.use();
	s.setMat4("model", modelMatrix);

	vao.bind();
	ebo.bind();
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	vao.unbind();
	ebo.unbind();
}

// How the Sphere is being created programmatically
std::vector<Vertex> Sphere::generateVertices(float r, int vd, int hd) // 0.3, 10, 10
{
	std::vector<Vertex> vertices;

	for (int i = 0; i <= vd; i++) // until i = 10 (11 times)
	{
		for (int j = 0; j <= hd; j++) // until j = 10 (11 times)  (11 * 11) = 121
		{
			Vertex vertex;

			// Spherical Coordinates
			float theta = j * (2 * M_PI / hd); // 1 * (2 * 3.14159 / 10) = 0.628318
			float phi = i * (M_PI / vd); // 1 * (3.14159 / 10) = 0.314159

			float x = r * sin(phi) * cos(theta); // 0.3 * sin(0.314159) * cos(0.628318) = 0.99993987163561784810612642895555
			float y = r * cos(phi); // 0.3 * cos(0.314159)								= 0.99998496779592088228841002347539
			float z = r * sin(phi) * sin(theta); // 0.3 * sin(0.314159) * sin(0.628318) = 0.99993987163561784810612642895555

			// Simply Normalise the Values for X, Y, Z
			glm::vec3 normalised = glm::normalize(glm::vec3(x, y, z)); // Unit Vector (Length of 1)

			float u = theta / (2 * M_PI);
			float v = phi / M_PI;

			vertex.position = glm::vec3(x, y, z);
			vertex.normal = normalised;
			vertex.textureCoords = glm::vec2(u, v);
			
			vertices.push_back(vertex);
		}
	}
	return vertices;
}

std::vector<GLuint> Sphere::generateIndices(int vd, int hd)
{
	std::vector<GLuint> indices; // Setting up the Vector

	// First Loop - Vertical Divisions (Latitude)
	for (int i = 0; i <= vd; i++)
	{
		// Second Loop - Horizontal Divisions (Longitude)
		for (int j = 0; j <= hd; j++)
		{
			// Finding the appropriate values to build 2 triangles for 1 quad
			// Imagine starting at i = 0 and j = 0 where vd = 30 and hd = 30
			int first = i * (hd + 1) + j;	// First Calc becomes (0 * (30 + 1) + 0) or 0
			int second = first + hd + 1;	// Second Calc becomes 0 + 30 + 1 or 31

			// First Triangle
			indices.push_back(first);		// Pushing back 0 (first vertex on first row)		+--+
			indices.push_back(second);		// Pushing back 31 (first vertex on second row		| /
			indices.push_back(first + 1);	// Pushing back 1 (second vertex on first row)		|/
			//																	                +
			// Second Triangle																	  +
			indices.push_back(second);		// Pushing back 31 (first vertex on second row)		 /|
			indices.push_back(second + 1);	// Pushing back 32 (second vertex on second row)    / |
			indices.push_back(first + 1);	// Pushing back 1 (second vertex on first row)	   +--+

			/*	Together they become a single quad like this
			*	
			*	+--+
			*	| /|
			*	|/ |
			*	+--+
			*/
		}
	}
	return indices;
}