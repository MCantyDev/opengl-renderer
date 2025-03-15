#include "Application.h"

Application::Application()
	: majorV(4), minorV(6), frameCount(0),
	  deltaTime(0), lastFrame(0), fpsTimer(0), fps(0), 
	  renderWindow(nullptr), uiWindow(nullptr), sceneManager(std::make_unique<SceneManager>())
{
	std::cout << "Setup: Beginning to initialise application requirements" << std::endl;
	if (!initialiseGlfw())	return;

	if (!initialiseWindow(renderWindow, 1200, 800, "OpenGL Renderer")) return;
	if (!initialiseWindow(uiWindow, 400, 800, "Renderer Controls")) return;

	glfwMakeContextCurrent(renderWindow);
	std::cout << "Setup: Window context set to window name: OpenGL Renderer" << std::endl;

	if (!initialiseGlad()) return;
	if (!initialiseImGui()) return;


	setVSync(false);
	glfwSetFramebufferSizeCallback(renderWindow, framebuffer_size_callback);
	glfwSetFramebufferSizeCallback(uiWindow, framebuffer_size_callback);

	sceneManager->initialiseSystems(renderWindow);
	sceneManager->addModel("Robot", "models/Robot/robo.obj");
	sceneManager->addModel("Backpack", "models/Backpack/Backpack.obj", true);

	cube = std::make_shared<Cube>();
	sphere = std::make_shared<Sphere>(0.3f, 30, 30);

	glEnable(GL_DEPTH_TEST);
	std::cout << "Setup: Initialisation of Application Complete" << std::endl;
}

Application::~Application()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(renderWindow);
	glfwDestroyWindow(uiWindow);

	glfwTerminate();
}

void Application::run()
{
	std::cout << "Setup: Proceeding to run Application" << std::endl;
	while (!glfwWindowShouldClose(renderWindow))
	{
		// Main Window Render Function
		renderMainWindow();

		// UI Window Render Function
		renderUIWindow();

		glfwPollEvents();
	}
}


// Initialisation Function
bool Application::initialiseGlfw()
{
	if (!glfwInit())
	{
		std::cout << "Error: Failed to Initialise GLFW" << std::endl;
		return false;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorV);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorV);
	std::cout << "Setup: OpenGL Version set as " << majorV << "." << minorV << std::endl;
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	std::cout << "Setup: OpenGL Core Profile selected" << std::endl;
	glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
	std::cout << "Setup: Successfully Initialised GLFW" << std::endl;
	return true;
}
bool Application::initialiseWindow(GLFWwindow*& window, int width, int height, const char* title)
{
	window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (!window)
	{
		std::cout << "Error: Error occured while trying to create Window" << std::endl;
		return false;
	}
	std::cout << "Setup: Window created successfully" << std::endl;
	return true;
}
bool Application::initialiseGlad()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Error: Error occured while trying to initialised GLAD" << std::endl;
		return false;
	}
	std::cout << "Setup: Successfully Initialised GLAD" << std::endl;
	return true;
}
bool Application::initialiseImGui()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	if (!ImGui_ImplGlfw_InitForOpenGL(uiWindow, true))
	{
		std::cerr << "Error: Error Occured while initialising Dear ImGui GLFW for OpenGL" << std::endl;
		return false;
	}
	if (!ImGui_ImplOpenGL3_Init("#version 130"))
	{
		std::cerr << "Error: Error Occured while initialising Dear ImGui OpenGL Version" << std::endl;
		return false;
	}
	std::cout << "Setup: Successfully Initalised Dear ImGui" << std::endl;
	return true;
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
		oss << "OpenGL Renderer - FPS: " << fps;
		glfwSetWindowTitle(renderWindow, oss.str().c_str());
	}
}

void Application::renderMainWindow()
{
	// Renderer Rendering Logic
	glfwMakeContextCurrent(renderWindow);
	// Input
	calculateFPS();
	processInput(renderWindow);
	sceneManager->cameraMovement(deltaTime);

	// Clearing and Readying Viewport
	glViewport(0, 0, 1200, 800);
	glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	sceneManager->update(1200, 800);
	sceneManager->render();

	glfwSwapBuffers(renderWindow);
}
void Application::renderUIWindow()
{
	// UI Renderering
	glfwMakeContextCurrent(uiWindow);

	// Input
	processInput(uiWindow);

	glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
	glViewport(0, 0, 400, 800);
	glClear(GL_COLOR_BUFFER_BIT);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize));
	ImGui::Begin("Renderer Settings", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);

	std::vector<std::string> models = sceneManager->getModelNames();
	showSpawn(models);

	ImGui::Separator();
	ImGui::Text("Select an Item from the below lists");
	std::vector<std::shared_ptr<Object>> objects = sceneManager->getObjects();
	showObjectComboBox(objects);
	std::vector<std::shared_ptr<Light>> lights = sceneManager->getLights();
	showLightComboBox(lights);
	ImGui::Separator();
	showItemProperties();

	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(uiWindow);
}

void Application::showSpawn(std::vector<std::string> modelNames)
{
	static int selectedSpawn = 0;
	
	std::vector<const char*> spawnNames;
	spawnNames.push_back("Cube");
	spawnNames.push_back("Sphere");

	for (auto& name : modelNames)
	{
		spawnNames.push_back(name.c_str());
	}

	ImGui::Text("Spawn Object");
	ImGui::Combo("Spawn Object", &selectedSpawn, spawnNames.data(), spawnNames.size());

	if (ImGui::Button("Spawn"))
	{
		if (std::string(spawnNames[selectedSpawn]) == "Cube")
			sceneManager->addObject(std::make_shared<Cube>(*cube));
		else if (std::string(spawnNames[selectedSpawn]) == "Sphere")
			sceneManager->addObject(std::make_shared<Sphere>(*sphere));
		else
			sceneManager->addObject(spawnNames[selectedSpawn]);
	}
}
void Application::showObjectComboBox(std::vector<std::shared_ptr<Object>>& objects)
{
	std::vector<const char*> objectNames;

	if (objects.empty())
	{
		ImGui::Text("No Objects Available");
		return;
	}

	for (const auto& object : objects)
	{
		objectNames.push_back(object->name.c_str());
	}

	if (ImGui::Combo("Select Object", &selectedObjectIndex, objectNames.data(), objectNames.size()))
	{
		selectedObject = objects[selectedObjectIndex];
		std::cout << "Selected Object: " << objectNames[selectedObjectIndex] << std::endl;
	}
}

void Application::showLightComboBox(std::vector<std::shared_ptr<Light>>& lights)
{
	std::vector<const char*> lightNames;

	if (lights.empty())
	{
		ImGui::Text("No Lights Available");
		return;
	}

	for (const auto& light : lights)
	{
		lightNames.push_back(light->name.c_str());
	}

	if (ImGui::Combo("Select Light", &selectedLightIndex, lightNames.data(), lightNames.size()))
	{
		selectedLight = lights[selectedLightIndex];
		std::cout << "Selected Light: " << lightNames[selectedLightIndex] << std::endl;
	}
}

void Application::showItemProperties()
{
	if (selectedObject != nullptr)
	{
		ImGui::Text(("Name: " + selectedObject->name).c_str());
		
		ImGui::Separator();
		static int materialIndex = -1;
		std::vector<const char*> materialNames = sceneManager->getMaterialNames();
		if (ImGui::Combo("Material", &materialIndex, materialNames.data(), materialNames.size()))
		{
			selectedObject->setMaterial(materialNames[materialIndex]);
		}
		ImGui::Separator();
		glm::vec3 position = selectedObject->getPosition();
		if (ImGui::DragFloat3("Object Position", &position.x, 0.01f, -100.0f, 100.0f, "%.01f"))
			selectedObject->setPosition(position);
		
		glm::vec4 rotation = glm::vec4(selectedObject->getAxis(), selectedObject->getRotation());
		if (ImGui::DragFloat4("Rotation", &rotation.x, 0.1f, -360.0f, 360.0f, "%.1f"))
			selectedObject->setRotation(rotation.w, glm::vec3(rotation.x, rotation.y, rotation.z));

		glm::vec3 scale = selectedObject->getScale();
		if (ImGui::DragFloat3("Scale", &scale.x, 0.1f, 0.0f, 100.0f, "%.1f"))
			selectedObject->setScale(scale);
		ImGui::Separator();
	}
	if (selectedLight != nullptr)
	{
		ImGui::Text(("Name: " + selectedLight->name).c_str());

		glm::vec3 ambient = selectedLight->ambient;
		glm::vec3 specular = selectedLight->specular;
		glm::vec3 diffuse = selectedLight->diffuse;

		if (ImGui::DragFloat3("Ambient", &ambient.x, 0.01f, 0.0f, 1.0f, "%.01f"))
			selectedLight->ambient = ambient;
		if (ImGui::DragFloat3("Diffuse", &diffuse.x, 0.01f, 0.0f, 1.0f, "%.01f"))
			selectedLight->diffuse = diffuse;
		if (ImGui::DragFloat3("Specular", &specular.x, 0.01f, 0.0f, 1.0f, "%.01f"))
			selectedLight->specular = specular;
		ImGui::Separator();

		if (selectedLight->type == DIRECTIONAL_LIGHT)
		{
			std::shared_ptr<DirectionalLight> light = std::static_pointer_cast<DirectionalLight>(selectedLight);

			glm::vec3 direction = light->direction;

			if (ImGui::DragFloat3("Light Direction", &direction.x, 0.01f, -100.0f, 100.0f, "%.01f"))
				light->direction = direction;
		}

		if (selectedLight->type == POINT_LIGHT)
		{
			std::shared_ptr<PointLight> light = std::static_pointer_cast<PointLight>(selectedLight);

			glm::vec3 position = light->position;
			float constant = light->constant;
			float linear = light->linear;
			float quadratic = light->quadratic;

			if (ImGui::DragFloat3("Light Position", &position.x, 0.01f, -100.0f, 100.0f, "%.01f"))
			{
				light->position = position;
				if (light->mesh)
					light->mesh->setPosition(light->position);
			}
			if (ImGui::InputFloat("Constant", &constant, 0.01f, 0.0f, "%.01f"))
				light->constant = constant;
			if (ImGui::InputFloat("Linear", &linear, 0.01f, 0.0f, "%.01f"))
				light->linear = linear;
			if (ImGui::InputFloat("Quadratic", &quadratic, 0.01f, 0.0f, "%.01f"))
				light->quadratic = quadratic;

			static int meshIndex = -1;
			std::vector<const char*> meshes = { "Cube", "Sphere" };
			if (ImGui::Combo("Mesh", &meshIndex, meshes.data(), meshes.size()))
			{
				if (std::string(meshes[meshIndex]) == "Cube")
				{
					light->mesh = std::make_shared<Cube>(*cube);
					light->mesh->setPosition(light->position);
				}
				if (std::string(meshes[meshIndex]) == "Sphere")
				{
					light->mesh = std::make_shared<Sphere>(*sphere);
					light->mesh->setPosition(light->position);
				}
			}
		}

		if (selectedLight->type == SPOT_LIGHT)
		{
			std::shared_ptr<SpotLight> light = std::static_pointer_cast<SpotLight>(selectedLight);

			glm::vec3 position = light->position;
			glm::vec3 direction = light->direction;
			float constant = light->constant;
			float linear = light->linear;
			float quadratic = light->quadratic;
			float innerCutOff = light->innerCutOff;
			float outerCutOff = light->outerCutOff;

			if (ImGui::DragFloat3("Light Position", &position.x, 0.01f, -100.0f, 100.0f, "%.01f"))
				light->position = position;
			if (ImGui::DragFloat3("Light Direction", &direction.x, 0.01f, -100.0f, 100.0f, "%.01f"))
				light->direction = direction;
			if (ImGui::InputFloat("Constant", &constant, 0.01f, 0.0f, "%.01f"))
				light->constant = constant;
			if (ImGui::InputFloat("Linear", &linear, 0.01f, 0.0f, "%.01f"))
				light->linear = linear;
			if (ImGui::InputFloat("Quadratic", &quadratic, 0.01f, 0.0f, "%.01f"))
				light->quadratic = quadratic;
			if (ImGui::InputFloat("Inner CutOff", &innerCutOff, 0.01f, 0.0f, "%.01f"))
				light->innerCutOff = innerCutOff;
			if (ImGui::InputFloat("Outer CutOff", &outerCutOff, 0.01f, 0.0f, "%.01f"))
				light->outerCutOff = outerCutOff;
		}

		ImGui::Separator();
	}
}