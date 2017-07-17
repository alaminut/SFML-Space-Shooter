#include <iostream>
#include <glew.h>
#include "Display.h"
#include "Application.h"

#define endlch '\n'

int main()
{
	//Ensure that application resources will be freed when user quits.
	{
		Application app;

		glewInit();
		if (glewIsSupported("GL_VERSION_4_5"))
		{
			std::cout << "OpenGL 4.5 Active" << endlch;
		}

		app.runGameLoop();
	}

#ifdef DEBUG_ON
	std::cout << "Press any key to exit" << endlch;
	std::cin.get();
#endif

	return 0;
}