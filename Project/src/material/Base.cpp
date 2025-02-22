#include "material/Base.h"

Base::Base()
	: ambient(glm::vec3(0.2f)), diffuse(glm::vec3(0.5f)), specular(glm::vec3(0.35f))
{

}

// Custom Constructor for Base
Base::Base(glm::vec3 a, glm::vec3 d, glm::vec3 s)
	: ambient(a), diffuse(d), specular(s)
{

}