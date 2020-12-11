#pragma once
#include "Object.h"
#include "Engine/Engine.h"

namespace nc
{
	class Scene
	{
	public:
		Scene(class Engine* engine) : m_engine{ engine } {}

		virtual void Update(float dt);
		virtual void Draw();

		void Add(Object* object)
		{
			object->m_scene = this;
			m_objects.push_back(object);
		}

		template<typename T>
		T* Get(const std::string& name)
		{
			for (Object* object : m_objects)
			{
				if (object->m_name == name)
				{
					return dynamic_cast<T*>(object);
				}
			}

			return nullptr;
		}

		template<typename T>
		std::vector<T*> Get()
		{
			std::vector<T*> objects;
			for (Object* object : m_objects)
			{
				if (dynamic_cast<T*>(object) != nullptr)
				{
					objects.push_back(dynamic_cast<T*>(object));
				}
			}

			return objects;
		}

		Engine* engine() { return m_engine; }

	protected:
		std::vector<class Object*> m_objects;
		class Engine* m_engine{ nullptr };
	};

}
