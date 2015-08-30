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

		void init();

		void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
		void end();

		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color);
		void renderBatch();

	private:
		void createRenderBatches();
		void createVertexArray();
		void sortGlyphs();
		
		static bool compareFrontToBack(Glyph* a, Glyph* b);
		static bool compareBackToFront(Glyph* a, Glyph* b);
		static bool compareTexture(Glyph* a, Glyph* b);

		GlyphSortType mSortType;

		GLuint mvbo;
		GLuint mvao;
		std::vector<Glyph*> mGlyphs;
		std::vector<RenderBatch> mBatches;
	};

}

