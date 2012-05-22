/*
 *  guidriverMyGUI: glue module for the MyGUI GUI backend
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

#ifndef GUCEF_MYGUI_CDATAMANAGER_H
#define GUCEF_MYGUI_CDATAMANAGER_H

/*-------------------------------------------------------------------------//
//                                                                         //
//      INCLUDES                                                           //
//                                                                         //
//-------------------------------------------------------------------------*/

#ifndef __MYGUI_DATA_MANAGER_H__
#include "MyGUI_DataManager.h"
#define __MYGUI_DATA_MANAGER_H__
#endif /* __MYGUI_DATA_MANAGER_H__ ? */

#ifndef GUCEF_MYGUI_MACROS_H
#include "guceMyGUI_macros.h"     /* often used guceMYGUI macros */
#define GUCEF_MYGUI_MACROS_H
#endif /* GUCEF_MYGUI_MACROS_H ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      CLASSES                                                            //
//                                                                         //
//-------------------------------------------------------------------------*/

/*
 *      Forward declarations of classes used here
 */
namespace Ogre { class RenderWindow; class RenderTexture; class Root; }
namespace MyGUI { class Gui; class OgrePlatform; class OgreRenderManager; }
namespace GUCEF { namespace CORE { class CDataNode; } }

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

namespace GUCEF {
namespace MYGUI {

/*-------------------------------------------------------------------------//
//                                                                         //
//      CLASSES                                                            //
//                                                                         //
//-------------------------------------------------------------------------*/

class CDataManager : public MyGUI::DataManager
{
    public:

    virtual MyGUI::IDataStream* getData( const std::string& _name );

    virtual bool isDataExist( const std::string& _name );

    virtual const MyGUI::VectorString& getDataListNames( const std::string& pattern );

    virtual const std::string& getDataPath( const std::string& name );

    void SetGuiDataRoot( const CORE::CString& guiDataRootPath );

    const CORE::CString GetGuiDataRoot( void ) const;

    void SetResourceGroup( const CORE::CString& guiResourceGroup );

    const CORE::CString& GetResourceGroup( void ) const;

    private:

    CDataManager( const CDataManager& src );
    CDataManager& operator=( const CDataManager& src );

    const MyGUI::VectorString& getDataListNames( const std::string& pattern, bool fullpath );

    private:

    CString m_guiDataRoot;
    CString m_resourceGroup;
};

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

} /* namespace MYGUI */
} /* namespace GUCEF */

/*-------------------------------------------------------------------------*/

#endif /* GUCEF_MYGUI_CDATAMANAGER_H ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      Info & Changes                                                     //
//                                                                         //
//-------------------------------------------------------------------------//

- 08-04-2007 :
        - Initial implementation

---------------------------------------------------------------------------*/
