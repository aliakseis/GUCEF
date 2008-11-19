/*
 *  gucefCORE: GUCEF module providing O/S abstraction and generic solutions
 *  Copyright (C) 2002 - 2007.  Dinand Vanvelzen
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA 
 */

#ifndef GUCEF_CORE_CTSGOBSERVER_H
#define GUCEF_CORE_CTSGOBSERVER_H
 
/*-------------------------------------------------------------------------//
//                                                                         //
//      INCLUDES                                                           //
//                                                                         //
//-------------------------------------------------------------------------*/

#include "CPumpedObserver.h"

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

namespace GUCEF { 
namespace CORE {

/*-------------------------------------------------------------------------//
//                                                                         //
//      CLASSES                                                            //
//                                                                         //
//-------------------------------------------------------------------------*/

class CTSGNotifier;

/*-------------------------------------------------------------------------*/

/**
 *  Internally used class that is to be used in combination with the CTSGNotifier
 *  class to add observer behavior to the CTSGNotifier. To use the mechanism create
 *  CTSGNotifier object.
 */
class GUCEFCORE_EXPORT_CPP CTSGObserver : public CPumpedObserver
{
    protected:
    
    /**
     *  Event handler that simply forwards the eventid and the
     *  eventdata to the parent notifier.
     *
     *  @param notifier the notifier that sent the notification
     *  @param eventid the unique event id for an event
     *  @param eventdata optional notifier defined userdata
     */
    virtual void OnPumpedNotify( CNotifier* notifier           ,
                                 const CEvent& eventid         ,
                                 CICloneable* eventdata = NULL );

    private:
    friend class CTSGNotifier;
    
    CTSGObserver( CPulseGenerator& pulsGenerator );                           
    
    virtual ~CTSGObserver();
    
    void SetParent( CTSGNotifier* parentNotifier );
    
    void AddEventToMailbox( CNotifier* notifier           ,
                            const CEvent& eventid         ,
                            CICloneable* eventdata = NULL );
                            
    void DoLockData( void ) const;
    
    void DoUnlockData( void ) const;
    
    private:
    
    CTSGObserver( void );
    
    CTSGObserver( const CTSGObserver& src );
    
    CTSGObserver& operator=( const CTSGObserver& src );
    
    private:
    
    CTSGNotifier* m_parentNotifier;
};

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace CORE */
}; /* namespace GUCEF */

/*-------------------------------------------------------------------------*/

#endif /* GUCEF_CORE_CTSGOBSERVER_H  ? */