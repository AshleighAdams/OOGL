////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include <oogl/Window.hpp>
#include <iostream>

const char* vertexShaderSource = "in vec2 in_Position;\
	in vec3 in_Color;\
	varying vec3 ex_Color;\
	void main()\
	{\
		gl_Position = vec4( ( in_Position.x - 400.0 ) / 400.0, ( 300.0 - in_Position.y ) / 300.0, 0.0, 1.0 );\
		ex_Color = in_Color;\
	}";
const char* fragmentShaderSource = "varying vec3 ex_Color;\
	void main()\
	{\
		gl_FragColor = vec4( ex_Color, 1.0 );\
	}";

int main()
{
	GL::Window window( 800, 600, 0, 0, "OpenGL Triangle", GL::WindowFlags::Caption | GL::WindowFlags::CenterScreen );
	GL::Context& gl = window.GetContext();

	GL::Shader vertexShader( GL::ShaderType::Vertex );
	GL::Shader fragmentShader( GL::ShaderType::Fragment );
	vertexShader.Source( vertexShaderSource );
	fragmentShader.Source( fragmentShaderSource );
	try {
		vertexShader.Compile();
		fragmentShader.Compile();
	} catch ( GL::ShaderCompileException& e ) {
		std::cerr << "Shader compilation failed:" << std::endl << e.what();
		return 1;
	}

	GL::Program program;
	program.Attach( vertexShader );
	program.Attach( fragmentShader );
	program.BindAttribLocation( 0, "in_Position" );
	program.BindAttribLocation( 1, "in_Color" );
	try {
		program.Link();
	} catch ( GL::ProgramLinkException& e ) {
		std::cerr << "Program linking failed" << std::endl << e.what();
		return 1;
	}
	program.Use();

	float vertices[] = {
		50.0f, 50.0f, 1.0f, 0.0f, 0.0f,
		750.0f, 50.0f, 0.0f, 1.0f, 0.0f,
		750.0f, 550.0f, 0.0f, 0.0f, 1.0f
	};
	GL::VertexBuffer vbo( vertices, sizeof( vertices ), GL::BufferUsage::StaticDraw );

	gl.VertexAttribLocation( 0, 2, GL::Type::Float, 5 * sizeof( float ) );
	gl.VertexAttribLocation( 1, 3, GL::Type::Float, 5 * sizeof( float ), 2 * sizeof( float ) );
	
	gl.ClearColor( 0.0f, 0.0f, 0.0f );

	while ( window.IsOpen() )
	{
		window.GetEvents();

		gl.Clear( GL::Buffer::Color );
		gl.DrawArrays( GL::Primitive::Triangles, 0, 3 );

		window.Present();
	}

	return 0;
}