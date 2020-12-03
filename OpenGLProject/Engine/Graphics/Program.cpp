#include "pch.h"
#include "Program.h"


namespace nc {

	bool  Program::Create(const std::string& name, void* null)
	{
		return true;
	}

	void  Program::Destroy()
	{
		if (m_program == 0) {
			return;
		}
		GLint num_shaders = 0;
		glGetProgramiv(m_program, GL_ATTACHED_SHADERS, &num_shaders);
		std::vector<GLuint> shaders{ (GLuint)num_shaders };
		glGetAttachedShaders(m_program, num_shaders, NULL, shaders.data());

		for (GLuint shader : shaders) { 
			glDetachShader(m_program, shader);
			glDeleteShader(shader);
		}

		glDeleteProgram(m_program);
	}

	void  Program::CreateShaderFromFile(const std::string& filename, GLenum shader_type)
	{
		if (m_program == 0) {
			m_program = glCreateProgram();
		}
		std::string source; bool success = ReadFileToString(filename.c_str(), source);
		if (success == false) {
			SDL_Log("Error: Failed to open file (%s).", filename.c_str());
		}
		CreateShaderFromSource(source, shader_type);
	}

	void  Program::CreateShaderFromSource(const std::string& source, GLenum shader_type)
	{
		GLuint shader = glCreateShader(shader_type);

		const char* source_c = source.c_str();
		glShaderSource(shader, 1, &source_c, NULL);
		glCompileShader(shader);

		GLint status;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status); 
		if (status == GL_FALSE) {
			
			GLint length = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
			if (length > 0){
				std::string infoLog(length, ' ');
				glGetShaderInfoLog(shader, length, &length, &infoLog[0]);
				SDL_Log("Error: Failed to compile shader.");
				SDL_Log("Shader Info: %s", infoLog.c_str());
			}
			
			glDeleteShader(shader);
		}
		else {
			
			glAttachShader(m_program, shader);
		}
	}

	void  Program::Link()
	{
		ASSERT(m_program != 0); if (m_linked) return;
		
		glLinkProgram(m_program);
		
		GLint status;
		glGetProgramiv(m_program, GL_LINK_STATUS, &status);
		if (status == GL_FALSE){
			GLint length = 0;
			glGetShaderiv(m_program, GL_INFO_LOG_LENGTH, &length);
			if (length > 0){
				std::string infoLog(length, ' ');
				glGetProgramInfoLog(m_program, length, &length, &infoLog[0]);
				SDL_Log("Error: Failed to link program.");
				SDL_Log("Program Info: %s", infoLog.c_str());
			}glDeleteProgram(m_program);
		}
		else{
			m_linked = true;
		}
	}

	void  Program::Use()
	{
		ASSERT(m_program && m_linked); 
		glUseProgram(m_program);
	}

	void  Program::SetUniform(const std::string& name, float x, float y, float z)
	{
		GLint uniform = GetUniform(name); 
		glUniform3f(uniform, x, y, z);
	}

	void  Program::SetUniform(const std::string& name, const glm::vec2& v2)
	{
		GLint uniform = GetUniform(name);
		glUniform2f(uniform, v2.x, v2.y);
	}

	void  Program::SetUniform(const std::string& name, const glm::vec3& v3)
	{
		GLint uniform = GetUniform(name); 
		glUniform3f(uniform, v3.x, v3.y, v3.z);
	}

	void  Program::SetUniform(const std::string& name, const glm::vec4& v4)
	{
		GLint uniform = GetUniform(name);
		glUniform4f(uniform, v4.x, v4.y, v4.z, v4.w);
	}

	void  Program::SetUniform(const std::string& name, const glm::mat4& mx4)
	{
		GLint uniform = GetUniform(name); 
		glUniformMatrix4fv(uniform, 1, GL_FALSE, glm::value_ptr(mx4));
	}

	void  Program::SetUniform(const std::string& name, const glm::mat3& mx3)
	{
		GLint uniform = GetUniform(name);
		glUniformMatrix3fv(uniform, 1, GL_FALSE, glm::value_ptr(mx3));
	}

	void  Program::SetUniform(const std::string& name, float value)
	{
		GLint uniform = GetUniform(name);
		glUniform1f(uniform, value);
	}

	void  Program::SetUniform(const std::string& name, int value)
	{
		GLint uniform = GetUniform(name); 
		glUniform1i(uniform, value);
	}

	void  Program::SetUniform(const std::string& name, bool value)
	{
		GLint uniform = GetUniform(name); 
		glUniform1i(uniform, value);
	}

	void  Program::SetUniform(const std::string& name, GLuint value)
	{
		GLint uniform = GetUniform(name);
		glUniform1ui(uniform, value);
	}
	GLint Program::GetUniform(const std::string& name)
	{
		auto uniform = m_uniforms.find(name); 
		if (uniform == m_uniforms.end()) {
			m_uniforms[name] = glGetUniformLocation(m_program, name.c_str());
		}
		return m_uniforms[name];
	}
}
