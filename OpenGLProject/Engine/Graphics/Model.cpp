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

}
