////////////////////////////////////////////////////////////
//
// Copyright (c) 2010, Alexander Overvoorde. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 1. Redistributions of source code must retain the above copyright
// 	notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
// 	notice, this list of conditions and the following disclaimer in the
// 	documentation and/or other materials provided with the distribution.
// 3. All advertising materials mentioning features or use of this software
// 	must display the following acknowledgement:
// 	This product includes software developed by Overv Projects.
// 4. Neither the name of Overv Projects nor the
// 	names of its contributors may be used to endorse or promote products
// 	derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY ALEXANDER OVERVOORDE ''AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL ALEXANDER OVERVOORDE BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include <oogl/Shader.hpp>

namespace GL
{
	Extensions::GLCREATESHADERPROC Shader::glCreateShader = 0;
	Extensions::GLDELETESHADERPROC Shader::glDeleteShader = 0;
	Extensions::GLSHADERSOURCEPROC Shader::glShaderSource = 0;
	Extensions::GLCOMPILESHADERPROC Shader::glCompileShader = 0;
	Extensions::GLGETSHADERPROC Shader::glGetShaderiv = 0;
	Extensions::GLGETSHADERINFOLOGPROC Shader::glGetShaderInfoLog = 0;

	Shader::Shader( unsigned int type )
	{
		if ( !glCreateShader )
		{
			glCreateShader = (Extensions::GLCREATESHADERPROC)Extensions::GetProcedure( "glCreateShader" );
			glDeleteShader = (Extensions::GLDELETESHADERPROC)Extensions::GetProcedure( "glDeleteShader" );
			glShaderSource = (Extensions::GLSHADERSOURCEPROC)Extensions::GetProcedure( "glShaderSource" );
			glCompileShader = (Extensions::GLCOMPILESHADERPROC)Extensions::GetProcedure( "glCompileShader" );
			glGetShaderiv = (Extensions::GLGETSHADERPROC)Extensions::GetProcedure( "glGetShaderiv" );
			glGetShaderInfoLog = (Extensions::GLGETSHADERINFOLOGPROC)Extensions::GetProcedure( "glGetShaderInfoLog" );
		}

		_identifier = glCreateShader( type );
	}

	Shader::~Shader()
	{
		glDeleteShader( _identifier );
	}

	void Shader::Source( const char* code )
	{
		glShaderSource( _identifier, 1, &code, 0 );
	}

	void Shader::Compile()
	{
		glCompileShader( _identifier );

		int status;
		glGetShaderiv( _identifier, Extensions::GL_COMPILE_STATUS, &status );
		if ( status == 0 )
		{
			char buffer[2048];
			glGetShaderInfoLog( _identifier, 2048, 0, buffer );
			throw ShaderCompileException( buffer );
		}
	}

	unsigned int Shader::GetIdentifier()
	{
		return _identifier;
	}
}
