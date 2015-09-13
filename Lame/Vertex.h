#pragma once

#include <GL/glew.h>

namespace lame {

	struct Position
	{
		float x;
		float y;
	};

	struct Color
	{
		Color() : r(0), g(0), b(0), a(0) {}
		Color(GLubyte R, GLubyte G, GLubyte B, GLubyte A) :
			r(R), g(G), b(B), a(A) {}

		static inline Color black() { return Color(0,   0,   0,   255); }
		static inline Color white() { return Color(255, 255, 255, 255); }
		static inline Color red()   { return Color(255, 0,   0,   255); }
		static inline Color green() { return Color(0,   255, 0,   255); }
		static inline Color blue()  { return Color(0,   0,   255, 255); }

		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;
	};

	struct UV
	{
		float u;
		float v;
	};

	struct Vertex
	{
		Position position;
		Color color;
		UV uv;

		void setPosition(float x, float y)
		{
			position.x = x;
			position.y = y;
		}

		void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
		{
			color.r = r;
			color.g = g;
			color.b = b;
			color.a = a;
		}

		void setUV(float u, float v)
		{
			uv.u = u;
			uv.v = v;
		}
	};

}