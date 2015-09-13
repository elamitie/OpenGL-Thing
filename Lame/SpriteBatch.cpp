#include "SpriteBatch.h"
#include <algorithm>

namespace lame {

	SpriteBatch::SpriteBatch() : m_vbo(0), m_vao(0)
	{
	}

	SpriteBatch::~SpriteBatch()
	{
	}

	void SpriteBatch::init()
	{
		m_defaultUV = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
		createVertexArray();
	}

	void SpriteBatch::begin(GlyphSortType sortType /* GlyphSortType::TEXTURE */)
	{
		m_sortType = sortType;
		m_batches.clear();

		for (auto& g : m_glyphs)
			delete g;

		m_glyphs.clear();
	}

	void SpriteBatch::end()
	{
		sortGlyphs();
		createRenderBatches();
	}

	void SpriteBatch::draw(const glm::vec4& destRect, Texture texture, float depth, const Color& color)
	{
		Glyph* glyph = new Glyph;
		glyph->texture = texture;
		glyph->depth = depth;

		glyph->topLeft.color = color;
		glyph->topLeft.setPosition(destRect.x, destRect.y + destRect.w);
		glyph->topLeft.setUV(m_defaultUV.x, m_defaultUV.y + m_defaultUV.w);

		glyph->bottomLeft.color = color;
		glyph->bottomLeft.setPosition(destRect.x, destRect.y);
		glyph->bottomLeft.setUV(m_defaultUV.x, m_defaultUV.y);

		glyph->bottomRight.color = color;
		glyph->bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
		glyph->bottomRight.setUV(m_defaultUV.x + m_defaultUV.z, m_defaultUV.y);

		glyph->topRight.color = color;
		glyph->topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
		glyph->topRight.setUV(m_defaultUV.x + m_defaultUV.z, m_defaultUV.y + m_defaultUV.w);

		m_glyphs.push_back(glyph);
	}

	void SpriteBatch::renderBatches()
	{
		glBindVertexArray(m_vao);

		for (unsigned int i = 0; i < m_batches.size(); i++)
		{
			glBindTexture(GL_TEXTURE_2D, m_batches[i].mTexture.getID());
			glDrawArrays(GL_TRIANGLES, m_batches[i].mOffset, m_batches[i].mNumVerts);
		}

		glBindVertexArray(0);
	}

	void SpriteBatch::createRenderBatches()
	{
		std::vector<Vertex> vertices;
		vertices.resize(m_glyphs.size() * 6);

		if (m_glyphs.empty())
			return;

		int offset = 0;
		int currVert = 0;
		m_batches.emplace_back(offset, 6, m_glyphs[0]->texture);
		vertices[currVert++] = m_glyphs[0]->topLeft;
		vertices[currVert++] = m_glyphs[0]->bottomLeft;
		vertices[currVert++] = m_glyphs[0]->bottomRight;
		vertices[currVert++] = m_glyphs[0]->bottomRight;
		vertices[currVert++] = m_glyphs[0]->topRight;
		vertices[currVert++] = m_glyphs[0]->topLeft;
		offset += 6;

		for (unsigned int cg = 1; cg < m_glyphs.size(); cg++)
		{
			if (m_glyphs[cg]->texture.getID() != m_glyphs[cg - 1]->texture.getID())
				m_batches.emplace_back(offset, 6, m_glyphs[cg]->texture);
			else
				m_batches.back().mNumVerts += 6;

			vertices[currVert++] = m_glyphs[cg]->topLeft;
			vertices[currVert++] = m_glyphs[cg]->bottomLeft;
			vertices[currVert++] = m_glyphs[cg]->bottomRight;
			vertices[currVert++] = m_glyphs[cg]->bottomRight;
			vertices[currVert++] = m_glyphs[cg]->topRight;
			vertices[currVert++] = m_glyphs[cg]->topLeft;

			offset += 6;
		}

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		// orphan the buffer
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void SpriteBatch::createVertexArray()
	{
		if (m_vao == 0)
			glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);

		if (m_vbo == 0)
			glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

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
		switch (m_sortType)
		{
		case GlyphSortType::BACK_TO_FRONT:
			std::stable_sort(m_glyphs.begin(), m_glyphs.end(), compareBackToFront);
			break;
		case GlyphSortType::FRONT_TO_BACK:
			std::stable_sort(m_glyphs.begin(), m_glyphs.end(), compareFrontToBack);
			break;
		case GlyphSortType::TEXTURE:
			std::stable_sort(m_glyphs.begin(), m_glyphs.end(), compareTexture);
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
		return (a->texture.getID() < b->texture.getID());
	}
}
