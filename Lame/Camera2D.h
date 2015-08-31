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
		inline glm::vec2 getPosition() { return mPosition; }
		inline glm::mat4 getCamMatrix() { return mCamMatrix; }
		inline float getScale() { return mScale; }

		// setters
		inline void setPosition(const glm::vec2& position) { mPosition = position; mNeedsMatUpdate = true; };
		inline void setScale(float scale) { mScale = scale; mNeedsMatUpdate = true; }


	private:
		int       mViewportWidth;
		int		  mViewportHeight;
		bool      mNeedsMatUpdate;
		float     mScale;
		glm::vec2 mPosition;
		glm::mat4 mCamMatrix;
		glm::mat4 mOrthoMatrix;
	};

}

