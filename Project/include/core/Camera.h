#ifndef CAMERA_H
#define CAMERA_H

#include "GLFW/glfw3.h"

// GLM for Matrix Transformations
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>

// Camera Class follows Singleton Pattern
class Camera
{
public:
	/*
	* @brief Static function that will return the instance of Camera. If one doesn't exist, will create one
	* @return Camera* instance - A pointer to the Camera instance
	*/
	static Camera* GetInstance();

	/*
	* @brief Static function that destroys the instance of Camera.
	*/
	static void DestroyInstance();
	
	/*
	* @brief Destructor of Camera object that destroys the instance of Camera
	*/
	~Camera();

	// Getters for important values
	/*
	* @brief Returns the View Matrix after performing the calculations with Euler Angles 
	* @return const glm::mat4 - const - The View Matrix after calculating with euler angles and the LookAt function
	*/
	glm::mat4 getView() const;
	/*
	* @brief Returns the Position of the Camera as a vector
	* @return const glm::vec3 - const - The position of the Camera
	*/
	glm::vec3 getPos() const;

	/*
	* @brief Returns the Front vector of the Camera
	* @return const glm::vec3 - const - The front vector of the Camera
	*/
	glm::vec3 getFront() const;
	/*
	* @brief Returns a float of the Camera's FOV
	* @return const float fov - const - FOV of the Camera
	*/
	float getFov() const;

	// Set values to change settings.
	/*
	* @brief Setter for adjusting the Sensitivity of the camera
	* @param float s - Sensitivity within the range of 0.0f -> 10.0f
	*/
	void setSensitivity(float s);
	/*
	* @brief Setter for adjusting the FOV of the camera
	* @param float f - FOV within the range of 1.0f -> 50.0f
	*/
	void setFov(float f);

	/*
	* @brief Initialisation function for the Camera that sets up the initial position, and glfw callbacks
	* @param GLFWwindow* w - GLFWwindow ptr for the window you are initialising for
	* @param glm::vec3 p - Initial camera position
	*/
	void initialiseCamera(GLFWwindow* w, glm::vec3 p);
	/*
	* @brief Function which processes all the Camera Movement with Keyboard inputs
	* @param float dt - DeltaTime
	*/
	void processKeyboardMovement(float dt); // Will process WASD Movement, Left Shift, and Left CTRL

private:
	// Private Constructor for Singleton pattern
	/*
	* @brief Private constructor adhering to the singleton pattern
	*/
	Camera();
	static Camera* instance; // Static Instance of Camera for Singleton Pattern

	/*
	* @brief Runs the processMouseMovement Function
	*/
	static void mouse_callback(GLFWwindow* w, double xp, double yp);
	/*
	* @brief Runs the processScroll Function
	*/
	static void scroll_callback(GLFWwindow* w, double xo, double yo);
	/*
	* @brief Runs the processClick function
	*/
	static void mouse_button_callback(GLFWwindow* w, int b, int a, int m);

	/*
	* @brief Calculates the new Front vector (See Camera.cpp for details) based on the (X Position) and (Y Position) of the Mouse
	* @param double xp - X position
	* @param double yp - Y position
 	*/
	void processMouseMovement(double xp, double yp);
	/*
	* @brief Calculates the FOV of camera based on the Y offset (of the scrollwheel)
	* @param double xo - X offset of scrollwheel (This one is not needed outside of linking to glfwSetScrollCallback)
	* @param double yo - Y offset of scrollwheel
	*/
	void processScroll(double xo, double yo);
	/*
	* @brief Processes the mouse click events
	* @param int b - Button
	* @param int a - Action
	* @param int m - Mods
	*/
	void processClick(int b, int a, int m);

	// Private Variables
	GLFWwindow* window = nullptr; // Window pointer

	// Camera Vectors
	glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	// Setting the Values as these are default Variables that don't rely on calculations
	float yaw = 0.0f;
	float pitch = 0.0f;

	bool firstMouse = true; // Make it so you can't click around and snap to a position
	float speed = 2.5f; // Camera Speed

	float fov = 45.0f; // Initial FOV
	float sensitivity = 0.05f; // Initial Sensitivity

	float lastX = 0.0f; // LastX position
	float lastY = 0.0f; // LastY position
};

#endif // CAMERA_H