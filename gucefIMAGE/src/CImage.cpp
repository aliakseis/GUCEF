/*
 *  gucefIMAGE: GUCEF module providing image utilities
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

#ifndef GUCEF_CORE_CCODECREGISTRY_H
#include "CCodecRegistry.h"
#define GUCEF_CORE_CCODECREGISTRY_H
#endif /* GUCEF_CORE_CCODECREGISTRY_H ? */

#ifndef GUCEF_IMAGE_CIMGCODEC_H
#include "CIMGCodec.h"
#define GUCEF_IMAGE_CIMGCODEC_H
#endif /* GUCEF_IMAGE_CIMGCODEC_H ? */

#include "CImage.h"       /* Header for this class */

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

namespace GUCEF {
namespace IMAGE {

/*-------------------------------------------------------------------------//
//                                                                         //
//      UTILITIES                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

GUCEF_IMPLEMENT_MSGEXCEPTION( CImage, EInvalidIndex );

/*--------------------------------------------------------------------------*/

CImage::CImage( void )
    : m_frameList()
{GUCEF_TRACE;

}

/*--------------------------------------------------------------------------*/

CImage::CImage( const TFrameList& frameList )
    : m_frameList( frameList )
{GUCEF_TRACE;

}

/*--------------------------------------------------------------------------*/
    
CImage::CImage( const TMipMapList& mipmapList )
    : m_frameList()
{GUCEF_TRACE;

    m_frameList.push_back( mipmapList );
}

/*--------------------------------------------------------------------------*/
    
CImage::CImage( const TPixelMapPtr& pixelMapPtr )
    : m_frameList()
{GUCEF_TRACE;

    TMipMapList mipmapList;
    mipmapList.push_back( pixelMapPtr );
    m_frameList.push_back( mipmapList );
}

/*--------------------------------------------------------------------------*/

void
CImage::Assign( const TFrameList& frameList )
{GUCEF_TRACE;

    // First we clean up our toys
    Clear();
    
    // Assign the image data
    m_frameList = frameList;
}

/*--------------------------------------------------------------------------*/
    
void
CImage::Assign( const TMipMapList& mipmapList )
{GUCEF_TRACE;

    // First we clean up our toys
    Clear();
    
    // Assign the image data
    m_frameList.push_back( mipmapList );
}

/*--------------------------------------------------------------------------*/
    
void
CImage::Assign( const TPixelMapPtr& pixelMapPtr )
{GUCEF_TRACE;

    // First we clean up our toys
    Clear();
    
    // Assign the image data
    TMipMapList mipmapList;
    mipmapList.push_back( pixelMapPtr );    
    m_frameList.push_back( mipmapList );
}

/*--------------------------------------------------------------------------*/

void
CImage::AddFrame( TMipMapList& imageFrame )
{GUCEF_TRACE;

    m_frameList.push_back( imageFrame );
}

/*--------------------------------------------------------------------------*/

void
CImage::AddFrame( TPixelMapPtr& imageFrame )
{GUCEF_TRACE;

    TMipMapList mipMapList;
    mipMapList.push_back( imageFrame );
    m_frameList.push_back( mipMapList );
}

/*--------------------------------------------------------------------------*/

void
CImage::SetFrame( TPixelMapPtr& imageFrame          ,
                  const UInt32 frameIndex /* = 0 */ )
{GUCEF_TRACE;

    TMipMapList mipMapList;
    mipMapList.push_back( imageFrame );
    SetFrame( mipMapList, frameIndex );    
}

/*--------------------------------------------------------------------------*/

void
CImage::SetFrame( TMipMapList& imageFrame           ,
                  const UInt32 frameIndex /* = 0 */ )
{GUCEF_TRACE;
    
    if ( frameIndex < m_frameList.size() )
    {
        m_frameList[ frameIndex ] = imageFrame;
    }
    else
    if ( frameIndex == m_frameList.size() )
    {
        m_frameList.push_back( imageFrame );
    }
    else
    {
        GUCEF_EMSGTHROW( EInvalidIndex, "CImage::SetFrame(): Invalid frame index" );
    }
}

/*--------------------------------------------------------------------------*/

CImage::~CImage()
{GUCEF_TRACE;
        Clear();
}

/*-------------------------------------------------------------------------*/

UInt32
CImage::GetFrameCount( void ) const
{GUCEF_TRACE;

    return static_cast< UInt32 >( m_frameList.size() );
}

/*-------------------------------------------------------------------------*/

UInt32
CImage::GetMipmapLevels( const UInt32 frameIndex /* = 0 */ ) const
{GUCEF_TRACE;

    if ( m_frameList.size() > frameIndex )
    {
        return static_cast< UInt32 >( m_frameList[ frameIndex ].size() );
    }
    
    GUCEF_EMSGTHROW( EInvalidIndex, "CImage::GetMipmapLevels(): Invalid frame index" );
}

/*-------------------------------------------------------------------------*/

void
CImage::Clear( void )
{
    // Because we are using shared pointers all we have to do is clear the list
    // this will cause things to be de-allocated as needed
    m_frameList.clear();
}

/*-------------------------------------------------------------------------*/

CImage::TPixelMapPtr
CImage::GetPixelMap( const UInt32 frameIndex /* = 0 */  ,
                     const UInt32 mipMapLevel /* = 0 */ ) const
{GUCEF_TRACE;

    if ( m_frameList.size() > frameIndex )
    {
        const TMipMapList& mipmapList = m_frameList[ frameIndex ];
        if ( mipmapList.size() > mipMapLevel )
        {
            return mipmapList[ mipMapLevel ];
        }
    }
    
    GUCEF_EMSGTHROW( EInvalidIndex, "CImage::GetFrame(): Invalid frame or mipmap index" );    
}

/*-------------------------------------------------------------------------*/

CImage::TMipMapList&
CImage::GetFrame( const UInt32 frameIndex /* = 0 */ )
{GUCEF_TRACE;

    if ( m_frameList.size() > frameIndex )
    {
        return m_frameList[ frameIndex ];
    }
    
    GUCEF_EMSGTHROW( EInvalidIndex, "CImage::GetFrame(): Invalid frame or mipmap index" );    
}

/*-------------------------------------------------------------------------*/

const CImage::TMipMapList&
CImage::GetFrame( const UInt32 frameIndex /* = 0 */ ) const
{GUCEF_TRACE;

    if ( m_frameList.size() > frameIndex )
    {
        return m_frameList[ frameIndex ];
    }
    
    GUCEF_EMSGTHROW( EInvalidIndex, "CImage::GetFrame(): Invalid frame or mipmap index" );    
}

/*-------------------------------------------------------------------------*/

bool
CImage::HasFrames( void ) const
{GUCEF_TRACE;

    return !m_frameList.empty();
}

/*-------------------------------------------------------------------------*/

UInt32
CImage::GetTotalPixelStorageSize( void ) const
{GUCEF_TRACE;

    UInt32 totalBytes = 0;
    TFrameList::const_iterator i = m_frameList.begin();
    while ( i != m_frameList.end() )
    {
        const TMipMapList& mipmapList = (*i);
        TMipMapList::const_iterator n = mipmapList.begin();
        while ( n != mipmapList.end() )
        {
            totalBytes += (*n)->GetTotalSizeInBytes();
            ++n;
        }
        ++i;
    }
    
    return totalBytes;
}

/*-------------------------------------------------------------------------*/

bool
CImage::Load( CORE::CIOAccess& data         ,
              const CORE::CString& dataType )
{GUCEF_TRACE;

    // Find an image codec using the file extension       
    CORE::CCodecRegistry::TCodecFamilyRegistryPtr codecRegistry = CORE::CCodecRegistry::Instance()->Lookup( "ImageCodec" );
    if ( NULL != codecRegistry )
    {
        CORE::CCodecRegistry::TICodecPtr codec = codecRegistry->Lookup( dataType );
        if ( NULL != codec )
        {
            // We have found a codec we can use, now try to load the data
            CIMGCodec codecUtil( codec );
            return codecUtil.Decode( data  ,
                                     *this );
        }
    }
    return false;
}

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

} /* namespace IMAGE */
} /* namespace GUCEF */

/*--------------------------------------------------------------------------*/




