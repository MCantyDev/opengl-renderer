#include "camera/Camera.h"

// Singleton Pattern
Camera* Camera::instance = nullptr;

// Constructor
Camera::Camera()
{
	std::cout << "Setup: Camera created" << std::endl;
}

// Destructor
Camera::~Camera()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
		std::cout << "Closing: Camera destroyed" << std::endl;
	}
}

Camera* Camera::GetInstance()
{
	// Checks if Instance is nullptr
	if (instance == nullptr)
		instance = new Camera(); // Creates an new Camera object and gives it to instance
	
	return instance; // Returns instance of already created, or newly created camera based on the instance ptr
}

void Camera::DestroyInstance()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
		std::cout << "Process: Camera destroyed" << std::endl;
	}
}

void Camera::initialiseCamera(GLFWwindow* w, glm::vec3 p)
{
	// Checks if instance exists (is not nullptr)
	if (instance)
	{
		std::cout << "Setup: Camera Instance found" << std::endl;
		window = w; // Gives the camera the window instance

		std::cout << "Setup: Setting Initial Position" << std::endl;
		pos = p; // Gives the camera its initial position

		std::cout << "Setup: Proceeding to bind Callbacks" << std::endl;
		std::cout << "Setup: Mouse Move Callback Bound" << std::endl;
		glfwSetCursorPosCallback(window, Camera::mouse_callback); // Binds the Cursor Position Callback (allowing for mouse movement)

		std::cout << "Setup: Scroll Callback Bound" << std::endl;
		glfwSetScrollCallback(window, Camera::scroll_callback); // Binds the Scroll callback (allowing for zoom in and out)

		std::cout << "Setup: Click Callback Bound" << std::endl;
		glfwSetMouseButtonCallback(window, Camera::mouse_button_callback); // Binds the Mouse Button callback (allowing for mouse clicks to be processed)
	}
	else
	{
		std::cerr << "Error: No Instance of Camera" << std::endl; // Happens if Instance is nullptr
	}
}

// Get camera data
glm::mat4 Camera::getView() const
{
	return glm::lookAt(pos, pos + front, up);
}

glm::vec3 Camera::getPos() const
{
	return pos;
}

float Camera::getFov() const
{
	return fov;
}

// Set Camera Settings
void Camera::setSensitivity(float s)
{
	// Checks if Sensitivity given is in range
	if (s < 1 || s > 10.0f)
	{
		std::cout << "Error: Sensitivity must be within range of 1 - 10" << std::endl;
		return;
	}
	// If so changes Sensitivity in place
	sensitivity = s / 100;
}

void Camera::setFov(float f)
{
	// Checks if FOV given is in range 
	if (f < 1.0f || f > 50.0f)
	{
		std::cout << "Error: FOV must be within range of 1 - 50" << std::endl;
		return;
	}
	// If so changes FOV in place
	fov = f;
}

// Camera Movement with Keyboard
void Camera::processKeyboardMovement(float dt)
{
	// Finding a normalised speed based off deltaTime to move in a consistant way no matter the FPS
	float cameraSpeed = (float)(speed * dt);

	// WASD Movement
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		// Calc is Pos + (normalisedSpeed * (0, 0, -1)) 
		pos += cameraSpeed * front;

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		// Calc is Pos - (normalisedSpeed * (0, 0, -1)) 
		pos -= cameraSpeed * front; 

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		// Cool thing where if A is front and B is up. 
		// You can do					New Vector			Our Case Results in vec3
		// ((Ay * Bz) - (Az * By)			X					(	1	),
		//  (Az * Bx) - (Ax * Bz)			Y					(	0	),
		//  (Ax * By) - (Ay * Bx))			Z					(	0	)
		// Taking this resulting vector and subtracting it from pos moves the camera to the Left
		pos -= cameraSpeed * glm::normalize(glm::cross(front, up)); 

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		// Taking this resulting vector and adding it to pos moves the camera to the right
		pos += cameraSpeed * glm::normalize(glm::cross(front, up));

	// Up and Down with Space and left CTRL
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		// Calc is Pos + (normalisedSpeed) * (0, 1, 0))
		pos += cameraSpeed * up;

	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		// Calc is Pos - (normalisedSpeed) * (0, 1, 0))
		pos -= cameraSpeed * up;

	// Shift = SPEED!
	// If Shift is Pressed doubles speed, if not halfs it
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		speed = 5.0f;

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
		speed = 2.5f;
}

// Processes
void Camera::processMouseMovement(double xp, double yp)
{
	// If Left Click is not being press
	if (glfwGetInputMode(window, GLFW_CURSOR) != GLFW_CURSOR_DISABLED)
		// Leave the function as we dont want to process Movement
		return;

	// First Mouse is the First Click. This is setup to stop the abrupt snapping no matter where you click from
	if (firstMouse)
	{
		lastX = xp; // Sets mouses last xPos to current xPos
		lastY = yp; // Sets mouses last yPos to current yPos
		firstMouse = false; // Sets first mouse to false as we have clicked
		return; // Returns out to skip the first render
	}

	float xOffset = xp - lastX; // Finds xOffset (how much to move on the X axis) by checking the distance between the current xpos and the last xpos
	float yOffset = yp - lastY; // Same thing with yOffset
	lastX = xp; lastY = yp; // Updates lastX and lastY

	// Finds the proper the x and y offset by multiplying the sensitivity
	xOffset *= sensitivity;
	yOffset *= sensitivity;

	// Adds offset to both the pitch and yaw
	pitch += yOffset;
	yaw += xOffset;

	// Clamping the yaw between 0 and 360 as 360 is a full turn so 360 would be the same as 0
	if (yaw > 360.0f) yaw -= 360.0f;
	if (yaw < 0.0f) yaw += 360.0f;

	// Clamping the pitch between -89 and 89 - Makes a flip not possible
	if (pitch > 89.0f) pitch = 89.0f;
	if (pitch < -89.0f) pitch = -89.0f;

	// Works out the New Camera Front vector
	glm::vec3 direction;

	// Using Trig to find x, y, and z axis
	// https://stackoverflow.com/questions/1568568/how-to-convert-euler-angles-to-directional-vector
	direction.x =  sin(glm::radians(yaw)) * cos(glm::radians(pitch));  // X-axis direction
	direction.y =  sin(glm::radians(-pitch));  // Y-axis direction (up/down)
	direction.z = -cos(glm::radians(yaw)) * cos(glm::radians(pitch));

	// Normalising to a unit direction vector (length of 1) for consistent camera movement
	front = glm::normalize(direction);
}

void Camera::processScroll(double xo, double yo)
{
	// Removing the Y Offset as FOV works in inverse (smaller number more zoom)
	fov -= (float)yo;

	// Clamping the FOV between 1 and 50
	if (fov < 1.0f) fov = 1.0f;
	if (fov > 50.0f) fov = 50.0f;
}

void Camera::processClick(int b, int a, int m)
{
	// If user clicks Right Mouse Button
	if (b == GLFW_MOUSE_BUTTON_RIGHT && a == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // Disables/Hides Cursor
	}

	// If user lets go of Right Mouse Button
	if (b == GLFW_MOUSE_BUTTON_RIGHT && a == GLFW_RELEASE)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); // Sets Cursor back to being Visable
		firstMouse = true; // Reset First Mouse so we dont jump based on the lastX and lastY positions
	}
}

// Callbacks
// I would need to check if there is an instance, However im already checking in the InitialiseCamera (which links these functions) so that check is redundant.
void Camera::scroll_callback(GLFWwindow* w, double xo, double yo)
{
	instance->processScroll(xo, yo);
}

void Camera::mouse_callback(GLFWwindow* w, double xp, double yp)
{
	instance->processMouseMovement(xp, yp);
}
void Camera::mouse_button_callback(GLFWwindow* w, int b, int a, int m)
{
	instance->processClick(b, a, m);
}
