#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace lame {

	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();

		void init(int width, int height);
		void update();

		glm::vec2 screenToWorld(glm::vec2 screenCoords);

		// getters
		inline glm::vec2 getPosition() { return m_position; }
		inline glm::mat4 getCamMatrix() { return m_camMatrix; }
		inline float getScale() { return m_scale; }

		// setters
		inline void setPosition(const glm::vec2& position) { m_position = position; m_needsMatUpdate = true; };
		inline void setScale(float scale) { m_scale = scale; m_needsMatUpdate = true; }


	private:
		int       m_viewportWidth;
		int		  m_viewportHeight;
		bool      m_needsMatUpdate;
		float     m_scale;
		glm::vec2 m_position;
		glm::mat4 m_camMatrix;
		glm::mat4 m_orthoMatrix;
	};

}

