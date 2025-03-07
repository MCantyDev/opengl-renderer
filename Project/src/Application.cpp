#include "Application.h"

Application::Application()
	: width(1200), height(800), majorV(4), minorV(6), frameCount(0),
	  deltaTime(0), lastFrame(0), fpsTimer(0), fps(0), 
	  title("OpenGL Renderer"),
	  window(nullptr), sceneManager(std::make_unique<SceneManager>())
{
	std::cout << "Setup: Beginning to initialise application requirements" << std::endl;
	if (!initialiseGlfw())	return;
	if (!initialiseWindow()) return;
	if (!initialiseGlad()) return;

	setVSync(false);
	glViewport(0, 0, width, height);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	sceneManager->initialiseSystems(window);
	sceneManager->addObject("robot", "models/Robot/robo.obj");

	glEnable(GL_DEPTH_TEST);
	std::cout << "Setup: Initialisation of Application Complete" << std::endl;
}

Application::~Application()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Application::run()
{
	std::cout << "Setup: Proceeding to run Application" << std::endl;
	while (!glfwWindowShouldClose(window))
	{
		calculateFPS();
		processInput(window);
		sceneManager->cameraMovement(deltaTime);

		glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		sceneManager->editObject(0, { {"scale", glm::vec3(0.2f)}, {"position", glm::vec3(0.0f)}, {"rotation", Rotation(-45.0f, glm::vec3(0.0f, 1.0f, 0.0f))}, {"material", "RoboMaterial"} });
		sceneManager->editLight(0, DIRECTIONAL_LIGHT, { {"ambient", glm::vec3(0.0f)}, {"diffuse", glm::vec3(1.0f, 1.0f, 1.0f)} });

		sceneManager->update(width, height);
		sceneManager->render();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
}

// Initialisation Function
bool Application::initialiseGlfw()
{
	if (!glfwInit())
	{
		std::cout << "Error: Failed to Initialise GLFW" << std::endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorV);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorV);
	std::cout << "Setup: OpenGL Version set as " << majorV << "." << minorV << std::endl;
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	std::cout << "Setup: OpenGL Core Profile selected" << std::endl;
	std::cout << "Setup: Successfully Initialised GLFW" << std::endl;
}
bool Application::initialiseWindow()
{
	window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (!window)
	{
		std::cout << "Error: Error occured while trying to create Window" << std::endl;
		return -1;
	}
	std::cout << "Setup: Window created successfully" << std::endl;
	glfwMakeContextCurrent(window);
	std::cout << "Setup: Window context set to window name: " << title << std::endl;
}
bool Application::initialiseGlad()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Error: Error occured while trying to initialised GLAD" << std::endl;
		return -1;
	}
	std::cout << "Setup: Successfully Initialised GLAD" << std::endl;
}

// Callback Function
void Application::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// Input Function
void Application::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		std::cout << "Closing: Closing Window" << std::endl;
		glfwSetWindowShouldClose(window, true);
	}
}
void Application::setVSync(bool v)
{
	glfwSwapInterval(v);
	std::cout << "Functional: V-Sync " << ((v) ? "Activated" : "Deactivated") << std::endl;
}

void Application::calculateFPS()
{
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
		oss << title << " - FPS: " << fps;
		glfwSetWindowTitle(window, oss.str().c_str());
	}
}