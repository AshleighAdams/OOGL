////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include <oogl/Window.hpp>
#include <iostream>

int main()
{
	GL::Window window( 800, 600, 0, 0, "OpenGL Triangle", GL::WindowFlags::Caption | GL::WindowFlags::CenterScreen );
	GL::Context& gl = window.GetContext();

	GL::Shader fragmentShader( GL::ShaderType::Fragment );
	GL::Shader vertexShader( GL::ShaderType::Vertex );
	fragmentShader.Source( "void main() {}" );
	vertexShader.Source( "" );
	try {
		fragmentShader.Compile();
		vertexShader.Compile();
	} catch ( GL::ShaderCompileException& e ) {
		std::cerr << "Shader compilation failed:" << std::endl << e.what();
		return 1;
	}

	GL::Program program;
	program.Attach( fragmentShader );
	program.Attach( vertexShader );
	try {
		program.Link();
	} catch ( GL::ProgramLinkException& e ) {
		std::cerr << "Program linking failed" << std::endl << e.what();
		return 1;
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
