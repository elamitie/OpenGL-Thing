#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace lame {

	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();

		void Init(int width, int height);
		void Update();

		glm::vec2 ScreenToWorld(glm::vec2 screenCoords);

		// getters
		inline glm::vec2 GetPosition() { return m_Position; }
		inline glm::mat4 GetCamMatrix() { return m_CamMatrix; }
		inline float GetScale() { return m_Scale; }

		// setters
		inline void SetPosition(const glm::vec2& position) { m_Position = position; m_NeedsMatUpdate = true; };
		inline void SetScale(float scale) { m_Scale = scale; m_NeedsMatUpdate = true; }


	private:
		int       m_ViewportWidth;
		int		  m_ViewportHeight;
		bool      m_NeedsMatUpdate;
		float     m_Scale;
		glm::vec2 m_Position;
		glm::mat4 m_CamMatrix;
		glm::mat4 m_OrthoMatrix;
	};

}

