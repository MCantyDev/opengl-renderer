#include "mesh/Sphere.h"

Sphere::Sphere(float r, int vd, int hd)
{
	sphereVAO.bind();
	
	std::vector<float> vertices = generateVertices(r, vd, hd);
	indices = generateIndices(vd, hd);

	sphereVBO = VBO(vertices.data(), vertices.size() * sizeof(float));
	sphereEBO = EBO(indices.data(), indices.size() * sizeof(GLuint));

	sphereVAO.linkAttrib(sphereVBO, 0, 3, GL_FLOAT, (5 * sizeof(float)), (void*)0);
	sphereVAO.linkAttrib(sphereVBO, 1, 2, GL_FLOAT, (5 * sizeof(float)), (void*)(3 * sizeof(float)));
}

void Sphere::setPosition(float x, float y, float z)
{
	modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
}

void Sphere::setRotation(float angle, glm::vec3 axis)
{
	modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), axis);
}

void Sphere::draw(Shader& s)
{
	s.use();
	s.setMat4("model", modelMatrix);

	sphereVAO.bind();
	sphereEBO.bind();
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	sphereVAO.unbind();
	sphereEBO.unbind();
}

// How the Sphere is being created programmatically
std::vector<float> Sphere::generateVertices(float r, int vd, int hd)
{
	std::vector<float> vertices;

	for (int i = 0; i <= vd; i++)
	{
		for (int j = 0; j <= hd; j++)
		{
			// Spherical Coordinates
			float theta = j * (2 * M_PI / hd);
			float phi = i * (M_PI / vd);

			float x = r * sin(phi) * cos(theta);
			float y = r * cos(phi);
			float z = r * sin(phi) * sin(theta);

			float u = theta / (2 * M_PI);
			float v = phi / M_PI;

			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);
			vertices.push_back(u);
			vertices.push_back(v);
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