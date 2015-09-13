#include "Camera2D.h"

namespace lame {

	Camera2D::Camera2D() : m_position(0, 0), m_camMatrix(1.0f), m_orthoMatrix(1.0f), m_scale(1.0f), m_needsMatUpdate(true), m_viewportWidth(500), m_viewportHeight(500)
	{
	}

	Camera2D::~Camera2D()
	{
	}

	void Camera2D::init(int width, int height)
	{
		m_viewportWidth = width;
		m_viewportHeight = height;
		m_orthoMatrix = glm::ortho(0.0f, (float)m_viewportWidth, 0.0f, (float)m_viewportHeight);
	}

	void Camera2D::update()
	{
		if (m_needsMatUpdate)
		{
			glm::vec3 translate(-m_position.x + m_viewportWidth / 2, -m_position.y + m_viewportHeight / 2, 0.0f);
			m_camMatrix = glm::translate(m_orthoMatrix, translate);

			glm::vec3 scale(m_scale, m_scale, 0.0f);
			m_camMatrix = glm::scale(glm::mat4(1.0f), scale) * m_camMatrix;

			m_needsMatUpdate = false;
		}
	}

	glm::vec2 Camera2D::screenToWorld(glm::vec2 screenCoords)
	{
		// Invert Y
		screenCoords.y = m_viewportHeight - screenCoords.y;

		screenCoords -= glm::vec2(m_viewportWidth / 2, m_viewportHeight / 2);
		screenCoords /= m_scale;
		screenCoords += m_position;
		return screenCoords;
	}
}
