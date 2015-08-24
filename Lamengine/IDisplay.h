#pragma once

namespace lamengine {

	class IDisplay
	{
	public:
		virtual ~IDisplay() {}
		virtual void update() = 0;
		virtual void swapBuffers() = 0;

		virtual bool isClosed() = 0;
		virtual void dispose() = 0;
		virtual void clear() = 0;
	};
}