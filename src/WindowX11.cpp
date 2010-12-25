
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
        swa.event_mask = ConfigureNotify | KeyPressMask | ExposureMask | ButtonPressMask | StructureNotifyMask;

        _window = XCreateWindow( _display, RootWindow( _display, vi->screen ), x, y, width, height, 0, vi->depth, InputOutput, vi->visual, CWBorderPixel | CWColormap | CWEventMask, &swa );
        XSetStandardProperties( _display, _window, title, "OpenGLWindow", None, 0, 0, NULL );
        XMapWindow( _display, _window );
        XFlush( _display );

        _open = true;
        _width = width;
        _height = height;
        _x = x;
        _y = y;

        // Create the OpenGL context
        _context = Context( _display, _window, vi );

        // Set additional window properties
        if ( flags & WindowFlags::CenterScreen )
			Center();
        if ( flags & WindowFlags::Hidden )
            SetVisible( false );

        // Way too long code to set window caption and resize settings
        if ( !( flags & WindowFlags::Sizable ) || !( flags & WindowFlags::Caption ) )
        {
            Atom hintsAtom = XInternAtom( _display, "_MOTIF_WM_HINTS", false );
            if ( hintsAtom )
            {
                static const unsigned long MWM_HINTS_FUNCTIONS = 1;
                static const unsigned long MWM_HINTS_DECORATIONS = 1 << 1;

                static const unsigned long MWM_DECOR_BORDER = 1 << 1;
                static const unsigned long MWM_DECOR_RESIZEH = 1 << 2;
                static const unsigned long MWM_DECOR_TITLE = 1 << 3;
                static const unsigned long MWM_DECOR_MENU = 1 << 4;
                static const unsigned long MWM_DECOR_MINIMIZE = 1 << 5;
                static const unsigned long MWM_DECOR_MAXIMIZE = 1 << 6;

                static const unsigned long MWM_FUNC_RESIZE = 1 << 1;
                static const unsigned long MWM_FUNC_MOVE = 1 << 2;
                static const unsigned long MWM_FUNC_MINIMIZE = 1 << 3;
                static const unsigned long MWM_FUNC_MAXIMIZE = 1 << 4;
                static const unsigned long MWM_FUNC_CLOSE  = 1 << 5;

                struct WindowHints
                {
                    unsigned long flags;
                    unsigned long functions;
                    unsigned long decorations;
                    long inputMode;
                    unsigned long state;
                };

                WindowHints hints;
                hints.flags = MWM_HINTS_FUNCTIONS | MWM_HINTS_DECORATIONS;
                hints.decorations = 0;
                hints.functions = MWM_FUNC_CLOSE;

                if ( flags & WindowFlags::Sizable )
                {
                    hints.decorations |= MWM_DECOR_MAXIMIZE | MWM_DECOR_RESIZEH;
                    hints.functions |= MWM_FUNC_MAXIMIZE | MWM_FUNC_RESIZE;
                }
                if ( flags & WindowFlags::Caption )
                {
                    hints.decorations |= MWM_DECOR_BORDER | MWM_DECOR_TITLE | MWM_DECOR_MINIMIZE | MWM_DECOR_MENU;
                    hints.functions |= MWM_FUNC_MOVE | MWM_FUNC_MINIMIZE;
                }

                const unsigned char* hintPtr = reinterpret_cast<const unsigned char*>( &hints );
                XChangeProperty( _display, _window, hintsAtom, hintsAtom, 32, PropModeReplace, hintPtr, 5 );
            }

            // Resize hack for some window systems
            XSizeHints sizeHints;
            sizeHints.flags = PMinSize | PMaxSize;
            sizeHints.min_width = sizeHints.max_width = width;
            sizeHints.min_height = sizeHints.max_height = height;
            XSetWMNormalHints( _display, _window, &sizeHints );

            XFlush( _display );
        }
    }

    void Window::GetEvents()
    {
        XEvent event;

        while ( XPending( _display ) )
        {
            XNextEvent( _display, &event );

            switch ( event.type )
            {
                case ConfigureNotify:
                    _width = event.xconfigure.width;
                    _height = event.xconfigure.height;
                    _x = event.xconfigure.x;
                    _y = event.xconfigure.y;
                    break;
            }
        }
    }

    void Window::SetTitle( const char* title )
    {
        XStoreName( _display, _window, title );
    }

    void Window::SetPosition( int x, int y )
    {
        XMoveWindow( _display, _window, x, y );
        XFlush( _display );
    }

    void Window::SetSize( unsigned int width, unsigned int height )
    {
        XResizeWindow( _display, _window, width, height );
        XFlush( _display );
    }

    void Window::SetVisible( bool visible )
    {
        if ( visible )
            XMapWindow( _display, _window );
        else
            XUnmapWindow( _display, _window );

        XFlush( _display );
    }

    void Window::Center()
    {
        SetPosition( XDisplayWidth( _display, 0 ) / 2 - _width / 2, XDisplayHeight( _display, 0 ) / 2 - _height / 2 );
    }

    void Window::Present()
    {
        glXSwapBuffers( _display, _window );
    }
}

#endif
