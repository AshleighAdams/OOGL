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

#ifdef _WIN32

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include <oogl/Context.hpp>

#include <windows.h>
#include <gl/gl.h>

namespace GL
{
	Context::Context( HWND window )
	{
		HDC dc = GetDC( window );

		// Choose appropriate pixel format
		PIXELFORMATDESCRIPTOR pfd;
		ZeroMemory( &pfd, sizeof( pfd ) );
		pfd.nSize = sizeof( pfd );
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 32;
		pfd.cDepthBits = 32;
		pfd.iLayerType = PFD_MAIN_PLANE;
		int pixelFormat = ChoosePixelFormat( dc, &pfd );
		SetPixelFormat( dc, pixelFormat, &pfd );

		// Create the context
		HGLRC context = wglCreateContext( dc );
		wglMakeCurrent( dc, context );

		// Set the initial viewport
		RECT dimensions;
		GetWindowRect( window, &dimensions );
		glViewport( 0, 0, dimensions.right - dimensions.left, dimensions.bottom - dimensions.top );

		_context = context;
	}
}

#endif