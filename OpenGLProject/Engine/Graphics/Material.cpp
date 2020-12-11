#include "pch.h"
#include "Material.h"

namespace nc
{
	void Material::Bind()
	{
		for (Texture& texture : textures)
		{
			texture.Bind();
		}
	}

	void Material::SetProgram(Program& program)
	{
		program.Use();

		program.SetUniform("material.ambient", ambient);
		program.SetUniform("material.diffuse", diffuse);
		program.SetUniform("material.specular", specular);
		program.SetUniform("material.shininess", shininess);
	}
}