#include "Application.h"

int main(int argc, char** argv)
{
	Application app(new Display(800, 600, "Lame Engine"), 60.0);
	app.run();

	return 0;
}