#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include "Vertex.h"

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

		GLuint texture;
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
		RenderBatch(GLuint offset, GLuint numVerts, GLuint texture) : mOffset(offset), mNumVerts(numVerts), mTexture(texture) {}

		GLuint mOffset;
		GLuint mNumVerts;
		GLuint mTexture;

	private:
	};


	class SpriteBatch
	{
	public:
		SpriteBatch();
		~SpriteBatch();

		void Init();

		void Begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
		void End();

		void Draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color);
		void RenderBatches();

	private:
		void createRenderBatches();
		void createVertexArray();
		void sortGlyphs();
		
		static bool compareFrontToBack(Glyph* a, Glyph* b);
		static bool compareBackToFront(Glyph* a, Glyph* b);
		static bool compareTexture(Glyph* a, Glyph* b);

		GlyphSortType            m_SortType;

		GLuint                   m_Vbo;
		GLuint                   m_Vao;
		std::vector<Glyph*>      m_Glyphs;
		std::vector<RenderBatch> m_Batches;
	};

}

