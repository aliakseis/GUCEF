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

#ifndef GUCEF_GUI_CIMAGEFRAME_H
#define GUCEF_GUI_CIMAGEFRAME_H

/*-------------------------------------------------------------------------//
//                                                                         //
//      INCLUDES                                                           //
//                                                                         //
//-------------------------------------------------------------------------*/

#ifndef GUCEF_IMAGE_CIMAGE_H
#include "CImage.h"
#define GUCEF_IMAGE_CIMAGE_H
#endif /* GUCEF_IMAGE_CIMAGE_H ? */

#ifndef GUCEF_GUI_CWIDGET_H
#include "gucefGUI_CWidget.h"
#define GUCEF_GUI_CWIDGET_H
#endif /* GUCEF_GUI_CWIDGET_H ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

namespace GUCEF {
namespace GUI {

/*-------------------------------------------------------------------------//
//                                                                         //
//      CLASSES                                                            //
//                                                                         //
//-------------------------------------------------------------------------*/

class GUCEF_GUI_EXPORT_CPP CImageFrame : public CWidget
{
    public:
    
    static const CORE::CEvent ImageChangedEvent;
    
    static void RegisterEvents( void );
    
    public:
    
    CImageFrame( void );
    
    virtual ~CImageFrame();
    
    virtual bool SetImage( const IMAGE::CImage& srcImage );
    
    private:
    
    CImageFrame( const CImageFrame& src );
    CImageFrame& operator=( const CImageFrame& src );
};

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace GUI */
}; /* namespace GUCEF */

/*-------------------------------------------------------------------------*/
          
#endif /* GUCEF_GUI_CIMAGEFRAME_H ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      Info & Changes                                                     //
//                                                                         //
//-------------------------------------------------------------------------//

- 18-08-2007 :
        - Dinand: Initial implementation

-----------------------------------------------------------------------------*/
