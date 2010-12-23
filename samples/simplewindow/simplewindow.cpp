////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include <oogl/Window.hpp>

int main()
{
	GL::Window window( 800, 600, 0, 0, "OpenGL Window", GL::WindowFlags::Caption | GL::WindowFlags::CenterScreen );

	while ( window.IsOpen() )
	{
		window.GetEvents();
	}

	return 0;
}