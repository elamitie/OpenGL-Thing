#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include "Vertex.h"
#include "Texture.h"

namespace lame {
	
	enum class GlyphSortType 
	{
		NONE,
		FRONT_TO_BACK,
		BACK_TO_FRONT,
		TEXTURE
	};


	class Glyph
	{
	public:
		Glyph(){};

		Texture texture;
		float depth;

		Vertex topLeft;
		Vertex bottomLeft;
		Vertex topRight;
		Vertex bottomRight;

	private:
	};


	class RenderBatch
	{
	public:
		RenderBatch(GLuint offset, GLuint numVerts, Texture texture) : mOffset(offset), mNumVerts(numVerts), mTexture(texture) {}

		GLuint mOffset;
		GLuint mNumVerts;
		Texture mTexture;

	private:
	};


	class SpriteBatch
	{
	public:
		SpriteBatch();
		~SpriteBatch();

		void init();

		void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
		void end();

		void draw(const glm::vec4& destRect, Texture texture, float depth, const Color& color);
		void renderBatches();

	private:
		void createRenderBatches();
		void createVertexArray();
		void sortGlyphs();
		
		static bool compareFrontToBack(Glyph* a, Glyph* b);
		static bool compareBackToFront(Glyph* a, Glyph* b);
		static bool compareTexture(Glyph* a, Glyph* b);

	private:
		GlyphSortType            m_sortType;
		glm::vec4				 m_defaultUV;
		GLuint                   m_vbo;
		GLuint                   m_vao;
		std::vector<Glyph*>      m_glyphs;
		std::vector<RenderBatch> m_batches;
	};

}

