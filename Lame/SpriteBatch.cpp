#include "SpriteBatch.h"
#include <algorithm>

namespace lame {

	SpriteBatch::SpriteBatch() : mvbo(0), mvao(0)
	{
	}

	SpriteBatch::~SpriteBatch()
	{
	}

	void SpriteBatch::init()
	{
		createVertexArray();
	}

	void SpriteBatch::begin(GlyphSortType sortType /* GlyphSortType::TEXTURE */)
	{
		mSortType = sortType;
		mBatches.clear();

		for (auto& g : mGlyphs)
			delete g;

		mGlyphs.clear();
	}

	void SpriteBatch::end()
	{
		sortGlyphs();
		createRenderBatches();
	}

	void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color)
	{
		Glyph* glyph = new Glyph;
		glyph->texture = texture;
		glyph->depth = depth;

		glyph->topLeft.color = color;
		glyph->topLeft.setPosition(destRect.x, destRect.y + destRect.w);
		glyph->topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

		glyph->bottomLeft.color = color;
		glyph->bottomLeft.setPosition(destRect.x, destRect.y);
		glyph->bottomLeft.setUV(uvRect.x, uvRect.y);

		glyph->bottomRight.color = color;
		glyph->bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
		glyph->bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

		glyph->topRight.color = color;
		glyph->topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
		glyph->topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

		mGlyphs.push_back(glyph);
	}

	void SpriteBatch::renderBatch()
	{
		glBindVertexArray(mvao);

		for (int i = 0; i < mBatches.size(); i++)
		{
			glBindTexture(GL_TEXTURE_2D, mBatches[i].mTexture);
			glDrawArrays(GL_TRIANGLES, mBatches[i].mOffset, mBatches[i].mNumVerts);
		}

		glBindVertexArray(0);
	}

	void SpriteBatch::createRenderBatches()
	{
		std::vector<Vertex> vertices;
		vertices.resize(mGlyphs.size() * 6);

		if (mGlyphs.empty())
			return;

		int offset = 0;
		int currVert = 0;
		mBatches.emplace_back(offset, 6, mGlyphs[0]->texture);
		vertices[currVert++] = mGlyphs[0]->topLeft;
		vertices[currVert++] = mGlyphs[0]->bottomLeft;
		vertices[currVert++] = mGlyphs[0]->bottomRight;
		vertices[currVert++] = mGlyphs[0]->bottomRight;
		vertices[currVert++] = mGlyphs[0]->topRight;
		vertices[currVert++] = mGlyphs[0]->topLeft;
		offset += 6;

		for (int cg = 1; cg < mGlyphs.size(); cg++)
		{
			if (mGlyphs[cg]->texture != mGlyphs[cg - 1]->texture)
				mBatches.emplace_back(offset, 6, mGlyphs[cg]->texture);
			else
				mBatches.back().mNumVerts += 6;

			vertices[currVert++] = mGlyphs[cg]->topLeft;
			vertices[currVert++] = mGlyphs[cg]->bottomLeft;
			vertices[currVert++] = mGlyphs[cg]->bottomRight;
			vertices[currVert++] = mGlyphs[cg]->bottomRight;
			vertices[currVert++] = mGlyphs[cg]->topRight;
			vertices[currVert++] = mGlyphs[cg]->topLeft;

			offset += 6;
		}

		glBindBuffer(GL_ARRAY_BUFFER, mvbo);
		// orphan the buffer
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void SpriteBatch::createVertexArray()
	{
		if (mvao == 0)
			glGenVertexArrays(1, &mvao);
		glBindVertexArray(mvao);

		if (mvbo == 0)
			glGenBuffers(1, &mvbo);
		glBindBuffer(GL_ARRAY_BUFFER, mvbo);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		glBindVertexArray(0);
	}

	void SpriteBatch::sortGlyphs()
	{
		switch (mSortType)
		{
		case GlyphSortType::BACK_TO_FRONT:
			std::stable_sort(mGlyphs.begin(), mGlyphs.end(), compareBackToFront);
			break;
		case GlyphSortType::FRONT_TO_BACK:
			std::stable_sort(mGlyphs.begin(), mGlyphs.end(), compareFrontToBack);
			break;
		case GlyphSortType::TEXTURE:
			std::stable_sort(mGlyphs.begin(), mGlyphs.end(), compareTexture);
			break;
		default:
			break;
		}

		
	} 

	bool SpriteBatch::compareBackToFront(Glyph* a, Glyph* b)
	{
		return (a->depth < b->depth);
	}

	bool SpriteBatch::compareFrontToBack(Glyph* a, Glyph* b)
	{
		return (a->depth > b->depth);
	}

	bool SpriteBatch::compareTexture(Glyph* a, Glyph* b)
	{
		return (a->texture < b->texture);
	}
}
