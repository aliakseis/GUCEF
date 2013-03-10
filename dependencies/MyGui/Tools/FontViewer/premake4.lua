--------------------------------------------------------------------
-- This file was automatically generated by ProjectGenerator
-- which is tooling part the build system designed for GUCEF
--     (Galaxy Unlimited Framework)
-- For the latest info, see http://www.VanvelzenSoftware.com/
--
-- The contents of this file are placed in the public domain. Feel
-- free to make use of it in any way you like.
--------------------------------------------------------------------
--

-- Configuration for module: MyGUI.FontViewer


configuration( { "LINUX" } )
  project( "MyGUI.FontViewer" )

configuration( { "WIN32" } )
  project( "MyGUI.FontViewer" )

configuration( { "WIN64" } )
  project( "MyGUI.FontViewer" )
location( os.getenv( "PM4OUTPUTDIR" ) )
configuration( { "LINUX" } )
kind( "ConsoleApp" )
configuration( { "WIN32" } )
kind( "WindowedApp" )
configuration( { "WIN64" } )
kind( "WindowedApp" )

configuration( { "LINUX" } )
  links( { "MyGUI.Engine", "MyGUI.OpenGLPlatform", "freetype" } )
  links( { "MyGUI.Engine", "MyGUI.OpenGLPlatform", "freetype" } )
  defines( { "MYGUI_USE_FREETYPE" } )

configuration( { "WIN32" } )
  links( { "MyGUI.Engine", "MyGUI.OpenGLPlatform", "freetype" } )
  links( { "MyGUI.Engine", "MyGUI.OpenGLPlatform", "freetype" } )
  defines( { "MYGUI_USE_FREETYPE" } )

configuration( { "WIN64" } )
  links( { "MyGUI.Engine", "MyGUI.OpenGLPlatform", "freetype" } )
  links( { "MyGUI.Engine", "MyGUI.OpenGLPlatform", "freetype" } )
  defines( { "MYGUI_USE_FREETYPE" } )


configuration( { "LINUX" } )
    vpaths { ["Platform Headers"] = { "**.h", "**.hpp", "**.hxx" } }
    files( {
      "DemoKeeper.h",
      "FontPanel.h",
      "FontView.h",
      "TextureView.h",
      "../../Common/Precompiled.h",
      "../../Common/Base/InputFocusInfo.h",
      "../../Common/Base/Main.h",
      "../../Common/Base/StatisticInfo.h",
      "../../Common/Base/OpenGL/BaseManager.h",
      "../../Common/Input/InputConverter.h",
      "../../Common/Input/OIS/InputManager.h",
      "../../Common/Input/OIS/PointerManager.h"
    } )

    vpaths { ["Platform Source"] = { "**.c", "**.cpp", "**.cs", "**.asm" } }
    files( {
      "DemoKeeper.cpp",
      "FontPanel.cpp",
      "FontView.cpp",
      "TextureView.cpp",
      "../../Common/Precompiled.cpp",
      "../../Common/Base/OpenGL/BaseManager.cpp",
      "../../Common/Input/OIS/InputManager.cpp",
      "../../Common/Input/OIS/PointerManager.cpp"
    } )



configuration( { "WIN32" } )
    vpaths { ["Platform Headers"] = { "**.h", "**.hpp", "**.hxx" } }
    files( {
      "DemoKeeper.h",
      "FontPanel.h",
      "FontView.h",
      "TextureView.h",
      "../../Common/Precompiled.h",
      "../../Common/Base/InputFocusInfo.h",
      "../../Common/Base/Main.h",
      "../../Common/Base/StatisticInfo.h",
      "../../Common/Base/OpenGL/BaseManager.h",
      "../../Common/Input/InputConverter.h",
      "../../Common/Input/Win32API/InputManager.h",
      "../../Common/Input/Win32API/PointerManager.h"
    } )

    vpaths { ["Platform Source"] = { "**.c", "**.cpp", "**.cs", "**.asm" } }
    files( {
      "DemoKeeper.cpp",
      "FontPanel.cpp",
      "FontView.cpp",
      "TextureView.cpp",
      "../../Common/Precompiled.cpp",
      "../../Common/Base/OpenGL/BaseManager.cpp",
      "../../Common/Input/Win32API/InputManager.cpp",
      "../../Common/Input/Win32API/PointerManager.cpp"
    } )



configuration( { "WIN64" } )
    vpaths { ["Platform Headers"] = { "**.h", "**.hpp", "**.hxx" } }
    files( {
      "DemoKeeper.h",
      "FontPanel.h",
      "FontView.h",
      "TextureView.h",
      "../../Common/Precompiled.h",
      "../../Common/Base/InputFocusInfo.h",
      "../../Common/Base/Main.h",
      "../../Common/Base/StatisticInfo.h",
      "../../Common/Base/OpenGL/BaseManager.h",
      "../../Common/Input/InputConverter.h",
      "../../Common/Input/Win32API/InputManager.h",
      "../../Common/Input/Win32API/PointerManager.h"
    } )

    vpaths { ["Platform Source"] = { "**.c", "**.cpp", "**.cs", "**.asm" } }
    files( {
      "DemoKeeper.cpp",
      "FontPanel.cpp",
      "FontView.cpp",
      "TextureView.cpp",
      "../../Common/Precompiled.cpp",
      "../../Common/Base/OpenGL/BaseManager.cpp",
      "../../Common/Input/Win32API/InputManager.cpp",
      "../../Common/Input/Win32API/PointerManager.cpp"
    } )


configuration( {} )
includedirs( { "../../../freetype/include", "../../../freetype/include/freetype", "../../../freetype/include/freetype/config", "../../../freetype/include/freetype/internal", "../../../freetype/include/freetype/internal/services", "../../../freetype/src/winfonts", "../../Common/FileSystemInfo", "../../MyGUIEngine/include", "../../Platforms/OpenGL/OpenGLPlatform/include", "../../Platforms/OpenGL/OpenGLPlatform/include/GL" } )

configuration( { "LINUX" } )
includedirs( { "../"FontViewer", "../../Common", "../../Common/Base", "../../Common/Base/OpenGL", "../../Common/Input", "../../Common/Input/OIS" } )

configuration( { "WIN32" } )
includedirs( { "../"FontViewer", "../../Common", "../../Common/Base", "../../Common/Base/OpenGL", "../../Common/Input", "../../Common/Input/Win32API" } )

configuration( { "WIN64" } )
includedirs( { "../"FontViewer", "../../Common", "../../Common/Base", "../../Common/Base/OpenGL", "../../Common/Input", "../../Common/Input/Win32API" } )
