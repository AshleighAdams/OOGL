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

#ifndef OOGL_WINDOW_HPP
#define OOGL_WINDOW_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include <oogl/WindowFlags.hpp>

#ifdef _WIN32
	#include <windows.h>
#endif

namespace GL
{
	////////////////////////////////////////////////////////////
	// Basic render window.
	////////////////////////////////////////////////////////////

	class Window
	{
	public:
		Window( unsigned int width, unsigned int height, int x, int y, const char* title, unsigned int flags = WindowFlags::Caption );

		bool IsOpen();

		void GetEvents();

		void SetTitle( const char* title );
		void SetPosition( int x, int y );
		void SetSize( unsigned int width, unsigned int height );

		void Center();

	private:
		void* _handle;
		
		bool _open;

		#ifdef _WIN32
			static LRESULT CALLBACK WindowEvent( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
			LRESULT Event( UINT msg, WPARAM wParam, LPARAM lParam );
		#endif
	};
}

#endif