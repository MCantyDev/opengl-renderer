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
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
/*
* Purpose - Process user input
* Find - processInput(window) in while loop
*/
void processInput(GLFWwindow* window);

/*
* Purpose - Callback function for the Camera controls for mouse movement
*/
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);


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

// Settings
// ------------
// Constants
int WIDTH = 1200;
int HEIGHT = 900;

// Camera
// -------------
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float baseSpeed = 2.5f;
float lastX = WIDTH / 2;
float lastY = HEIGHT / 2;
float yaw = -90.0f;
float pitch = 0.0f;
float fov = 45.0f;
float sensitivity = 0.05f;
bool firstMouse = true;

// Timing
// ------------
float deltaTime = 0.0f;
float lastFrame = 0.0f;
float fpsTimer = 0.0f;
float fps = 0.0f;
int frameCount = 0;



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
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Renderer Application", nullptr, nullptr);

	if (window == nullptr) // Check if Window was successfully created
	{
		std::cout << "Failed to Create Window" << std::endl;
		glfwTerminate(); // Clean up glfw
		return -1;
	}
	glfwMakeContextCurrent(window); // Make the created window the current context...very useful for next line
	glfwSwapInterval(0); // Deactivate V-SYNC
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	// After making Window current context we can Load GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
	{
		std::cout << "Failed to Initialise GLAD" << std::endl;
		return -1;
	}
	
	glViewport(0, 0, WIDTH, HEIGHT); // Set the default viewport
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // Set the frambuffer size callback function to framebuffer_size_callback 
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

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
	float currFrame = glfwGetTime();
	deltaTime = currFrame - lastFrame;
	lastFrame = currFrame;
	frameCount++;

	fpsTimer += deltaTime;
	if (fpsTimer > 1.0f)
	{
		fps = frameCount;
		frameCount = 0;
		fpsTimer = 0.0f;
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

	// Projection Matrix - Defines the perspective transformation (How 3D Objects are projected on a 2D space)
	glm::mat4 projection;
	projection = glm::perspective(glm::radians(fov), (float)(WIDTH / HEIGHT), 0.1f, 100.0f);
	shaderProgram.setMat4("projection", projection);

	// View Matrix - Tranforms the Camera's positon and orientation (Defines the user's viewpoint)
	glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	shaderProgram.setMat4("view", view);


	// Placing Containers
	float angle = glfwGetTime() * 100.0f;
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

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		std::cout << "Closing Window" << std::endl;
		glfwSetWindowShouldClose(window, true);
	}

	// Camera Movement
	float cameraSpeed = (float)(baseSpeed * deltaTime);
	// WASD Movement
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		cameraPos += cameraSpeed * cameraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		cameraPos -= cameraSpeed * cameraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}

	// Up and Down
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		cameraPos += cameraSpeed * cameraUp;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		cameraPos -= cameraSpeed * cameraUp;
	}

	// Shift = SPEED!
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		baseSpeed = 5.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		baseSpeed = 2.5f;
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xOffset = xpos - lastX;
	float yOffset = ypos - lastY;
	lastX = xpos; lastY = ypos;

	xOffset *= sensitivity;
	yOffset *= sensitivity;

	yaw += xOffset;
	pitch += yOffset;

	if (pitch > 89.0f) pitch = 89.0f;
	if (pitch < -89.0f) pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = -sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));


	cameraFront = glm::normalize(direction);
}

void scroll_callback(GLFWwindow* window, double xOffset, double yOffset)
{
	fov -= (float)yOffset;
	if (fov < 1.0f) fov = 1.0f;
	if (fov > 50.0f) fov = 50.0f;
}