/*
 *  gucefCOMCORE: GUCEF module providing basic communication facilities
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
 
/*-------------------------------------------------------------------------//
//                                                                         //
//      INCLUDES                                                           //
//                                                                         //
//-------------------------------------------------------------------------*/

#ifndef GUCEFCORE_H
#include "gucefCORE.h"          /* GUCEF CORE library API */
#define GUCEFCORE_H
#endif /* GUCEFCORE_H ? */

#ifndef GUCEFCOMCORE_H
#include "gucefCOMCORE.h"       /* GUCEF COMCORE library API */
#define GUCEFCOMCORE_H
#endif /* GUCEFCOMCORE_H ? */

#ifdef GUCEF_MSWIN_BUILD
  #include <windows.h>
#else
  #include <assert.h>
#endif

/*-------------------------------------------------------------------------//
//                                                                         //
//      MACROS                                                             //
//                                                                         //
//-------------------------------------------------------------------------*/

#ifndef GUCEF_MSWIN_BUILD
  #define DebugBreak() assert( 0 )
#endif

#define ERRORHERE { printf( "Test failed @ %s(%d)\n", __FILE__, __LINE__ ); DebugBreak(); }

/*-------------------------------------------------------------------------//
//                                                                         //
//      CONSTANTS                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

#define MAX_PINGS    1
#define PING_BYTES   32
#define PING_TIMEOUT 1000
#define REMOTE_HOST  "127.0.0.1"

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

using namespace GUCEF;

/*-------------------------------------------------------------------------//
//                                                                         //
//      CLASSES                                                            //
//                                                                         //
//-------------------------------------------------------------------------*/

class CPingTester : public CORE::CGUCEFAppSubSystem
{
    public:
    
    /*---------------------------------------------------------------------*/
    
    static CPingTester* Instance( void )
    {GUCEF_TRACE;
        
        if ( NULL == m_instance )
        {
            m_instance = new CPingTester();
        }
        return m_instance;
    }
    
    /*---------------------------------------------------------------------*/
    
    private:
    
    /*---------------------------------------------------------------------*/
    
    static void Deinstance( void )
    {GUCEF_TRACE;
    
        delete m_instance;
        m_instance = NULL;
    }
    
    /*---------------------------------------------------------------------*/
    
    CPingTester( void )
        : CORE::CGUCEFAppSubSystem( true ) ,
          m_pingCount( 0 )                 ,
          m_ping()
    {GUCEF_TRACE;
    
        printf( "**** STARTING THE PING TEST ****\n" );
        
        SubscribeTo( &m_ping );
    }
    
    /*---------------------------------------------------------------------*/
    
    virtual ~CPingTester()
    {GUCEF_TRACE;
    
    }
    
    /*---------------------------------------------------------------------*/
    
    protected:
    
    /*---------------------------------------------------------------------*/
    
    virtual void OnNotify( CORE::CNotifier* notifier           ,
                           const CORE::CEvent& eventid         ,
                           CORE::CICloneable* eventdata = NULL )
    {GUCEF_TRACE;
    
        if ( eventid == CORE::CGUCEFApplication::AppInitEvent )
        {   
            printf( "CPingTester: pinging %s for %d time(s) with %d bytes and a timeout of %d ms\n", REMOTE_HOST, MAX_PINGS, PING_BYTES, PING_TIMEOUT );
            if ( !m_ping.Start( REMOTE_HOST  , 
                                MAX_PINGS    ,
                                PING_BYTES   ,
                                PING_TIMEOUT ) )
            {
                // Failed to start the ping sequence
                printf( "ERROR: CPingTester: Failed to start the ping sequence\n" );
                ERRORHERE;
            }
            printf( "CPingTester: Ping started\n" );
        }
        else
        if ( eventid == CORE::CGUCEFApplication::AppShutdownEvent )
        {
            printf( "CPingTester: The application is shutting down\n" );
            // @TODO: ScheduleForDestruction 
        }
        else
        if ( eventid == COMCORE::CPing::PingReponseEvent )
        {
            COMCORE::CPing::TPingReponseEventData* eData = static_cast< COMCORE::CPing::TPingReponseEventData* >( eventdata );
            if ( NULL == eData )
            {
                // We should have received data with this event
                printf( "ERROR: CPingTester: no event data for event PingReponseEvent\n" );
                ERRORHERE;
            }            
            printf( "CPingTester: Received ping response from %s: %d ms\n", REMOTE_HOST, eData->GetData() );
                        
            if ( m_pingCount > MAX_PINGS )
            {
                // check if the maximum ping count functionality is working
                printf( "ERROR: CPingTester: we are getting more ping responses then we asked for\n" );
                ERRORHERE;
            }
            ++m_pingCount;
        }
        else
        if ( eventid == COMCORE::CPing::PingTimeoutEvent )
        {   
            // We are pinging REMOTE_HOST, we should not get a timeout (unless REMOTE_HOST is having a bad day)
            printf( "ERROR: CPingTester: timeout while pinging %s, this should not happen\n", REMOTE_HOST );
            ERRORHERE;
        }
        else
        if ( eventid == COMCORE::CPing::PingFailedEvent )
        {   
            // some error occurred while attempting to ping
            printf( "ERROR: CPingTester: error while pinging\n" );
            ERRORHERE;
        }
        else
        if ( eventid == COMCORE::CPing::PingStoppedEvent )
        {
            // If we got here without any errors then we are finished
            printf( "CPingTester: Stopped pinging\n" );
            printf( "**** SUCCESSFULLY COMPLETED THE PING TEST ****\n" );
            CORE::CGUCEFApplication::Instance()->Stop();
            printf( "CPingTester: Application stopped\n" );
        }                
        else
        {
            printf( "CPingTester: Received event: %s\n", eventid.GetName() );
        }
    }
    
    /*---------------------------------------------------------------------*/
    
    private:
    
    CORE::UInt32 m_pingCount;
    COMCORE::CPing m_ping;
    static CPingTester* m_instance;   
};

/*-------------------------------------------------------------------------//
//                                                                         //
//      GLOBAL VARS                                                        //
//                                                                         //
//-------------------------------------------------------------------------*/

CPingTester* CPingTester::m_instance = NULL;

/*-------------------------------------------------------------------------//
//                                                                         //
//      UTILITIES                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

void
PerformPingTest( void )
{
    #ifdef DEBUG_MODE
    //CORE::GUCEF_LogStackToStdOut();
    //CORE::GUCEF_SetStackLogging( 1 );
    #endif /* DEBUG_MODE ? */
    
    try
    {
        CPingTester::Instance();
        CORE::CGUCEFApplication::Instance()->main( 0, NULL, true );
    }
    catch ( ... )
    {
        printf( "ERROR unhandled exception during test\n" );
        #ifdef DEBUG_MODE
        CORE::GUCEF_PrintCallstack();
        #endif /* DEBUG_MODE ? */
        ERRORHERE;
    }
}

/*-------------------------------------------------------------------------*/