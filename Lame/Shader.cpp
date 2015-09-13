#include "Shader.h"
#include <iostream>
#include <fstream>
#include <vector>

namespace lame {

	Shader::Shader()
		: m_program(0), m_vert(0), m_frag(0), m_numAttributes(0)
	{
	}

	Shader::~Shader()
	{
	}

	void Shader::compile(const std::string& vertPath, const std::string& fragPath)
	{
		m_program = glCreateProgram();

		m_vert = glCreateShader(GL_VERTEX_SHADER);
		if (m_vert == 0)
			std::cout << "Vertex shader failed to be created" << std::endl;

		m_frag = glCreateShader(GL_FRAGMENT_SHADER);
		if (m_frag == 0)
			std::cout << "Fragment shader failed to be created" << std::endl;

		compileShader(vertPath, m_vert);
		compileShader(fragPath, m_frag);
	}

	void Shader::link()
	{
		glAttachShader(m_program, m_vert);
		glAttachShader(m_program, m_frag);

		glLinkProgram(m_program);

		GLint isLinked = 0;
		glGetProgramiv(m_program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> errorLog(maxLength);
			glGetProgramInfoLog(m_program, maxLength, &maxLength, &errorLog[0]);

			glDeleteProgram(m_program);
			glDeleteShader(m_vert);
			glDeleteShader(m_frag);

			std::printf("%s\n", &errorLog[0]);
			return;
		}

		glDetachShader(m_program, m_vert);
		glDetachShader(m_program, m_frag);
		glDeleteShader(m_vert);
		glDeleteShader(m_frag);
	}

	void Shader::addAttribute(const std::string& attrib)
	{
		glBindAttribLocation(m_program, m_numAttributes++, attrib.c_str());
	}

	GLint Shader::getUniformLocation(const std::string& uniformName)
	{
		GLint location = glGetUniformLocation(m_program, uniformName.c_str());
		if (location == GL_INVALID_INDEX)
			std::cout << "could not find uniform name" << std::endl;
		return location;
	}

	void Shader::compileShader(const std::string& path, GLuint& id)
	{
		std::ifstream file(path);
		std::string filecontents = "";
		std::string line;

		while (std::getline(file, line))
			filecontents += line + "\n";

		file.close();

		const char* contents = filecontents.c_str();
		glShaderSource(id, 1, &contents, nullptr);
		glCompileShader(id);

		GLint success = 0;
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);

		if (success == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> errorLog(maxLength);
			glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

			std::printf("%s\n", &errorLog[0]);

			glDeleteShader(id);
			return;
		}
	}

	void Shader::enable()
	{
		glUseProgram(m_program);
		for (int i = 0; i < m_numAttributes; i++)
			glEnableVertexAttribArray(i);
	}

	void Shader::disable()
	{
		glUseProgram(0);
		for (int i = 0; i < m_numAttributes; i++)
			glDisableVertexAttribArray(i);
	}

	void Shader::setUniform(const std::string& name, GLint data)
	{
		GLint location = this->getUniformLocation(name);
		glUniform1i(location, data);
	}

	void Shader::setUniform(const std::string& name, GLint* data, GLsizei count)
	{
		GLint location = this->getUniformLocation(name);
		glUniform1iv(location, count, data);
	}

	void Shader::setUniform(const std::string& name, GLfloat data)
	{
		GLint location = this->getUniformLocation(name);
		glUniform1f(location, data);
	}

	void Shader::setUniform(const std::string& name, GLfloat* data, GLsizei count)
	{
		GLint location = this->getUniformLocation(name);
		glUniform1fv(location, count, data);
	}

	void Shader::setUniform(const std::string& name, const glm::vec2& vector)
	{
		GLint location = this->getUniformLocation(name);
		glUniform2f(location, vector.x, vector.y);
	}

	void Shader::setUniform(const std::string& name, const glm::vec3& vector)
	{
		GLint location = this->getUniformLocation(name);
		glUniform3f(location, vector.x, vector.y, vector.z);
	}

	void Shader::setUniform(const std::string& name, const glm::vec4& vector)
	{
		GLint location = this->getUniformLocation(name);
		glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
	}

	void Shader::setUniform(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = this->getUniformLocation(name);
		glUniformMatrix4fv(location, 1, GL_FALSE, &(matrix[0][0]));
	}

}
