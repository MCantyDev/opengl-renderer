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

// Indices took specifically from LearnOpenGL.com
GLfloat vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

// Cube Positions to place the cubes at
glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(5.0f,  7.0f, -17.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};

GLuint indices[] =
{
	0, 1, 3,
	1, 2 ,3,
};

// Constants
int WIDTH = 1200;
int HEIGHT = 900;

// Main Function
int main()
{
	// For the Frame Generation
	float lastTime = 0.0f;
	int frameCount = 0;
	float fps = 0.0f;
	float speed = 20.0f;

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
	glfwSwapInterval(0); // Deactivate V-SYNC
	
	// After making Window current context we can Load GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
	{
		std::cout << "Failed to Initialise GLAD" << std::endl;
		return -1;
	}
	
	glViewport(0, 0, WIDTH, HEIGHT); // Set the default viewport
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // Set the frambuffer size callback function to framebuffer_size_callback 

	// Setup the Shaders, both the Vertex and Fragment ones
	Shader shaderProgram("shaders/default.vert", "shaders/default.frag");

	// Buffer and VAO Setup
	VAO VAO1; // VAO -> Vertex Array Object
	VAO1.bind(); // Binding the VAO
	VBO VBO1(vertices, sizeof(vertices)); // Creating a VBO (Vertex Buffer Object) with the Vertices array
	
	// Creating the Attribute Pointers to correctly identify data from the VBO in the Shader program
	VAO1.linkAttrib(VBO1, 0, 3, GL_FLOAT, (5 * sizeof(float)), (void*)0); 
	VAO1.linkAttrib(VBO1, 1, 2, GL_FLOAT, (5 * sizeof(float)), (void*)(3 * sizeof(float)));

	// Unbinding the VAO, VBO, and EBO
	VAO1.unbind();
	VBO1.unbind();

	// Creating the Textures used within the program
	Texture texture1("assets/container.jpg");
	Texture texture2("assets/awesomeface.png");
	texture1.activateTexture(0);
	texture2.activateTexture(1);

	// Enable Depth Testing for Rendering the correct stuff based on Depth
	glEnable(GL_DEPTH_TEST);

	// Run loop of the application
	while (!glfwWindowShouldClose(window))
	{
		// Show FPS in title
		float currTime = glfwGetTime();
		frameCount++;

		if (currTime - lastTime >= 1.0f)
		{
			fps = frameCount;
			frameCount = 0;
			lastTime = currTime;

			std::ostringstream oss;
			oss << "OpenGL Renderer Application - FPS: " << fps; // Build the string
			glfwSetWindowTitle(window, oss.str().c_str());
		}

		// Process input
		processInput(window);

		// Render stuff here
		glClearColor(0.15f, 0.15f, 0.15f, 1.0f); // Gray background
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Starting using the Texture Program and use the proper textures
		shaderProgram.use();
		shaderProgram.setInt("texture1", 0);
		shaderProgram.setInt("texture2", 1);

		VAO1.bind();
		
		// View Matrix - Tranforms the Camera's positon and orientation (Defines the user's viewpoint)
		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		shaderProgram.setMat4("view", view);

		// Projection Matrix - Defines the perspective transformation (How 3D Objects are projected on a 2D space)
		glm::mat4 projection;
		projection = glm::perspective(glm::radians(50.0f), (float)(WIDTH / HEIGHT), 0.1f, 100.0f);
		shaderProgram.setMat4("projection", projection);

		// Placing Containers
		float angle = glfwGetTime() * speed;
		for (GLuint i = 0; i < 10; i++)
		{
			// Model Matrix - Transforms each cube individually (Position, Rotation, Scale)
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);

			float x = (i % 2 == 0) ? 1.0f : -1.0f;
			float y = (i % 2 == 0) ? 0.3f : -0.3f;
			float z = (i % 2 == 0) ? 0.5f : -0.5f;

			model = glm::rotate(model, glm::radians(angle + (20.0f * i)), glm::vec3(x, y, z));
			shaderProgram.setMat4("model", model);
			
			// Drawing the Triangles
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glBindVertexArray(0);

		// Swap the buffers and Poll+Call events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Clean up
	VAO1.clear();
	VBO1.clear();
	shaderProgram.clear();

	glfwDestroyWindow(window);
	glfwTerminate();
	
	return 0;
}