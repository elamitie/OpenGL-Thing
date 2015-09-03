#include "Shader.h"
#include <iostream>
#include <fstream>
#include <vector>

namespace lame {

	Shader::Shader()
		: m_Program(0), m_Vert(0), m_Frag(0), m_NumAttributes(0)
	{
	}

	Shader::~Shader()
	{
	}

	void Shader::Compile(const std::string& vertPath, const std::string& fragPath)
	{
		m_Program = glCreateProgram();

		m_Vert = glCreateShader(GL_VERTEX_SHADER);
		if (m_Vert == 0)
			std::cout << "Vertex shader failed to be created" << std::endl;

		m_Frag = glCreateShader(GL_FRAGMENT_SHADER);
		if (m_Frag == 0)
			std::cout << "Fragment shader failed to be created" << std::endl;

		compileShader(vertPath, m_Vert);
		compileShader(fragPath, m_Frag);
	}

	void Shader::Link()
	{
		glAttachShader(m_Program, m_Vert);
		glAttachShader(m_Program, m_Frag);

		glLinkProgram(m_Program);

		GLint isLinked = 0;
		glGetProgramiv(m_Program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_Program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> errorLog(maxLength);
			glGetProgramInfoLog(m_Program, maxLength, &maxLength, &errorLog[0]);

			glDeleteProgram(m_Program);
			glDeleteShader(m_Vert);
			glDeleteShader(m_Frag);

			std::printf("%s\n", &errorLog[0]);
			return;
		}

		glDetachShader(m_Program, m_Vert);
		glDetachShader(m_Program, m_Frag);
		glDeleteShader(m_Vert);
		glDeleteShader(m_Frag);
	}

	void Shader::AddAttribute(const std::string& attrib)
	{
		glBindAttribLocation(m_Program, m_NumAttributes++, attrib.c_str());
	}

	GLint Shader::GetUniformLocation(const std::string& uniformName)
	{
		GLint location = glGetUniformLocation(m_Program, uniformName.c_str());
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

	void Shader::Enable()
	{
		glUseProgram(m_Program);
		for (int i = 0; i < m_NumAttributes; i++)
			glEnableVertexAttribArray(i);
	}

	void Shader::Disable()
	{
		glUseProgram(0);
		for (int i = 0; i < m_NumAttributes; i++)
			glDisableVertexAttribArray(i);
	}

	void Shader::SetUniform(const std::string& name, GLint data)
	{
		GLint location = this->GetUniformLocation(name);
		glUniform1i(location, data);
	}

	void Shader::SetUniform(const std::string& name, GLint* data, GLsizei count)
	{
		GLint location = this->GetUniformLocation(name);
		glUniform1iv(location, count, data);
	}

	void Shader::SetUniform(const std::string& name, GLfloat data)
	{
		GLint location = this->GetUniformLocation(name);
		glUniform1f(location, data);
	}

	void Shader::SetUniform(const std::string& name, GLfloat* data, GLsizei count)
	{
		GLint location = this->GetUniformLocation(name);
		glUniform1fv(location, count, data);
	}

	void Shader::SetUniform(const std::string& name, const glm::vec2& vector)
	{
		GLint location = this->GetUniformLocation(name);
		glUniform2f(location, vector.x, vector.y);
	}

	void Shader::SetUniform(const std::string& name, const glm::vec3& vector)
	{
		GLint location = this->GetUniformLocation(name);
		glUniform3f(location, vector.x, vector.y, vector.z);
	}

	void Shader::SetUniform(const std::string& name, const glm::vec4& vector)
	{
		GLint location = this->GetUniformLocation(name);
		glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
	}

	void Shader::SetUniform(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = this->GetUniformLocation(name);
		glUniformMatrix4fv(location, 1, GL_FALSE, &(matrix[0][0]));
	}

}
