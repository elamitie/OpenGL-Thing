#pragma once

#include <GL/glew.h>
#include <string>

namespace lamengine {

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

	private:
		void compileShader(const std::string& path, GLuint& id);

		GLuint mProgram;
		GLuint mVert;
		GLuint mFrag;
		int    mNumAttributes;
	};

}

