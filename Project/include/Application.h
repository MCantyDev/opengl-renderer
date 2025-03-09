#ifndef APPLICATION_H
#define APPLICATION_H

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

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
	int majorV, minorV, frameCount; // All integers
	float deltaTime, lastFrame, fpsTimer, fps;
	GLFWwindow* renderWindow;
	GLFWwindow* uiWindow;
	std::unique_ptr<SceneManager> sceneManager;

	// Quick Fix for Problem
	std::shared_ptr<Cube> cube = nullptr;
	std::shared_ptr<Sphere> sphere = nullptr;

	// Selected Item
	std::shared_ptr<Object> selectedObject = nullptr;
	std::shared_ptr<Light> selectedLight = nullptr;
	int selectedObjectIndex = -1;
	int selectedLightIndex = -1;
	
	// Initialisation Functions
	bool initialiseGlfw();
	bool initialiseWindow(GLFWwindow*& window, int width, int height, const char* title);
	bool initialiseGlad();
	bool initialiseImGui();

	// Callback
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	
	// Input Function
	void processInput(GLFWwindow* window);

	// Private Functions
	void setVSync(bool v);
	void calculateFPS();

	// Window Render Functions
	void renderMainWindow();
	void renderUIWindow();

	// ImGui Render Functions
	void showSpawn(std::vector<std::string> modelNames);
	void showObjectComboBox(std::vector<std::shared_ptr<Object>>& objects);
	void showLightComboBox(std::vector<std::shared_ptr<Light>>& lights);
	void showItemProperties();
};

#endif // APPLICATION_H