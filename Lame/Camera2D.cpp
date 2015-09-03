#include "Camera2D.h"

namespace lame {

	Camera2D::Camera2D() : m_Position(0, 0), m_CamMatrix(1.0f), m_OrthoMatrix(1.0f), m_Scale(1.0f), m_NeedsMatUpdate(true), m_ViewportWidth(500), m_ViewportHeight(500)
	{
	}

	Camera2D::~Camera2D()
	{
	}

	void Camera2D::Init(int width, int height)
	{
		m_ViewportWidth = width;
		m_ViewportHeight = height;
		m_OrthoMatrix = glm::ortho(0.0f, (float)m_ViewportWidth, 0.0f, (float)m_ViewportHeight);
	}

	void Camera2D::Update()
	{
		if (m_NeedsMatUpdate)
		{
			glm::vec3 translate(-m_Position.x + m_ViewportWidth / 2, -m_Position.y + m_ViewportHeight / 2, 0.0f);
			m_CamMatrix = glm::translate(m_OrthoMatrix, translate);

			glm::vec3 scale(m_Scale, m_Scale, 0.0f);
			m_CamMatrix = glm::scale(glm::mat4(1.0f), scale) * m_CamMatrix;

			m_NeedsMatUpdate = false;
		}
	}

	glm::vec2 Camera2D::ScreenToWorld(glm::vec2 screenCoords)
	{
		// Invert Y
		screenCoords.y = m_ViewportHeight - screenCoords.y;

		screenCoords -= glm::vec2(m_ViewportWidth / 2, m_ViewportHeight / 2);
		screenCoords /= m_Scale;
		screenCoords += m_Position;
		return screenCoords;
	}
}
