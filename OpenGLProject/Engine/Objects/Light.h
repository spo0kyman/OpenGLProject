#pragma once
#include "Object.h"
#include "Engine/Graphics/Program.h"

namespace nc
{
	class Light : public Object
	{
	public:
		Light(const std::string& name, const Transform& transform, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular) :
			Object{ name, transform },
			ambient{ ambient },
			diffuse{ diffuse },
			specular{ specular }
		{}
		 
		void SetProgram(Program& program);

	public:
		glm::vec3 ambient = glm::vec3(0);
		glm::vec3 diffuse = glm::vec3(1);
		glm::vec3 specular = glm::vec3(1);
	};
}
