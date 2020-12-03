#pragma once
#include "document.h"
#include "istreamwrapper.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "SDL.h"
#include <string>
#include <vector>

namespace nc {

	namespace json {
		bool Load(const std::string& filename, rapidjson::Document& document); 
		bool Get(const rapidjson::Value& value, const std::string& name, int& data);
		bool Get(const rapidjson::Value& value, const std::string& name, float& data); 
		bool Get(const rapidjson::Value& value, const std::string& name, bool& data); 
		bool Get(const rapidjson::Value& value, const std::string& name, std::string& data); 
		bool Get(const rapidjson::Value& value, const std::string& name, Vector2& data); 
		bool Get(const rapidjson::Value& value, const std::string& name, Color& data);
		bool Get(const rapidjson::Value& value, const std::string& name, SDL_Rect& rect);

		bool Get(const rapidjson::Value& value, const std::string& name, std::vector<std::string>& data);
		bool Get(const rapidjson::Value& value, const std::string& name, std::vector<int>& data);

	};

}