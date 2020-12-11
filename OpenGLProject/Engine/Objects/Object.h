#pragma once

namespace nc
{
	class Object
	{
	public:
		Object(const std::string& name, const Transform& transform) : m_name{ name }, m_transform{ transform } {}

		virtual void Update(float dt) {}
		virtual void Draw() {}

		const std::string& name() { return m_name; }
		Transform& transform() { return m_transform; }

		friend class Scene;

	protected:
		std::string m_name;
		Transform m_transform;

		class Scene* m_scene{ nullptr };
	};
}
