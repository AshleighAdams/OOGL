////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include <oogl/Window.hpp>
#include <iostream>

int main()
{
	GL::Window window( 800, 600, 0, 0, "OpenGL Triangle", GL::WindowFlags::Caption | GL::WindowFlags::CenterScreen );
	GL::Context& gl = window.GetContext();

	GL::Shader shader = GL::Shader( GL::ShaderType::Fragment );
	std::cout << "Shader #: " << shader.GetIdentifier() << std::endl;

	gl.ClearColor( 0.0f, 0.0f, 0.0f );

	while ( window.IsOpen() )
	{
		window.GetEvents();

		gl.Clear( GL::Buffer::Color );

		window.Present();
	}

	return 0;
}