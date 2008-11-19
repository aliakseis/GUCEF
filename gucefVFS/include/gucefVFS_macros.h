/*
 *  gucefVFS: GUCEF module implementing a Virtual File System
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
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA 
 */

#ifndef GUCEF_VFS_MACROS_H
#define GUCEF_VFS_MACROS_H

/*
 *      Build configuration specific macros.
 *      Also includes the generic macros which are build config independant.
 */

/*-------------------------------------------------------------------------//
//                                                                         //
//      INCLUDES                                                           //
//                                                                         //
//-------------------------------------------------------------------------*/

#ifndef GUCEF_CORE_BASICMACROS_H
#include "macros.h"                /* generic often used macros */
#define GUCEF_CORE_BASICMACROS_H
#endif /* GUCEF_CORE_BASICMACROS_H ? */

#ifndef GUCEF_VFS_ETYPES_H
#include "gucefVFS_ETypes.h"      /* simple types */
#define GUCEF_VFS_ETYPES_H
#endif /* GUCEF_VFS_ETYPES_H ? */

#ifndef GUCEF_VFS_CONFIG_H
#include "gucefVFS_config.h"      /* Module build configuration */
#define GUCEF_VFS_CONFIG_H
#endif /* GUCEF_VFS_CONFIG_H ? */

#ifndef GUCEF_CORE_CLOGMANAGER_H
#include "CLogManager.h"
#define GUCEF_CORE_CLOGMANAGER_H
#endif /* GUCEF_CORE_CLOGMANAGER_H ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      GENERAL MACROS                                                     //
//                                                                         //
//-------------------------------------------------------------------------*/

/*
 *      O/S Detection macro.
 *      If you don't want to use the auto detection macro then set
 *      the MANUAL_OS_DEFINE define in the config file.
 */
#ifndef MANUAL_OS_DEFINE
  #if defined( WIN32 ) || defined( _WIN32 )
    #define GUCEF_MSWIN_BUILD
  #elif defined( linux )
    #define GUCEF_LINUX_BUILD
  #else
    #error Cannot automaticly detect your operating system
  #endif  
#endif /* MANUAL_OS_DEFINE ? */

/*-------------------------------------------------------------------------*/

/*
 *      Auto detection of debug mode
 */
#ifndef MANUAL_DEBUG_MODE_DEFINE
  #if defined( _DEBUG )
    #define DEBUG_MODE
  #else
    #undef DEBUG_MODE
  #endif /* compiler DEBUG switches */
#endif /* MANUAL_DEBUG_MODE_DEFINE ? */

/*-------------------------------------------------------------------------*/

/*
 *      In debug mode we will include the core module's tracer
 */
#ifdef __cplusplus
  #ifdef GUCEF_VFS_DEBUG_MODE
    #ifndef GUCEF_CORE_CTRACER_H
      #include "CTracer.h"
      #define GUCEF_CORE_CTRACER_H
    #endif /* GUCEF_CORE_CTRACER_H ? */
  #else
    #ifndef GUCEF_TRACE
      #define GUCEF_TRACE
    #endif /* GUCEF_TRACE ? */
  #endif
#endif /* __cplusplus ? */

/*-------------------------------------------------------------------------*/

/*
 *      Macro for enabling/disabling the GUCEF namespace
 */
#undef GUCEF_NAMESPACE_BEGIN
#undef GUCEF_NAMESPACE_END   
#ifdef USE_GUCEF_NAMESPACE
  #define GUCEF_NAMESPACE_BEGIN   namespace GUCEF {
  #define GUCEF_NAMESPACE_END     }
#else
  #define GUCEF_NAMESPACE_BEGIN
  #define GUCEF_NAMESPACE_END
#endif /* USE_GUCEF_NAMESPACE ? */

/*-------------------------------------------------------------------------*/

/*
 *      Macro for enabling/disabling the CORE namespace
 */
#undef VFS_NAMESPACE_BEGIN
#undef VFS_NAMESPACE_END   
#ifdef USE_VFS_NAMESPACE
  #define VFS_NAMESPACE_BEGIN   namespace VFS {
  #define VFS_NAMESPACE_END     }
#else
  #define VFS_NAMESPACE_BEGIN
  #define VFS_NAMESPACE_END
#endif /* USE_VFS_NAMESPACE ? */

/*-------------------------------------------------------------------------*/

/*
 *      When compiling the gucefVFS library you should define BUILD_GUCEFVFS_DLL
 *      before including this macro file.
 */
#ifndef MANUAL_EXPORT_DEFINE
  #undef USE_DLL
  #undef BUILD_DLL
  #ifdef BUILD_GUCEFVFS_DLL
    #define BUILD_DLL
  #else
    #define USE_DLL 
  #endif
#endif /* MANUAL_EXPORT_DEFINE ? */

/*-------------------------------------------------------------------------*/

/*
 *      Macros for dynamic linking or static linking. Use the switches in the
 *      config file to control the export type.
 */
#undef EXPORT
#ifdef GUCEF_MSWIN_BUILD
  #ifdef BUILD_DLL
    #define EXPORT __declspec( dllexport )
  #else
    #ifdef USE_DLL
      #define EXPORT __declspec( dllimport )
    #else
      #define EXPORT
    #endif /* USE_DLL */
  #endif /* BUILD_DLL */
#else
  #define EXPORT   /* Linux does not need an additional directive */
#endif /* GUCEF_MSWIN_BUILD ? */

#undef EXPORT_CPP
#ifdef EXPORT_CPP_CODE
  #define EXPORT_CPP EXPORT
#else
  #define EXPORT_CPP
#endif /* EXPORT_CPP_CODE */

#undef EXPORT_C 
#ifdef EXPORT_C_CODE
  #define EXPORT_C EXPORT
#else
  #define EXPORT_C
#endif /* EXPORT_C_CODE */

#define GUCEF_VFS_EXPORT_CPP EXPORT_CPP

/*-------------------------------------------------------------------------*/

/*
 *      Change calling convention notation depending on the compiler used.
 */
#if defined ( __BORLANDC__ ) || defined ( _MSC_VER )
  #define CALLSPEC_C __cdecl
#else  
  #define CALLSPEC_C cdecl
#endif  
#if defined ( __BORLANDC__ ) || defined ( _MSC_VER )
  #define CALLSPEC_STD __stdcall
#else  
  #define CALLSPEC_STD stdcall
#endif 

#undef CALLSPEC_TYPE
#ifdef USE_CALLSPEC_C 
  #define CALLSPEC_TYPE CALLSPEC_C
#else 
  #ifdef USE_CALLSPEC_STD  
    #define CALLSPEC_TYPE CALLSPEC_STD
  #else  
    #ifdef USE_CALLSPEC_PASCAL    
      #define CALLSPEC_TYPE CALLSPEC_PASCAL
    #else 
       #ifdef USE_CALLSPEC_FAST  
         #define CALLSPEC_TYPE CALLSPEC_FAST
       #else  
         #error No calling convention configuration was specified
       #endif    
     #endif
  #endif
#endif  

#undef PLUGIN_CALLSPEC_TYPE
#ifdef USE_PLUGIN_CALLSPEC_C 
  #define PLUGIN_CALLSPEC_TYPE CALLSPEC_C
#else 
  #ifdef USE_PLUGIN_CALLSPEC_STD  
    #define PLUGIN_CALLSPEC_TYPE CALLSPEC_STD
  #else  
    #ifdef USE_PLUGIN_CALLSPEC_PASCAL    
      #define PLUGIN_CALLSPEC_TYPE CALLSPEC_PASCAL
    #else 
       #ifdef USE_PLUGIN_CALLSPEC_FAST  
         #define PLUGIN_CALLSPEC_TYPE CALLSPEC_FAST
       #else  
         #error No calling convention configuration was specified for plugins 
       #endif    
     #endif
  #endif
#endif        
      
/*
 *      Macro that switches between a calling convention prefix and
 *      postfix notation.
 */
#undef CALLSPEC_PREFIX
#undef CALLSPEC_SUFFIX
#undef PLUGIN_CALLSPEC_PREFIX
#undef PLUGIN_CALLSPEC_SUFFIX
#if defined ( __BORLANDC__ ) || defined ( _MSC_VER )
  #define CALLSPEC_PREFIX CALLSPEC_TYPE
  #define CALLSPEC_SUFFIX
  #define PLUGIN_CALLSPEC_PREFIX PLUGIN_CALLSPEC_TYPE  
  #define PLUGIN_CALLSPEC_SUFFIX
#else
  #define CALLSPEC_PREFIX
  #define CALLSPEC_SUFFIX  __attribute__((CALLSPEC_TYPE))
  #define PLUGIN_CALLSPEC_PREFIX   
  #define PLUGIN_CALLSPEC_SUFFIX __attribute__((PLUGIN_CALLSPEC_TYPE)) 
#endif

/*-------------------------------------------------------------------------*/

/*
 *      Detection of 32/64 bits builds. 
 */
#ifndef MANUAL_BITTARGET_DEFINE
  #undef GUCEF32BIT
  #undef GUCEF64BIT
  #if defined ( GUCEF_MSWIN_BUILD ) && ( defined( _WIN32 ) || defined( WIN32 ) )
    #define GUCEF32BIT
  #elif defined ( GUCEF_MSWIN_BUILD ) && ( defined( _WIN64 ) || defined( WIN64 ) )
    #define GUCEF64BIT
  #else  
    #error Cannot autodetect wheter this is a 32 or 64 bit build
  #endif
#endif

/*-------------------------------------------------------------------------*/

/*
 *      Usefull macro when parsing path strings cross-platform
 *      Allows you to use the same code to swap out dir seperators
 */
#undef DIRSEPCHAR
#undef DIRSEPCHAROPPOSITE
#ifdef GUCEF_MSWIN_BUILD
  #define DIRSEPCHAR         '\\'
  #define DIRSEPCHAROPPOSITE '/'
#else
  #define DIRSEPCHAR         '/'
  #define DIRSEPCHAROPPOSITE '\\'
#endif 

/*-------------------------------------------------------------------------*/

/*
 *      Small macro that changes integers used for storing memory 
 *      addresses to 32 or 64 bit depending on the build target.
 *      Usage of INTPTR allows you to safely cast or manipulate a 
 *      pointer as an integer.  
 */
#undef INTPTR 
#ifdef GUCEF32BIT
  #define INTPTR UInt32
#else /* 64 Bit target */
  #define INTPTR UInt64
#endif  

/*-------------------------------------------------------------------------*/

#ifdef DEBUG_MODE
  #ifndef TSPRINTING_H
    #include "tsprinting.h"
    #define TSPRINTING_H
  #endif /* TSPRINTING_H ? */
#endif /* DEBUG_MODE ? */

/*-------------------------------------------------------------------------*/

#undef DEBUGOUTPUT 
#undef DEBUGOUTPUTs
#undef DEBUGOUTPUTi
#undef DEBUGOUTPUTss
#undef DEBUGOUTPUTsi
#undef DEBUGOUTPUTis
#undef DEBUGOUTPUTsss
#ifdef DEBUG_MODE
  #ifdef ADD_EXTRA_INFO_TO_DEBUGOUTPUT
    #define DEBUGOUTPUT( c_str ) ( GUCEF::CORE::tsprintf( "%s @ Line %d File %s\n", c_str, __LINE__, __FILE__ ) )
    #define DEBUGOUTPUTs DEBUGOUTPUT
    #define DEBUGOUTPUTi( intval ) ( GUCEF::CORE::tsprintf( "%i @ Line %d File %s\n", intval, __LINE__, __FILE__ ) )    
    #define DEBUGOUTPUTss( c_str1, c_str2 ) ( GUCEF::CORE::tsprintf( "%s%s @ Line %d File %s\n", c_str1, c_str2, __LINE__, __FILE__ ) )
    #define DEBUGOUTPUTis( intval, c_str ) ( GUCEF::CORE::tsprintf( "%i%s @ Line %d File %s\n", intval, c_str, __LINE__, __FILE__ ) )
    #define DEBUGOUTPUTsi( c_str, intval ) ( GUCEF::CORE::tsprintf( "%s%i @ Line %d File %s\n", c_str, intval, __LINE__, __FILE__ ) )    
    #define DEBUGOUTPUTsss( c_str1, c_str2, c_str3 ) ( GUCEF::CORE::tsprintf( "%s%s%s @ Line %d File %s\n", c_str1, c_str2, c_str3, __LINE__, __FILE__ ) )
  #else
    #define DEBUGOUTPUT( c_str ) { GUCEF::CORE::tsprintf( "%s\n", c_str ); }
    #define DEBUGOUTPUTs DEBUGOUTPUT
    #define DEBUGOUTPUTi( intval ) ( GUCEF::CORE::tsprintf( "%i\n", intval ) )    
    #define DEBUGOUTPUTss( c_str1, c_str2 ) ( GUCEF::CORE::tsprintf( "%s%s\n", c_str1, c_str2 ) )
    #define DEBUGOUTPUTis( intval, c_str ) ( GUCEF::CORE::tsprintf( "%i%s\n", intval, c_str ) )
    #define DEBUGOUTPUTsi( c_str, intval ) ( GUCEF::CORE::tsprintf( "%s%i\n", c_str, intval ) )
    #define DEBUGOUTPUTsss( c_str1, c_str2, c_str3 ) ( GUCEF::CORE::tsprintf( "%s%s%s\n", c_str1, c_str2, c_str3 ) )
  #endif  
#else
  #define DEBUGOUTPUT( c_str ) ( )
  #define DEBUGOUTPUTi ( intval ) ( )
  #define DEBUGOUTPUTs DEBUGOUTPUT
  #define DEBUGOUTPUTss( c_str1, c_str2 ) ( )
  #define DEBUGOUTPUTsi( c_str, intval ) ( )
  #define DEBUGOUTPUTis( intval, c_str ) ( )
  #define DEBUGOUTPUTsss( c_str1, c_str2, c_str3 ) ( )
#endif /* DEBUG_MODE ? */  

/*-------------------------------------------------------------------------*/

#endif /* GUCEF_VFS_MACROS_H ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      Info & Changes                                                     //
//                                                                         //
//-------------------------------------------------------------------------//

- 26-03-2005 :
       - Initial version of this file.

-----------------------------------------------------------------------------*/
