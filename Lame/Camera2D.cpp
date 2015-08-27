#include "Camera2D.h"

namespace lame {

	Camera2D::Camera2D() : mPosition(0, 0), mCamMatrix(1.0f), mOrthoMatrix(1.0f), mScale(1.0f), mNeedsMatUpdate(true), mViewportWidth(500), mViewportHeight(500)
	{
	}

	Camera2D::~Camera2D()
	{
	}

	void Camera2D::init(int width, int height)
	{
		mViewportWidth = width;
		mViewportHeight = height;
		mOrthoMatrix = glm::ortho(0.0f, (float)mViewportWidth, 0.0f, (float)mViewportHeight);
	}

	void Camera2D::update()
	{
		if (mNeedsMatUpdate)
		{
			glm::vec3 translate(-mPosition.x, -mPosition.y, 0.0f);
			mCamMatrix = glm::translate(mOrthoMatrix, translate);

			glm::vec3 scale(mScale, mScale, 0.0f);
			mCamMatrix = glm::scale(mCamMatrix, scale);

			mNeedsMatUpdate = false;
		}
	}

}
