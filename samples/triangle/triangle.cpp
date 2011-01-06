////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include <oogl/Window.hpp>
#include <iostream>

int main()
{
	GL::Window window( 800, 600, 0, 0, "OpenGL Triangle", GL::WindowFlags::Caption | GL::WindowFlags::CenterScreen );
	GL::Context& gl = window.GetContext();

	GL::Shader shader( GL::ShaderType::Fragment );
	shader.Source( "void main() { " );
	try {
		shader.Compile();
	} catch ( GL::ShaderCompileException& e ) {
		std::cerr << "Shader compilation failed:" << std::endl << e.what() << std::endl;
	}

	gl.ClearColor( 0.0f, 0.0f, 0.0f );

	while ( window.IsOpen() )
	{
		window.GetEvents();

		gl.Clear( GL::Buffer::Color );

		window.Present();
	}

	return 0;
}
