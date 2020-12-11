#pragma once

namespace nc {
	struct Transform
	{
		glm::vec3 translation;
		glm::vec3 rotation;
		glm::vec3 scale{ 1 };

		Transform() : translation{ 0 }, rotation{ 0 }, scale{ 1 } {}
		Transform(const glm::vec3& translation, const glm::vec3& rotation = glm::vec3{ 0 }, const glm::vec3& scale = glm::vec3{ 1 }) :
			translation{ translation },
			rotation{ rotation },
			scale{ scale }
		{}

		operator glm::mat4() const
		{
			glm::mat4 scaleMatrix = glm::scale(glm::mat4(1), scale);
			glm::mat4 rotationMatrix = glm::eulerAngleYXZ(rotation.y, rotation.x, rotation.z);
			glm::mat4 translationMatrix = glm::translate(glm::mat4(1), translation);

			return (translationMatrix * rotationMatrix * scaleMatrix);
		}

		Transform& operator = (const glm::mat4 matrix) {
			translation = glm::vec3{ matrix[3] };
			scale = glm::vec3{ matrix[0][0], matrix[1][1], matrix[2][2] };
			glm::extractEulerAngleYXZ(matrix, rotation.y, rotation.x, rotation.z);

			return *this;
		}
	};
}