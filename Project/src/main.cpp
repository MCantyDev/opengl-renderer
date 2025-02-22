// Standard Lib Imports
#include <random>
#include <vector>
#include <cmath>

// Custom Components
#include "shaders/Shader.h"

#include "core/Camera.h"
#include "core/ObjectManager.h"
#include "core/TextureManager.h"
#include "core/MaterialManager.h"

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
int WIDTH = 1200;
int HEIGHT = 900;

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
	
	// After making Window current context we can Load GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
	{
		std::cout << "Failed to Initialise GLAD" << std::endl;
		return -1;
	}
	
	glViewport(0, 0, WIDTH, HEIGHT); // Set the default viewport
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // Set the frambuffer size callback function to framebuffer_size_callback 

	// Setup Singleton Instances
	Camera* camera = Camera::GetInstance();
	TextureManager* textureManager = TextureManager::GetInstance();
	MaterialManager* materialManager = MaterialManager::GetInstance();

	// Setup the Shaders, both the Vertex and Fragment ones
	Shader defaultShader("shaders/default.vert", "shaders/default.frag");
	Shader lightingShader("shaders/lighting.vert", "shaders/lighting.frag");

	// Enable Depth Testing for Rendering the correct stuff based on Depth
	glEnable(GL_DEPTH_TEST);


	// Lets me draw cubes!
	Cube cube;
	Sphere sphere(0.3f, 50, 50);


	// Initialise
	camera->initialiseCamera(window, glm::vec3(0.0f, 0.0f, 3.0f));

	textureManager->addTexture("wood_diffuse", "assets/woodenCube.png");
	textureManager->addTexture("wood_specular", "assets/woodenCubeSpecular.png");
	textureManager->addTexture("wood_emission", "assets/matrix.jpg");

	Material baseMaterial( Base(glm::vec3(0.2f), glm::vec3(0.5f, 0.75f, 0.2f), glm::vec3(0.5f)), 256.0f );

	Material texturedMaterial(
		textureManager->getTexture("wood_diffuse"), 
		textureManager->getTexture("wood_specular"), 
		textureManager->getTexture("wood_emission"), 
		64.0f
	);

	Light light
	{
		glm::vec3(1.2f, 1.0f, 2.0f),
		glm::vec3(0.2f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f)
	};

	std::vector<glm::vec3> positions = generateRandomPositions(100, -10.0f, 10.0f);

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
	camera->processKeyboardMovement(deltaTime);

	// Render stuff here
	glClearColor(0.15f, 0.15f, 0.15f, 1.0f); // Gray background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// Starting using the Texture Program and use the proper textures
	defaultShader.use();
	
	// Setup Projection Matrix
	glm::mat4 projection;
	projection = glm::perspective(glm::radians(camera->getFov()), (float)(WIDTH / HEIGHT), 0.1f, 100.0f);
	defaultShader.setMat4("projection", projection);

	// Setup View Matrix
	glm::mat4 view = camera->getView();
	defaultShader.setMat4("view", view);

	// Provide the Shader the Uniforms that are needed for Rendering Light
	defaultShader.setLight(light);
	defaultShader.setVec3("viewPos", camera->getPos());

	defaultShader.setMaterial(texturedMaterial);
	defaultShader.setFloat("time", glfwGetTime() * 0.2);
	cube.setPosition(positions[0]);
	cube.setRotation(glfwGetTime() * 50.0f, glm::vec3(0.5f, 0.7f, 1.0f));
	cube.draw(defaultShader);

	lightingShader.use();
	lightingShader.setMat4("projection", projection);
	lightingShader.setMat4("view", view);
	lightingShader.setVec3("lightColour", light.diffuse);

	sphere.setPosition(light.position);
	sphere.setScale(glm::vec3(0.5f));
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