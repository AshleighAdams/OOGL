////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include <oogl/Window.hpp>
#include <oogl/Context.hpp>
#include <cstdio>

int main()
{
	GL::Window window( 800, 600, 0, 0, "OpenGL Window", GL::WindowFlags::Caption | GL::WindowFlags::CenterScreen );
	GL::Context& gl = window.GetContext();

	gl.ClearColor( 0.0f, 0.0f, 0.0f );

	while ( window.IsOpen() )
	{
		window.GetEvents();

		gl.Clear( GL::Buffer::Color );

		window.Present();
	}

	return 0;
}
