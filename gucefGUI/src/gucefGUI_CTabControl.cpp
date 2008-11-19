/*
 *  gucefGUI: GUCEF module providing a uniform interface towards GUI backends
 *  Copyright (C) 2002 - 2007.  Dinand Vanvelzen
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

#include "gucefGUI_CTabControl.h"

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

namespace GUCEF {
namespace GUI {

/*-------------------------------------------------------------------------//
//                                                                         //
//      GLOBAL VARS                                                        //
//                                                                         //
//-------------------------------------------------------------------------*/

const CORE::CEvent CTabControl::ActiveTabChangedEvent = "GUCEF::GUI::CTabControl::ActiveTabChangedEvent";

/*-------------------------------------------------------------------------//
//                                                                         //
//      UTILITIES                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

void
CTabControl::RegisterEvents( void )
{
    ActiveTabChangedEvent.Initialize();
}

/*-------------------------------------------------------------------------*/

CTabControl::CTabControl( void )
    : CWidget()
{GUCEF_TRACE;

    RegisterEvents();
}

/*-------------------------------------------------------------------------*/
    
CTabControl::~CTabControl()
{GUCEF_TRACE;

}

/*-------------------------------------------------------------------------*/

Int32
CTabControl::GetActiveTab( void ) const
{GUCEF_TRACE;

    return -1;
}

/*-------------------------------------------------------------------------*/

bool
CTabControl::SetActiveTab( const UInt32 tabIndex )
{GUCEF_TRACE;

    return false;
}

/*-------------------------------------------------------------------------*/

CTabContentPane*
CTabControl::GetTabContentPane( const UInt32 tabIndex )
{GUCEF_TRACE;

    return NULL;
}

/*-------------------------------------------------------------------------*/
    
const CString&
CTabControl::GetClassTypeName( void ) const
{GUCEF_TRACE;

    static const CString classTypeName = "GUCEF::GUI::CTabControl";
    return classTypeName;
}

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace GUI */
}; /* namespace GUCEF */

/*-------------------------------------------------------------------------*/
