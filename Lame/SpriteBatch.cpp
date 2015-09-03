#include "SpriteBatch.h"
#include <algorithm>

namespace lame {

	SpriteBatch::SpriteBatch() : m_Vbo(0), m_Vao(0)
	{
	}

	SpriteBatch::~SpriteBatch()
	{
	}

	void SpriteBatch::Init()
	{
		createVertexArray();
	}

	void SpriteBatch::Begin(GlyphSortType sortType /* GlyphSortType::TEXTURE */)
	{
		m_SortType = sortType;
		m_Batches.clear();

		for (auto& g : m_Glyphs)
			delete g;

		m_Glyphs.clear();
	}

	void SpriteBatch::End()
	{
		sortGlyphs();
		createRenderBatches();
	}

	void SpriteBatch::Draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color)
	{
		Glyph* glyph = new Glyph;
		glyph->texture = texture;
		glyph->depth = depth;

		glyph->topLeft.color = color;
		glyph->topLeft.SetPosition(destRect.x, destRect.y + destRect.w);
		glyph->topLeft.SetUV(uvRect.x, uvRect.y + uvRect.w);

		glyph->bottomLeft.color = color;
		glyph->bottomLeft.SetPosition(destRect.x, destRect.y);
		glyph->bottomLeft.SetUV(uvRect.x, uvRect.y);

		glyph->bottomRight.color = color;
		glyph->bottomRight.SetPosition(destRect.x + destRect.z, destRect.y);
		glyph->bottomRight.SetUV(uvRect.x + uvRect.z, uvRect.y);

		glyph->topRight.color = color;
		glyph->topRight.SetPosition(destRect.x + destRect.z, destRect.y + destRect.w);
		glyph->topRight.SetUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

		m_Glyphs.push_back(glyph);
	}

	void SpriteBatch::RenderBatches()
	{
		glBindVertexArray(m_Vao);

		for (unsigned int i = 0; i < m_Batches.size(); i++)
		{
			glBindTexture(GL_TEXTURE_2D, m_Batches[i].mTexture);
			glDrawArrays(GL_TRIANGLES, m_Batches[i].mOffset, m_Batches[i].mNumVerts);
		}

		glBindVertexArray(0);
	}

	void SpriteBatch::createRenderBatches()
	{
		std::vector<Vertex> vertices;
		vertices.resize(m_Glyphs.size() * 6);

		if (m_Glyphs.empty())
			return;

		int offset = 0;
		int currVert = 0;
		m_Batches.emplace_back(offset, 6, m_Glyphs[0]->texture);
		vertices[currVert++] = m_Glyphs[0]->topLeft;
		vertices[currVert++] = m_Glyphs[0]->bottomLeft;
		vertices[currVert++] = m_Glyphs[0]->bottomRight;
		vertices[currVert++] = m_Glyphs[0]->bottomRight;
		vertices[currVert++] = m_Glyphs[0]->topRight;
		vertices[currVert++] = m_Glyphs[0]->topLeft;
		offset += 6;

		for (unsigned int cg = 1; cg < m_Glyphs.size(); cg++)
		{
			if (m_Glyphs[cg]->texture != m_Glyphs[cg - 1]->texture)
				m_Batches.emplace_back(offset, 6, m_Glyphs[cg]->texture);
			else
				m_Batches.back().mNumVerts += 6;

			vertices[currVert++] = m_Glyphs[cg]->topLeft;
			vertices[currVert++] = m_Glyphs[cg]->bottomLeft;
			vertices[currVert++] = m_Glyphs[cg]->bottomRight;
			vertices[currVert++] = m_Glyphs[cg]->bottomRight;
			vertices[currVert++] = m_Glyphs[cg]->topRight;
			vertices[currVert++] = m_Glyphs[cg]->topLeft;

			offset += 6;
		}

		glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
		// orphan the buffer
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void SpriteBatch::createVertexArray()
	{
		if (m_Vao == 0)
			glGenVertexArrays(1, &m_Vao);
		glBindVertexArray(m_Vao);

		if (m_Vbo == 0)
			glGenBuffers(1, &m_Vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);

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
		switch (m_SortType)
		{
		case GlyphSortType::BACK_TO_FRONT:
			std::stable_sort(m_Glyphs.begin(), m_Glyphs.end(), compareBackToFront);
			break;
		case GlyphSortType::FRONT_TO_BACK:
			std::stable_sort(m_Glyphs.begin(), m_Glyphs.end(), compareFrontToBack);
			break;
		case GlyphSortType::TEXTURE:
			std::stable_sort(m_Glyphs.begin(), m_Glyphs.end(), compareTexture);
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
