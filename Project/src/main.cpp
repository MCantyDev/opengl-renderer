// Standard Lib Imports
#include <vector>

// Custom Components
#include "core/SceneManager.h"

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

// Settings
// ------------
// Constants
int GLFW_MAJOR = 4;
int GLFW_MINOR = 6;
const char* WINDOW_NAME = "OpenGL Renderer Application";

// Windowing
// ------------
int width = 1200;
int height = 800;

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
	std::cout << "Setup: Beginning to initialise application requirements" << std::endl;

	if (!glfwInit()) // Attempt to init glfw
	{
		std::cout << "Error: Failed to Initialise GLFW" << std::endl;
		return -1; // Return error code
	}
	std::cout << "Setup: Initialised GLFW successfully" << std::endl;

	// Setup window hints for version 4.6 of OpenGL (The most recent version)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLFW_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLFW_MINOR);
	std::cout << "Setup: Using GLFW version: " << GLFW_MAJOR << "." << GLFW_MINOR << std::endl;
	// Use the Core profile as that is what is used with GLAD
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	std::cout << "Setup: GLFW_OPENGL_PROFILE: Core Profile Selected" << std::endl;

	// Create a GLFWwindow pointer, with the glfwCreateWindow function
	GLFWwindow* window = glfwCreateWindow(width, height, WINDOW_NAME, nullptr, nullptr);
	if (window == nullptr) // Check if Window was successfully created
	{
		std::cout << "Error: Failed to Create Window" << std::endl;
		glfwTerminate(); // Clean up glfw
		return -1;
	}
	std::cout << "Setup: \"" << WINDOW_NAME << "\" window has been created" <<  std::endl;
	std::cout << "Setup: \"" << WINDOW_NAME << "\": Width set as " << width <<  std::endl;
	std::cout << "Setup: \"" << WINDOW_NAME << "\": Height set as " << height << std::endl;

	glfwMakeContextCurrent(window); // Make the created window the current context...very useful for next line
	glfwSwapInterval(0); // V-SYNC - 0 for Off, 1 for On
	std::cout << "Setup: V-Sync Deactivated" << std::endl;

	// After making Window current context we can Load GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
	{
		std::cout << "Error: Failed to Initialise GLAD" << std::endl;
		return -1;
	}
	std::cout << "Setup: GLAD Initialised successfully with \"" << WINDOW_NAME << "\" window set as context" << std::endl;
	
	glViewport(0, 0, width, height); // Set the default viewport
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // Set the frambuffer size callback function to framebuffer_size_callback 

	std::unique_ptr<SceneManager> sceneManager = std::make_unique<SceneManager>();
	sceneManager->initialiseSystems(window);
	sceneManager->addObject("robot", "models/Robot/robo.obj");

	glEnable(GL_DEPTH_TEST);
	std::cout << "Setup: Initialisation of Application complete\nSetup: Proceeding to Run" << std::endl;

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
			oss << WINDOW_NAME << " - FPS: " << fps; // Build the string
			glfwSetWindowTitle(window, oss.str().c_str());
		}

		// Process input
		processInput(window);
		sceneManager->cameraMovement(deltaTime);

		// Render stuff here
		glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		sceneManager->editObject(0, { {"scale", glm::vec3(0.2f)}, {"position", glm::vec3(0.0f)}, {"rotation", Rotation(-45.0f, glm::vec3(0.0f, 1.0f, 0.0f))}, {"material", "RoboMaterial"} });
		sceneManager->editLight(0, DIRECTIONAL_LIGHT, { {"ambient", glm::vec3(0.0f)}, {"diffuse", glm::vec3(1.0f, 1.0f, 1.0f)} });
		
		sceneManager->update(width, height);
		sceneManager->render();

		// Swap the buffers and Poll+Call events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

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
}