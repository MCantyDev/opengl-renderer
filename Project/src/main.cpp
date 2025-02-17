#define STB_IMAGE_IMPLEMENTATION

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include <iostream>
#include "stb/stb_image.h"

#include "shaders/Shader.h"
#include "buffers/VBO.h"
#include "buffers/EBO.h"
#include "buffers/VAO.h"	

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
	// Positions          // Colors           // Texture Coords
	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left
};

GLuint indices[] =
{
	0, 1, 3,
	1, 2 ,3
};

// Main Function
int main()
{
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
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Renderer Application", nullptr, nullptr);

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
	
	glViewport(0, 0, 800, 600); // Set the default viewport
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // Set the frambuffer size callback function to framebuffer_size_callback 

	Shader shaderProgram("shaders/default.vert", "shaders/default.frag");

	VAO VAO1;
	VAO1.bind();
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));
	
	VAO1.linkAttrib(VBO1, 0, 3, (8 * sizeof(float)), (void*)0);
	VAO1.linkAttrib(VBO1, 1, 3, (8 * sizeof(float)), (void*)(3 * sizeof(float)));
	VAO1.linkAttrib(VBO1, 2, 2, (8 * sizeof(float)), (void*)(6 * sizeof(float)));

	VAO1.unbind();
	VBO1.unbind();
	EBO1.unbind();

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Setup Texture Params
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(true);
	int width, height, nrChannels;
	unsigned char* data = stbi_load("assets/container.jpg", &width, &height, &nrChannels, 0);

	if (data)
	{
		GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		std::cout << "SUCCESS: Successfully loaded texture" << std::endl;
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	// Run loop of the application
	while (!glfwWindowShouldClose(window))
	{
		// Process input
		processInput(window);

		// Render stuff here
		glClearColor(0.15f, 0.15f, 0.15f, 1.0f); // Gray background
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.use();
		VAO1.bind();
		
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Use GL_LINE for Wireframe, GL_FILL for filled in
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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