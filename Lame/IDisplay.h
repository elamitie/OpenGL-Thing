#pragma once

namespace lame {

	class IDisplay
	{
	public:
		virtual ~IDisplay() {}
		virtual void update() = 0;
		virtual void swapBuffers() = 0;

		virtual bool isClosed() = 0;
		virtual void dispose() = 0;
		virtual void clear() = 0;

		virtual int  getWidth() = 0;
		virtual int  getHeight() = 0;
	};
}