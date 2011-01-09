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

#ifndef OOGL_CONTEXT_HPP
#define OOGL_CONTEXT_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include <oogl/OpenGL.hpp>
#include <oogl/Shader.hpp>
#include <oogl/Program.hpp>
#include <oogl/VertexBuffer.hpp>

namespace GL
{
	////////////////////////////////////////////////////////////
	// Enumeration of OpenGL buffers.
	////////////////////////////////////////////////////////////

	namespace Buffer
	{
		enum
		{
			Color = GL_COLOR_BUFFER_BIT,
			Depth = GL_DEPTH_BUFFER_BIT,
			Stencil = GL_STENCIL_BUFFER_BIT
		};
	}

	////////////////////////////////////////////////////////////
	// Enumeration of OpenGL types.
	////////////////////////////////////////////////////////////

	namespace Type
	{
		enum
		{
			Float = GL_FLOAT
		};
	}

	////////////////////////////////////////////////////////////
	// Enumeration of OpenGL primitives.
	////////////////////////////////////////////////////////////

	namespace Primitive
	{
		enum
		{
			Triangles = GL_TRIANGLES,
		};
	}

	////////////////////////////////////////////////////////////
	// OpenGL context
	////////////////////////////////////////////////////////////

	class Context
	{
	friend class Window;

	public:
		void ClearColor( float r, float g, float b, float a = 1.0f );
		void Clear( unsigned int buffers );

		void VertexAttribLocation( unsigned int index, unsigned int size, unsigned int type, unsigned int stride, const void* pointer );
		void VertexAttribLocation( unsigned int index, unsigned int size, unsigned int type, unsigned int stride, unsigned int offset = 0 );
		
		void DrawArrays( unsigned int shape, unsigned int first, unsigned int count );

	private:
		Context() {}

		#if defined( _WIN32 )
            Context( HWND window, unsigned int width, unsigned int height );
            HGLRC _context;
        #elif defined( __linux__ )
            Context( Display* display, Window window, XVisualInfo* vi, unsigned int width, unsigned int height );
            GLXContext _context;
        #endif

		static Extensions::GLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
		static Extensions::GLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
	};
}

#endif
