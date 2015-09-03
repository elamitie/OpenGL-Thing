#include "Application.h"

int main(int argc, char** argv)
{
	Application app(new Display(800, 600, "Lame"), 60.0);
	app.Run();

	return 0;
}