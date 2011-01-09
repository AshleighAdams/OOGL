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

#pragma once

#ifndef OOGL_PROGRAM_HPP
#define OOGL_PROGRAM_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include <oogl/OpenGL.hpp>
#include <oogl/Shader.hpp>
#include <exception>
#include <string>

namespace GL
{
	////////////////////////////////////////////////////////////
	// Program linking exception
	////////////////////////////////////////////////////////////

	class ProgramLinkException : public std::exception
	{
	public:
		ProgramLinkException( const char* error ) { _error = std::string( error ); }
		~ProgramLinkException() throw() {};

		const char* what() const throw() { return _error.c_str(); }

	private:
		std::string _error;
	};

	////////////////////////////////////////////////////////////
	// OpenGL shader program
	////////////////////////////////////////////////////////////

	class Program
	{
	public:
		Program();
		~Program();

		void Attach( Shader& shader );
		void BindAttribLocation( unsigned int index, const char* name );

		void Link();

		void Use();

		unsigned int GetIdentifier();

	private:
		unsigned int _identifier;

		static Extensions::GLCREATEPROGRAMPROC glCreateProgram;
		static Extensions::GLDELETEPROGRAMPROC glDeleteProgram;
		static Extensions::GLATTACHSHADERPROC glAttachShader;
		static Extensions::GLBINDATTRIBLOCATIONPROC glBindAttribLocation;
		static Extensions::GLLINKPROGRAMPROC glLinkProgram;
		static Extensions::GLGETPROGRAMPROC glGetProgramiv;
		static Extensions::GLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
		static Extensions::GLUSEPROGRAMPROC glUseProgram;
	};
}

#endif
