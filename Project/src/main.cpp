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

// Meshes
#include "mesh/Cube.h"
#include "mesh/Sphere.h"

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


std::vector<glm::vec3> generateRandomPositions(int numPositions, float minValue, float maxValue) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(minValue, maxValue);

	std::vector<glm::vec3> positions;

	positions.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
	for (int i = 0; i < numPositions - 1; ++i) {
		float x = dis(gen);
		float y = dis(gen);
		float z = dis(gen);

		positions.push_back(glm::vec3(x, y, z));
	}

	return positions;
}

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

	// Get the Monitor for the Total Size
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	// Create a GLFWwindow pointer, with the glfwCreateWindow function
	GLFWwindow* window = glfwCreateWindow(800, 600, WINDOW_NAME, nullptr, nullptr);
	if (window == nullptr) // Check if Window was successfully created
	{
		std::cout << "Error: Failed to Create Window" << std::endl;
		glfwTerminate(); // Clean up glfw
		return -1;
	}
	glfwMaximizeWindow(window);
	
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
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
	
	// Initialise
	camera->initialiseCamera(window, glm::vec3(0.0f, 0.0f, 3.0f));

	// Setup the Shaders, both the Vertex and Fragment ones
	Shader defaultShader("shaders/default.vert", "shaders/default.frag");
	Shader lightingShader("shaders/lighting.vert", "shaders/lighting.frag");

	// Enable Depth Testing for Rendering the correct stuff based on Depth
	glEnable(GL_DEPTH_TEST);


	// Lets me draw cubes!
	Cube cube;
	Sphere sphere(0.3f, 50, 50);

	GLuint diff = textureManager->addTexture("wood", TEXTURE_DIFFUSE, "assets/woodenCube.png");
	GLuint spec = textureManager->addTexture("wood", TEXTURE_SPECULAR, "assets/woodenCubeSpecular.png");
	GLuint emission = textureManager->addTexture("matrix", TEXTURE_EMISSION, "assets/matrix.jpg");

	// Activate Matrix Emission texture by change -1 to emission
	materialManager->addMaterial(
		"woodenCube", 
		Material( diff, spec, -1, 64.0f) 
	);

	materialManager->addMaterial(
		"sphere",
		Material(Base(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.5f, 0.5f, 0.5f)), 64.0f)
	);
	
	lightManager->addLight(std::make_shared<DirectionalLight>
	(
		glm::vec3(-0.2f, -1.0f, -0.3f),
		glm::vec3(0.0f),
		glm::vec3(0.3f, 0.3f, 0.3f),
		glm::vec3(0.06f, 0.06f, 0.6f)
	), DIRECTIONAL_LIGHT);

	lightManager->addLight(std::make_shared<PointLight>
	(
		glm::vec3(1.2f, 1.0f, 2.0f),
		glm::vec3(0.05f, 0.01f, 0.01f),
		glm::vec3(0.3f, 0.3f, 0.3f),
		glm::vec3(0.1f, 0.1f, 0.1f),
		1.0f, 0.14f, 0.07f
	), POINT_LIGHT);

	std::cout << "Setup: Initialisation of Application complete\nSetup: Proceeding to Run" << std::endl;

	std::vector<glm::vec3> positions = generateRandomPositions(50, -10.0, 10.0f);

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
			oss << WINDOW_NAME << " - FPS: " << fps; // Build the string
			glfwSetWindowTitle(window, oss.str().c_str());
		}

		// Process input
		processInput(window);
		camera->processKeyboardMovement(deltaTime);

		// Render stuff here
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Gray background
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Starting using the Texture Program and use the proper textures
		defaultShader.use();

		// Make sure we have the correct WIDTH and HEIGHT
		glfwGetFramebufferSize(window, &width, &height);
	
		// Setup Projection Matrix
		glm::mat4 projection;
		projection = glm::perspective(glm::radians(camera->getFov()), (float)(width / height), 0.1f, 100.0f);
		defaultShader.setMat4("projection", projection);

		// Setup View Matrix
		glm::mat4 view = camera->getView();
		defaultShader.setMat4("view", view);
		defaultShader.setVec3("viewPos", camera->getPos());

		// Setup Material
		defaultShader.setMaterial(materialManager->getMaterial("woodenCube"));
		
		defaultShader.setInt("numDirLights", lightManager->getMapSize(DIRECTIONAL_LIGHT));
		std::shared_ptr<Light> light = lightManager->getLight(0, DIRECTIONAL_LIGHT);
		std::shared_ptr<DirectionalLight> dirLight = std::dynamic_pointer_cast<DirectionalLight>(light);
		defaultShader.setVec3("dirLights[0].direction", dirLight->direction);
		defaultShader.setVec3("dirLights[0].ambient", dirLight->ambient);
		defaultShader.setVec3("dirLights[0].diffuse", dirLight->diffuse);
		defaultShader.setVec3("dirLights[0].specular", dirLight->specular);

		// Render Multiple Cubes
		for (int i = 0; i < positions.size(); i++)
		{
			cube.setPosition(positions[i]);
			cube.setRotation(20.f * i, glm::vec3(1.0f, 0.3f, 0.5));
			cube.draw(defaultShader);
		}

		lightingShader.use();

		lightingShader.setMat4("projection", projection);
		lightingShader.setMat4("view", view);
		//lightingShader.setVec3("lightColour", pointLight.diffuse);

		//sphere.setPosition(pointLight.position);
		sphere.setScale(glm::vec3(0.5f, 0.5f, 0.5f));
		sphere.draw(lightingShader);

		// Swap the buffers and Poll+Call events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Clean up
	defaultShader.clear();
	lightingShader.clear();

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