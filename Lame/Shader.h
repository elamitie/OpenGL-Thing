#pragma once

#include <GL/glew.h>
#include <string>
#include <glm/glm.hpp>

namespace lame {

	class Shader
	{
	public:
		Shader();
		~Shader();

		void Compile(const std::string& vertPath, const std::string& fragPath);
		void Link();
		void AddAttribute(const std::string& attrib);

		GLint GetUniformLocation(const std::string& uniformName);

		void Enable();
		void Disable();

		void SetUniform(const std::string& name, GLint data);
		void SetUniform(const std::string& name, GLint* data, GLsizei count);
		void SetUniform(const std::string& name, GLfloat data);
		void SetUniform(const std::string& name, GLfloat* data, GLsizei count);
		void SetUniform(const std::string& name, const glm::vec2& vector);
		void SetUniform(const std::string& name, const glm::vec3& vector);
		void SetUniform(const std::string& name, const glm::vec4& vector);
		void SetUniform(const std::string& name, const glm::mat4& matrix);

	private:
		void compileShader(const std::string& path, GLuint& id);

	private:
		GLuint m_Program;
		GLuint m_Vert;
		GLuint m_Frag;
		int    m_NumAttributes;
	};

}

