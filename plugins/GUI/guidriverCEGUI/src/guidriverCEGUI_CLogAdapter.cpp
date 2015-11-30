/*
 *  guidriverCEGUI: glue module for the CEGUI GUI backend
 *  Copyright (C) 2002 - 2008.  Dinand Vanvelzen
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

#ifndef GUCEF_CORE_CCOREGLOBAL_H
#include "gucefCORE_CCoreGlobal.h"
#define GUCEF_CORE_CCOREGLOBAL_H
#endif /* GUCEF_CORE_CCOREGLOBAL_H ? */

#include "guidriverCEGUI_CLogAdapter.h"

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

namespace GUCEF {
namespace GUIDRIVERCEGUI {

/*-------------------------------------------------------------------------//
//                                                                         //
//      CLASSES                                                            //
//                                                                         //
//-------------------------------------------------------------------------*/

CLogAdapter::CLogAdapter( void )
    : Logger()                                             ,
      m_logManager( &GUCEF::CORE::CCoreGlobal::Instance()->GetLogManager() )
{GUCEF_TRACE;

    assert( m_logManager != NULL );
}

/*-------------------------------------------------------------------------*/

CLogAdapter::~CLogAdapter()
{GUCEF_TRACE;

}

/*-------------------------------------------------------------------------*/

void
CLogAdapter::logEvent( const CEGUI::String& message                      ,
                               CEGUI::LoggingLevel level /* = CEGUI::Standard */ )
{GUCEF_TRACE;

    if ( getLoggingLevel() >= level )
    {
        static const GUCEF::CORE::CString logMsgPrefix = "[CEGUI] ";
        m_logManager->Log( GUCEF::CORE::CLogManager::LOG_SYSTEM ,
                           static_cast< Int32 >( level )        ,
                           logMsgPrefix + message.c_str()       );
    }
}

/*-------------------------------------------------------------------------*/

void
CLogAdapter::setLogFilename( const CEGUI::String& filename , 
                                     bool append /* = false */     )
{GUCEF_TRACE;

    // do nothing
}

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace MYGUI */
}; /* namespace GUCEF */

/*-------------------------------------------------------------------------*/
