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

#ifndef OOGL_VBO_HPP
#define OOGL_VBO_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include <oogl/OpenGL.hpp>

namespace GL
{
	////////////////////////////////////////////////////////////
	// Enumeration of buffer uses.
	////////////////////////////////////////////////////////////

	namespace BufferUsage
	{
		enum
		{
			StreamDraw = Extensions::GL_STREAM_DRAW,
			StreamRead = Extensions::GL_STREAM_READ,
			StreamCopy = Extensions::GL_STREAM_COPY,
			StaticDraw = Extensions::GL_STATIC_DRAW,
			StaticRead = Extensions::GL_STATIC_READ,
			StaticCopy = Extensions::GL_STATIC_COPY,
			DynamicDraw = Extensions::GL_DYNAMIC_DRAW,
			DynamicRead = Extensions::GL_DYNAMIC_READ,
			DynamicCopy = Extensions::GL_DYNAMIC_COPY
		};
	}

	////////////////////////////////////////////////////////////
	// OpenGL vertex buffer
	////////////////////////////////////////////////////////////

	class VertexBuffer
	{
	public:
		VertexBuffer( const void* data, unsigned long size, unsigned int usage );
		~VertexBuffer();

		unsigned int GetIdentifier();

	private:
		unsigned int _identifier;

		static Extensions::GLGENBUFFERSPROC glGenBuffers;
		static Extensions::GLDELETEBUFFERSPROC glDeleteBuffers;
		static Extensions::GLBINDBUFFERPROC glBindBuffer;
		static Extensions::GLBUFFERDATAPROC glBufferData;
	};
}

#endif
