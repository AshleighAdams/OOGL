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

#include <oogl/Program.hpp>

namespace GL
{
	Extensions::GLCREATEPROGRAMPROC Program::glCreateProgram = 0;
	Extensions::GLDELETESHADERPROC Program::glDeleteProgram = 0;
	Extensions::GLATTACHSHADERPROC Program::glAttachShader = 0;
	Extensions::GLLINKPROGRAMPROC Program::glLinkProgram = 0;
	Extensions::GLGETPROGRAMPROC Program::glGetProgramiv = 0;
	Extensions::GLGETPROGRAMINFOLOGPROC Program::glGetProgramInfoLog = 0;

	Program::Program()
	{
		if ( !glCreateProgram )
		{
			glCreateProgram = (Extensions::GLCREATEPROGRAMPROC)Extensions::GetProcedure( "glCreateProgram" );
			glDeleteProgram = (Extensions::GLDELETESHADERPROC)Extensions::GetProcedure( "glDeleteProgram" );
			glAttachShader = (Extensions::GLATTACHSHADERPROC)Extensions::GetProcedure( "glAttachShader" );
			glLinkProgram = (Extensions::GLLINKPROGRAMPROC)Extensions::GetProcedure( "glLinkProgram" );
			glGetProgramiv = (Extensions::GLGETPROGRAMPROC)Extensions::GetProcedure( "glGetProgramiv" );
			glGetProgramInfoLog = (Extensions::GLGETPROGRAMINFOLOGPROC)Extensions::GetProcedure( "glGetProgramInfoLog" );
		}

		_identifier = glCreateProgram();
	}

	Program::~Program()
	{
		glDeleteProgram( _identifier );
	}

	void Program::Attach( Shader& shader )
	{
		glAttachShader( _identifier, shader.GetIdentifier() );
	}

	void Program::Link()
	{
		glLinkProgram( _identifier );

		int status;
		glGetProgramiv( _identifier, Extensions::GL_LINK_STATUS, &status );
		if ( status == 0 )
		{
			char buffer[2048];
			glGetProgramInfoLog( _identifier, 2048, 0, buffer );
			throw ProgramLinkException( buffer );
		}
	}

	unsigned int Program::GetIdentifier()
	{
		return _identifier;
	}
}