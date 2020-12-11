#include "pch.h"
#include "Model.h"

namespace nc {

	bool Model::Load(const std::string& filename, std::vector<glm::vec3>& positions, std::vector<glm::vec3>& normals, std::vector<glm::vec2>& texcoords)
	{
		std::vector<glm::vec3> model_positions;
		std::vector<glm::vec3> model_normals;
		std::vector<glm::vec2> model_texcoords;
		std::ifstream stream(filename, std::ios::binary);
		if (!stream.is_open()) {
			SDL_Log("Error opening model file: %s", filename.c_str());
			return false;
		}

		std::string line;
		while (std::getline(stream, line)) {
			if (line.substr(0, 2) == "v ") {
				std::istringstream sstream{ line.substr(2) };
				glm::vec3 position;
				sstream >> position.x;
				sstream >> position.y;
				sstream >> position.z;

				model_positions.push_back(position);
			}
			else if (line.substr(0, 3) == "vn ") {
				std::istringstream sstream{ line.substr(3) };
				glm::vec3 normal;
				sstream >> normal.x;
				sstream >> normal.y;
				sstream >> normal.z;

				model_normals.push_back(normal);
			}
			else if (line.substr(0, 3) == "vt ") {
				std::istringstream sstream{ line.substr(3) };
				glm::vec2 texcoord;
				sstream >> texcoord.x;
				sstream >> texcoord.y;

				model_texcoords.push_back(texcoord);
			}
			else if (line.substr(0, 2) == "f ") {
				std::istringstream sstream{ line.substr(2) };
				std::string str;
				while (std::getline(sstream, str, ' ')) {
					std::istringstream sstream(str);
					std::string indexString;

					size_t i = 0;
					unsigned int index[3] = { 0, 0, 0 };
					while (std::getline(sstream, indexString, '/')) {
						if (!indexString.empty()) {
							std::istringstream indexStream{ indexString };
							indexStream >> index[i];
						}
						i++;
					}

					if (index[0])
					{
						glm::vec3 position = model_positions[index[0] - 1];
						positions.push_back(position);
					}

					if (index[1])
					{
						glm::vec2 texcoord = model_texcoords[index[1] - 1];
						texcoords.push_back(texcoord);
					}

					if (index[2])
					{
						glm::vec3 normal = model_normals[index[2] - 1];
						normals.push_back(normal);
					}
				}	
			}
		}

		stream.close();

		return true;
	}

	VertexArray Model::Load(const std::string& filename)
	{
		nc::VertexArray vertexArray;
		vertexArray.Create("vertex");

		std::vector<glm::vec3> positions;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> texcoords;
		nc::Model::Load(filename, positions, normals, texcoords);

		if (!positions.empty()) {
			vertexArray.CreateBuffer(positions.size() * sizeof(glm::vec3), positions.size(), positions.data());
			vertexArray.SetAttribute(0, 3, 0, 0);
		}
		if (!normals.empty()) {
			vertexArray.CreateBuffer(normals.size() * sizeof(glm::vec3), normals.size(), normals.data());
			vertexArray.SetAttribute(1, 3, 0, 0);
		}
		if (!texcoords.empty()) {
			vertexArray.CreateBuffer(texcoords.size() * sizeof(glm::vec2), texcoords.size(), texcoords.data());
			vertexArray.SetAttribute(2, 2, 0, 0);
		}

		return vertexArray;
	}

	void Model::Draw()
	{
		m_program.Use();
		m_material.SetProgram(m_program);

		Camera* camera = m_scene->Get<Camera>("camera");
		ASSERT(camera != nullptr);

		glm::mat4 mvp = camera->projection() * camera->view() * (glm::mat4)m_transform;
		m_program.SetUniform("mvp", mvp);
		glm::mat4 model_view = camera->view() * (glm::mat4)m_transform; 
		m_program.SetUniform("model_view", model_view);

		m_vertexArray.Draw(GL_TRIANGLES);
	}

}
