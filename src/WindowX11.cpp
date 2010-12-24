
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

#ifdef __linux__

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include <oogl/Window.hpp>
#include <stdlib.h>

namespace GL
{
    Window::Window( unsigned int width, unsigned int height, int x, int y, const char* title, unsigned int flags )
    {
        // Create the window
        _display = XOpenDisplay( NULL );

        int doubleBuffered[]  = { GLX_RGBA, GLX_DEPTH_SIZE, 16, GLX_DOUBLEBUFFER, None };
        XVisualInfo* vi = glXChooseVisual( _display, DefaultScreen( _display ), doubleBuffered );

        Colormap cmap = XCreateColormap( _display, RootWindow( _display, vi->screen ), vi->visual, AllocNone );
        XSetWindowAttributes swa;
        swa.colormap = cmap;
        swa.border_pixel = 0;
        swa.event_mask = KeyPressMask | ExposureMask | ButtonPressMask | StructureNotifyMask;

        _window = XCreateWindow( _display, RootWindow( _display, vi->screen ), x, y, width, height, 0, vi->depth, InputOutput, vi->visual, CWBorderPixel | CWColormap | CWEventMask, &swa );
        XSetStandardProperties( _display, _window, title, "OpenGLWindow", None, 0, 0, NULL );

        XMapWindow( _display, _window );

        // Create the OpenGL context
        _context = Context( _display, _window, vi );
    }

    void Window::GetEvents()
    {
        XEvent event;

        while ( XPending( _display ) )
        {
            XNextEvent( _display, &event );
        }
    }

    void Window::Present()
    {
        glXSwapBuffers( _display, _window );
    }
}

#endif
