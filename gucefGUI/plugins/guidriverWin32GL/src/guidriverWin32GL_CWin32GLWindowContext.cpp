/*
 *  guidriverWin32GL: module implementing GL based window management for Win32
 *  Copyright (C) 2002 - 2011.  Dinand Vanvelzen
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

/*-------------------------------------------------------------------------//
//                                                                         //
//      INCLUDES                                                           //
//                                                                         //
//-------------------------------------------------------------------------*/

#ifndef GUCEF_CORE_LOGGING_H
#include "gucefCORE_Logging.h"
#define GUCEF_CORE_LOGGING_H
#endif /* GUCEF_CORE_LOGGING_H ? */

#ifndef GUCEF_GUI_CWINDOWCONTEXT_H
#include "gucefGUI_CWindowContext.h"
#define GUCEF_GUI_CWINDOWCONTEXT_H
#endif /* GUCEF_GUI_CWINDOWCONTEXT_H ? */

#include "guidriverWin32GL_CWin32GLWindowContext.h"

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

namespace GUCEF {
namespace GUIDRIVERWIN32GL {

/*-------------------------------------------------------------------------//
//                                                                         //
//      UTILITIES                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

CWin32GLWindowContext::CWin32GLWindowContext( void )
    : CWindowContext()         ,
      m_guiContext()           ,
      m_id()                   ,
      m_name()                 ,
      m_window()               ,
      m_renderContext( NULL )  ,
      m_deviceContext( NULL )
{GUCEF_TRACE;

}

/*-------------------------------------------------------------------------*/

CWin32GLWindowContext::~CWin32GLWindowContext()
{GUCEF_TRACE;

    Shutdown();
}

/*-------------------------------------------------------------------------*/

void
CWin32GLWindowContext::SetGuiContext( GUI::TGuiContextPtr& context )
{GUCEF_TRACE;

    m_guiContext = context;
}

/*-------------------------------------------------------------------------*/

GUI::TGuiContextPtr
CWin32GLWindowContext::GetGuiContext( void )
{GUCEF_TRACE;

    return m_guiContext;
}

/*-------------------------------------------------------------------------*/

GUI::UInt32
CWin32GLWindowContext::GetID( void ) const
{GUCEF_TRACE;

    return m_id;
}

/*-------------------------------------------------------------------------*/

bool
CWin32GLWindowContext::IsActive( void ) const
{GUCEF_TRACE;

    return false;
}

/*-------------------------------------------------------------------------*/

GUI::CString
CWin32GLWindowContext::GetName( void ) const
{GUCEF_TRACE;

    return m_name;
}

/*-------------------------------------------------------------------------*/

void
CWin32GLWindowContext::Shutdown( void )
{GUCEF_TRACE;

	if ( NULL != m_renderContext )
	{
		wglMakeCurrent( NULL, NULL ); 
		wglDeleteContext( m_renderContext );
		m_renderContext = NULL;
	}

	if ( NULL != m_deviceContext )
	{
		ReleaseDC( m_window.GetHwnd(), m_deviceContext );
		m_deviceContext = NULL;
	}

    if ( NULL != m_window.GetHwnd() )
    {
        CORE::CMsWin32Window::UnregisterWindowClass( m_window.GetText() );
        m_window.WindowDestroy();
    }
}

/*-------------------------------------------------------------------------*/

bool
CWin32GLWindowContext::Initialize( const GUI::CString& title                ,
                                   const GUI::CVideoSettings& videoSettings )
{GUCEF_TRACE;

    // Do not initialize twice
    Shutdown();

    if ( !CORE::CMsWin32Window::RegisterWindowClass( title ) )
    {
        GUCEF_ERROR_LOG( CORE::LOGLEVEL_NORMAL, "Win32GLWindowContext: Could not register window class" );
        return false;
    }

    // First create a regular Win32 window
    if ( m_window.WindowCreate( title                                       ,
                                title                                       ,
                                0                                           ,
                                0                                           ,
                                videoSettings.GetResolutionWidthInPixels()  ,
                                videoSettings.GetResolutionHeightInPixels() ) )
    {
	    // Now proceed with setting up the OpenGL specifics
        m_deviceContext = GetDC( m_window.GetHwnd() );
	    if ( NULL == m_deviceContext )
	    {
		    GUCEF_ERROR_LOG( CORE::LOGLEVEL_NORMAL, "Win32GLWindowContext: Could not obtain window device context" );
            Shutdown();
		    return false;
	    }

	    PIXELFORMATDESCRIPTOR pixelFormatDescriptor;
	    memset( &pixelFormatDescriptor, 0, sizeof(pixelFormatDescriptor) );
	    pixelFormatDescriptor.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	    pixelFormatDescriptor.nVersion = 1;
	    pixelFormatDescriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	    pixelFormatDescriptor.iPixelType = PFD_TYPE_RGBA;
	    pixelFormatDescriptor.cColorBits = 32;
	    pixelFormatDescriptor.cRedBits = 8;
	    pixelFormatDescriptor.cGreenBits = 8;
	    pixelFormatDescriptor.cBlueBits = 8;
	    pixelFormatDescriptor.cAlphaBits = 8;
	    pixelFormatDescriptor.cDepthBits = 24;
	    pixelFormatDescriptor.cStencilBits = 8;

	    int pixelFormat = ChoosePixelFormat( m_deviceContext, &pixelFormatDescriptor );
	    if ( 0 == pixelFormat )
	    {
		    GUCEF_ERROR_LOG( CORE::LOGLEVEL_NORMAL, "Win32GLWindowContext: Failed to get the desired pixel format" );
		    Shutdown();
            return false;
	    }

	    if ( FALSE == SetPixelFormat( m_deviceContext, pixelFormat, &pixelFormatDescriptor ) )
	    {
		    GUCEF_ERROR_LOG( CORE::LOGLEVEL_NORMAL, "Win32GLWindowContext: Could not set pixel format" );
		    Shutdown();
            return false;
	    }

	    m_renderContext = wglCreateContext( m_deviceContext );
	    if ( NULL == m_renderContext )
	    { 
		    GUCEF_ERROR_LOG( CORE::LOGLEVEL_NORMAL, "Win32GLWindowContext: Could not create OpenGL rendering context" );
		    Shutdown();
            return false;
	    }

	    if ( wglMakeCurrent( m_deviceContext, m_renderContext ) == FALSE )
	    {
		    GUCEF_ERROR_LOG( CORE::LOGLEVEL_NORMAL, "Win32GLWindowContext: Could not make OpenGL rendering context current" );
		    Shutdown();
            return false;
	    }

        GUCEF_SYSTEM_LOG( CORE::LOGLEVEL_NORMAL, "Win32GLWindowContext: Succesfully created OpenGL rendering context" );
        m_window.Show();
        return true;
    }
    return false;
}

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

} /* namespace GUIDRIVERWIN32GL */
} /* namespace GUCEF */

/*-------------------------------------------------------------------------*/
