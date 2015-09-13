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

		void compile(const std::string& vertPath, const std::string& fragPath);
		void link();
		void addAttribute(const std::string& attrib);

		GLint getUniformLocation(const std::string& uniformName);

		void enable();
		void disable();

		void setUniform(const std::string& name, GLint data);
		void setUniform(const std::string& name, GLint* data, GLsizei count);
		void setUniform(const std::string& name, GLfloat data);
		void setUniform(const std::string& name, GLfloat* data, GLsizei count);
		void setUniform(const std::string& name, const glm::vec2& vector);
		void setUniform(const std::string& name, const glm::vec3& vector);
		void setUniform(const std::string& name, const glm::vec4& vector);
		void setUniform(const std::string& name, const glm::mat4& matrix);

	private:
		void compileShader(const std::string& path, GLuint& id);

	private:
		GLuint m_program;
		GLuint m_vert;
		GLuint m_frag;
		int    m_numAttributes;
	};

}

