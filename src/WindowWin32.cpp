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

#include <oogl/Window.hpp>

namespace GL
{
	Window::Window( unsigned int width, unsigned int height, int x, int y, const char* title, unsigned int flags )
	{
		// Create the window
		WNDCLASSEX windowClass;
		ZeroMemory( &windowClass, sizeof( windowClass ) );
		windowClass.cbSize = sizeof( WNDCLASSEX );
		windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		windowClass.lpfnWndProc = WindowEvent;
		windowClass.hIcon =  LoadIcon( NULL, IDI_APPLICATION );
		windowClass.hIconSm = LoadIcon( NULL, IDI_APPLICATION );
		windowClass.hCursor = LoadCursor( NULL, IDC_ARROW );
		windowClass.hbrBackground = (HBRUSH)GetStockObject( WHITE_BRUSH );
		windowClass.lpszClassName = "OpenGLWindow";
		RegisterClassEx( &windowClass );

		RECT windowSize;
		windowSize.left = 0;
		windowSize.top = 0;
		windowSize.right = width;
		windowSize.bottom = height;
		AdjustWindowRect( &windowSize, WS_POPUPWINDOW | WS_CAPTION, false );

		DWORD style = WS_POPUPWINDOW | WS_MINIMIZEBOX;
		if ( flags & WindowFlags::Caption ) style |= WS_CAPTION;
		if ( flags & WindowFlags::Sizable ) style |= WS_MAXIMIZEBOX | WS_SIZEBOX;

		HWND window = CreateWindowEx( WS_EX_OVERLAPPEDWINDOW, "OpenGLWindow", title, style, x, y, windowSize.right - windowSize.left, windowSize.bottom - windowSize.top, NULL, NULL, NULL, this );
		HDC dc = GetDC( window );
		ShowWindow( window, flags & WindowFlags::Hidden ? SW_HIDE : ( flags & WindowFlags::Minimized ? SW_MINIMIZE : ( flags & WindowFlags::Maximized ? SW_MAXIMIZE : SW_SHOWNORMAL ) ) );
		UpdateWindow( window );
		
		if ( flags & WindowFlags::CenterScreen )
			Center();

		_open = true;

		// Create the OpenGL context
		_context = Context( _handle );
	}

	void Window::GetEvents()
	{
		MSG msg;
			
		while ( PeekMessage( &msg, (HWND)_handle, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
	}

	void Window::SetTitle( const char* title )
	{
		SetWindowText( (HWND)_handle, title );
	}

	void Window::SetPosition( int x, int y )
	{
		SetWindowPos( (HWND)_handle, 0, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE );
	}

	void Window::SetSize( unsigned int width, unsigned int height )
	{
		SetWindowPos( (HWND)_handle, 0, 0, 0, width, height, SWP_NOZORDER | SWP_NOMOVE );
	}

	void Window::SetVisible( bool visible )
	{
		ShowWindow( (HWND)_handle, visible ? SW_NORMAL : SW_HIDE );
	}

	unsigned int Window::GetWidth()
	{
		RECT dimensions;
		GetWindowRect( (HWND)_handle, &dimensions );
		return dimensions.right - dimensions.left;
	}

	unsigned int Window::GetHeight()
	{
		RECT dimensions;
		GetWindowRect( (HWND)_handle, &dimensions );
		return dimensions.bottom - dimensions.top;
	}

	int Window::GetX()
	{
		RECT dimensions;
		GetWindowRect( (HWND)_handle, &dimensions );
		return dimensions.left;
	}

	int Window::GetY()
	{
		RECT dimensions;
		GetWindowRect( (HWND)_handle, &dimensions );
		return dimensions.top;
	}

	void Window::Center()
	{
		RECT desktop, window;
		GetWindowRect( GetDesktopWindow(), &desktop );
		GetWindowRect( (HWND)_handle, &window );
		SetWindowPos( (HWND)_handle, 0, desktop.right / 2 - window.right / 2, desktop.bottom / 2 - window.bottom / 2, 0, 0, SWP_NOZORDER | SWP_NOSIZE );
	}

	void Window::Present()
	{
		SwapBuffers( (HDC)_handle2 );
	}

	LRESULT Window::Event( UINT msg, WPARAM wParam, LPARAM lParam )
	{
		switch ( msg )
		{
		case WM_DESTROY:
			_open = false;
			break;

		default:
			return DefWindowProc( (HWND)_handle, msg, wParam, lParam );
		}

		return 0;
	}

	LRESULT CALLBACK Window::WindowEvent( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
	{
		Window* window;

		if ( msg == WM_NCCREATE )
		{
			window = reinterpret_cast<Window*>( ((LPCREATESTRUCT)lParam)->lpCreateParams );
			window->_handle = hWnd;
			window->_handle2 = GetDC( hWnd );

			SetWindowLong( hWnd, GWL_USERDATA, reinterpret_cast<long>( window ) );

			return DefWindowProc( hWnd, msg, wParam, lParam );
		} else {
			window = reinterpret_cast<Window*>( GetWindowLong( hWnd, GWL_USERDATA ) );

			return window->Event( msg, wParam, lParam );
		}
	}
}

#endif
