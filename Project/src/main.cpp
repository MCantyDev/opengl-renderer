// Standard Lib Imports
#include <random>
#include <vector>

// Custom Components
#include "shaders/Shader.h"

#include "core/Camera.h"
#include "core/ObjectManager.h"
#include "core/TextureManager.h"
#include "core/MaterialManager.h"
#include "core/LightManager.h"
#include "core/ShaderManager.h"
#include "core/AssimpLoader.h"

// Meshes
#include "mesh/Cube.h"
#include "mesh/Sphere.h"
#include "mesh/Model.h"

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
	GLFWwindow* window = glfwCreateWindow(800, 600, WINDOW_NAME, nullptr, nullptr);
	if (window == nullptr) // Check if Window was successfully created
	{
		std::cout << "Error: Failed to Create Window" << std::endl;
		glfwTerminate(); // Clean up glfw
		return -1;
	}
	
	int width = 800;
	int height = 600;
	std::cout << "Setup: \"" << WINDOW_NAME << "\" window has been created" <<  std::endl;
	std::cout << "Setup: \"" << WINDOW_NAME << "\": Width set as " << width <<  std::endl;
	std::cout << "Setup: \"" << WINDOW_NAME << "\": Height set as " << height << std::endl;

	glfwMakeContextCurrent(window); // Make the created window the current context...very useful for next line
	glfwSwapInterval(0); // Deactivate V-SYNC
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

	// Setup Singleton Instances
	Camera* camera = Camera::GetInstance();
	TextureManager* textureManager = TextureManager::GetInstance();
	MaterialManager* materialManager = MaterialManager::GetInstance();
	LightManager* lightManager = LightManager::GetInstance();
	ObjectManager* objectManager = ObjectManager::GetInstance();
	ShaderManager* shaderManager = ShaderManager::GetInstance();

	
	// Initialise
	AssimpLoader assimpLoader;
	// Setup the Shaders, both the Vertex and Fragment ones
	shaderManager->addShader("default", std::make_shared<Shader>("shaders/default.vert", "shaders/default.frag"));
	shaderManager->addShader("lighting", std::make_shared<Shader>("shaders/lighting.vert", "shaders/lighting.frag"));
	camera->initialiseCamera(window, glm::vec3(0.0f, 0.0f, 3.0f));
	materialManager->addMaterial("default", Material(Base(glm::vec3(0.3f), glm::vec3(1.0f), glm::vec3(0.5f)), 32.0f));
	lightManager->addLight(std::make_shared<DirectionalLight>
	(
		glm::vec3(-0.2f, -1.0f, -0.3f),
		glm::vec3(0.0f),
		glm::vec3(0.3f, 0.3f, 0.3f),
		glm::vec3(0.06f, 0.06f, 0.06f)
	), DIRECTIONAL_LIGHT);
	lightManager->addLight(std::make_shared<PointLight>
	(
		glm::vec3(0.0f, 2.0f, 1.0f),
		glm::vec3(0.1f, 0.1f, 0.1f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(0.3f, 0.3f, 0.3f),
		1.0f, 0.09f, 0.032f
	), POINT_LIGHT);
	objectManager->addObject(std::make_shared<Model>(0, assimpLoader.load("models/Robot/robo.obj")), BASE_OBJECT);
	objectManager->addObject(std::make_shared<Model>(1, assimpLoader.load("models/Backpack/backpack.obj", true)), BASE_OBJECT);

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
		camera->processKeyboardMovement(deltaTime);

		// Render stuff here
		glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection = glm::perspective(glm::radians(camera->getFov()), (float)(width / height), 0.1f, 100.0f);
		glm::mat4 view = camera->getView();

		shaderManager->setupShaderMatrices("default", projection, view);
		shaderManager->setupShaderMatrices("lighting", projection, view);

		shaderManager->setupShaderUniforms("default", { {"viewPos", camera->getPos()} });
		shaderManager->setupLighting("default");

		std::shared_ptr<Object> object = objectManager->getObject(0, BASE_OBJECT);
		std::shared_ptr<Model> robot = std::dynamic_pointer_cast<Model>(object);
		robot->setScale(glm::vec3(0.5f));
		robot->setPosition(glm::vec3(3.0f));

		objectManager->renderObjects(shaderManager->getShader("default"), shaderManager->getShader("lighting"));

		// Swap the buffers and Poll+Call events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	camera->DestroyInstance();
	textureManager->DestroyInstance();
	materialManager->DestroyInstance();
	lightManager->DestroyInstance();
	objectManager->DestroyInstance();
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