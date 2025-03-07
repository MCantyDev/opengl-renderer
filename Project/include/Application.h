#ifndef APPLICATION_H
#define APPLICATION_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "core/SceneManager.h"

#include <iostream>

class Application
{
public:
	Application();
	~Application();

	void run();
private:
	// Private Variables
	int width, height, majorV, minorV, frameCount; // All integers
	float deltaTime, lastFrame, fpsTimer, fps;
	const char* title;
	GLFWwindow* window;
	std::unique_ptr<SceneManager> sceneManager;
	
	// Initialisation Functions
	bool initialiseGlfw();
	bool initialiseWindow();
	bool initialiseGlad();

	// Callback
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	
	// Input Function
	void processInput(GLFWwindow* window);

	// Private Functions
	void setVSync(bool v);
	void calculateFPS();
};

#endif // APPLICATION_H