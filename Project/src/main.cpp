#define STB_IMAGE_IMPLEMENTATION

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "shaders/Shader.h"
#include "buffers/VBO.h"
#include "buffers/EBO.h"
#include "buffers/VAO.h"	
#include "textures/Texture.h"

/*
* Purpose - Callback Function when the Window has been resized with cursor. 
* Find - glfwSetFramebufferSizeCallback()
*/
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

/*
* Purpose - Process user input
* Find - processInput(window) in while loop
*/
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		std::cout << "Closing Window" << std::endl;
		glfwSetWindowShouldClose(window, true);
	}
}

GLfloat vertices[] = {
	// Positions          // Texture Coords
	 0.5f,  0.5f, 0.0f,   1.0f, 1.0f,		// Top Right
	 0.5f, -0.5f, 0.0f,   1.0f, 0.0f,		// Bottom Right
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f,		// Bottom Left
	-0.5f,  0.5f, 0.0f,   0.0f, 1.0f		// Top Left
};

GLuint indices[] =
{
	0, 1, 3,
	1, 2 ,3,
};

// Constants
int WIDTH = 1200;
int HEIGHT = 900;
float speed = 2.0f;

// Main Function
int main()
{
	float lastFrame = 0.0f;
	float deltaTime = 0.0f;

	if (!glfwInit()) // Attempt to init glfw
	{
		std::cout << "Failed to Initialise GLFW" << std::endl;
		return -1; // Return error code
	}

	// Setup window hints for version 4.6 of OpenGL (The most recent version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	// Use the Core profile as that is what is used with GLAD
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	// Create a GLFWwindow pointer, with the glfwCreateWindow function
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Renderer Application", nullptr, nullptr);

	if (window == nullptr) // Check if Window was successfully created
	{
		std::cout << "Failed to Create Window" << std::endl;
		glfwTerminate(); // Clean up glfw
		return -1;
	}
	glfwMakeContextCurrent(window); // Make the created window the current context...very useful for next line
	
	// After making Window current context we can Load GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
	{
		std::cout << "Failed to Initialise GLAD" << std::endl;
		return -1;
	}
	
	glViewport(0, 0, WIDTH, HEIGHT); // Set the default viewport
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // Set the frambuffer size callback function to framebuffer_size_callback 

	Shader shaderProgram("shaders/default.vert", "shaders/default.frag");

	VAO VAO1;
	VAO1.bind();
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));
	
	VAO1.linkAttrib(VBO1, 0, 3, GL_FLOAT, (5 * sizeof(float)), (void*)0);
	VAO1.linkAttrib(VBO1, 1, 2, GL_FLOAT, (5 * sizeof(float)), (void*)(3 * sizeof(float)));

	VAO1.unbind();
	VBO1.unbind();
	EBO1.unbind();

	Texture texture("assets/container.jpg");
	Texture texture2("assets/awesomeface.png");
	texture.activateTexture(0);
	texture2.activateTexture(1);

	// Run loop of the application
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Process input
		processInput(window);

		// Render stuff here
		glClearColor(0.15f, 0.15f, 0.15f, 1.0f); // Gray background
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.use();
		shaderProgram.setInt("texture1", 0);
		shaderProgram.setInt("texture2", 1);
		VAO1.bind();
		
		// First Container
		// Matrix transformations
		glm::mat4 identityMatrix(1.0f);  // Identity matrix (with the diag values being 1.0)
		identityMatrix = glm::translate(identityMatrix, glm::vec3(0.5f, -0.5f, 0.0f)); // Moving the Container to the the Bottom Right
		identityMatrix = glm::rotate(identityMatrix, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f)); // Rotating the Container in place based on the glfwGetTime()

		// Drawing the Container
		shaderProgram.setMat4("transform", identityMatrix);
		glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0); // Drawing the second Container

		// Second Container
		// Matrix Transformations
		identityMatrix = glm::mat4(1.0f); // reset it to identity matrix
		identityMatrix = glm::translate(identityMatrix, glm::vec3(-0.5f, 0.5f, 0.0f)); // Moving the Container to the top left

		float scale = sin(glfwGetTime());

		identityMatrix = glm::scale(identityMatrix, glm::vec3(scale, scale, scale)); // Scaling each axis by the scale amount for a equal scaling in each axis
		identityMatrix = glm::rotate(identityMatrix, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, -1.0f));

		// Drawing the Container
		shaderProgram.setMat4("transform", identityMatrix);
		shaderProgram.setInt("texture2", 0);
		glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0); // Drawing the Second Container

		// Third Container
		// Matrix Transformations
		identityMatrix = glm::mat4(1.0f);
		identityMatrix = glm::translate(identityMatrix, glm::vec3(0.5f, 0.5f, 0.0f));
		identityMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.5f, 0.5f));
		identityMatrix = glm::rotate(identityMatrix, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));

		shaderProgram.setMat4("transform", identityMatrix);
		
		// Make Both Textures equal to something that doesnt exist
		shaderProgram.setInt("texture1", 3);
		shaderProgram.setInt("texture2", 3);
		glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);


		// Last Container
		identityMatrix = glm::mat4(1.0f);
		identityMatrix = glm::translate(identityMatrix, glm::vec3(-0.5f, -0.5f, 0.0f));
		identityMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.5f, 0.5f));

		shaderProgram.setMat4("transform", identityMatrix);
		shaderProgram.setInt("texture1", 0);
		shaderProgram.setInt("texture2", 1);
		glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);
		
		glBindVertexArray(0);

		// Swap the buffers and Poll+Call events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Clean up
	VAO1.clear();
	VBO1.clear();
	EBO1.clear();
	shaderProgram.clear();

	glfwDestroyWindow(window);
	glfwTerminate();
	
	return 0;
}