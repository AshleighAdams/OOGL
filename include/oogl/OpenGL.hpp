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

#ifndef OOGL_OPENGL_HPP
#define OOGL_OPENGL_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#if defined( _WIN32 )
	#include <windows.h>
	#include <gl/gl.h>
#elif defined( __linux__ )
    #include <GL/glx.h>
    #include <X11/X.h>
#endif

namespace GL
{
	namespace Extensions
	{
		////////////////////////////////////////////////////////////
		// Extension loading
		////////////////////////////////////////////////////////////

		inline void* GetProcedure( const char* name )
		{
			#if defined( _WIN32 )
				return wglGetProcAddress( name );
			#elif defined( __linux__ )
				return (void*)glXGetProcAddressARB( (const GLubyte*)name );
			#endif
		}

		////////////////////////////////////////////////////////////
		// Extension prototypes
		////////////////////////////////////////////////////////////

		#ifndef _WIN32
			#define __stdcall
		#endif

		typedef char GLchar;

		typedef GLuint ( __stdcall * GLCREATESHADERPROC ) ( GLenum type );
		typedef void ( __stdcall * GLDELETESHADERPROC ) ( GLuint shader );
		typedef void ( __stdcall * GLSHADERSOURCEPROC ) ( GLuint shader, GLsizei count, const GLchar** string, const GLint* length );
		typedef void ( __stdcall * GLCOMPILESHADERPROC ) ( GLuint shader );
		typedef void ( __stdcall * GLGETSHADERPROC ) ( GLuint shader, GLenum pname, GLint* params );
		typedef void ( __stdcall * GLGETSHADERINFOLOGPROC ) ( GLuint shader, GLsizei maxLength, GLsizei* length, GLchar* infoLog );

		typedef GLuint ( __stdcall * GLCREATEPROGRAMPROC ) ();
		typedef void ( __stdcall * GLDELETEPROGRAMPROC ) ( GLuint program );
		typedef void ( __stdcall * GLATTACHSHADERPROC ) ( GLuint program, GLuint shader );
		typedef void ( __stdcall * GLBINDATTRIBLOCATIONPROC ) ( GLuint program, GLuint index, const GLchar* name );
		typedef void ( __stdcall * GLLINKPROGRAMPROC ) ( GLuint program );
		typedef void ( __stdcall * GLGETPROGRAMPROC ) ( GLuint program, GLenum pname, GLint* params );
		typedef void ( __stdcall * GLGETPROGRAMINFOLOGPROC ) ( GLuint program, GLsizei maxLength, GLsizei* length, GLchar* infoLog );
		typedef void ( __stdcall * GLUSEPROGRAMPROC ) ( GLuint program );

		typedef void ( __stdcall * GLGENBUFFERSPROC ) ( GLsizei n, GLuint* buffers );
		typedef void ( __stdcall * GLDELETEBUFFERSPROC ) ( GLsizei n, GLuint* buffers );
		typedef void ( __stdcall * GLBINDBUFFERPROC ) ( GLenum target, GLuint buffer );
		typedef void ( __stdcall * GLBUFFERDATAPROC ) ( GLenum target, GLsizei* size, const GLvoid* data, GLenum usage );

		typedef void ( __stdcall * GLVERTEXATTRIBPOINTERPROC ) ( GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer );
		typedef void ( __stdcall * GLENABLEVERTEXATTRIBARRAYPROC ) ( GLuint index );

		////////////////////////////////////////////////////////////
		// Extension values
		////////////////////////////////////////////////////////////

		#undef GL_FRAGMENT_SHADER
		#undef GL_VERTEX_SHADER
		#undef GL_COMPILE_STATUS

		#undef GL_LINK_STATUS

		#undef GL_STREAM_DRAW
		#undef GL_STREAM_READ
		#undef GL_STREAM_COPY
		#undef GL_STATIC_DRAW
		#undef GL_STATIC_READ
		#undef GL_STATIC_COPY
		#undef GL_DYNAMIC_DRAW
		#undef GL_DYNAMIC_READ
		#undef GL_DYNAMIC_COPY

		#undef GL_ARRAY_BUFFER

		const unsigned int GL_FRAGMENT_SHADER = 0x8B30;
		const unsigned int GL_VERTEX_SHADER = 0x8B31;
		const unsigned int GL_COMPILE_STATUS = 0x8B81;

		const unsigned int GL_LINK_STATUS = 0x8B82;

		const unsigned int GL_STREAM_DRAW = 0x88E0;
		const unsigned int GL_STREAM_READ = 0x88E1;
		const unsigned int GL_STREAM_COPY = 0x88E2;
		const unsigned int GL_STATIC_DRAW = 0x88E4;
		const unsigned int GL_STATIC_READ = 0x88E5;
		const unsigned int GL_STATIC_COPY = 0x88E6;
		const unsigned int GL_DYNAMIC_DRAW = 0x88E8;
		const unsigned int GL_DYNAMIC_READ = 0x88E9;
		const unsigned int GL_DYNAMIC_COPY = 0x88EA;

		const unsigned int GL_ARRAY_BUFFER = 0x8892;
	}
}

#endif
