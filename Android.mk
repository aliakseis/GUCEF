#-------------------------------------------------------------------
# This file has been automatically generated by ProjectGenerator    
# which is part of a build system designed for GUCEF                
#     (Galaxy Unlimited Framework)                                  
# For the latest info, see http://www.VanvelzenSoftware.com/        
#                                                                   
# The contents of this file are placed in the public domain. Feel   
# free to make use of it in any way you like.                       
#-------------------------------------------------------------------


#
# This is the project makefile which includes all modules which are part of this project
#
# PROJECT: "GUCEF"
#

ifndef $(PROJECT_ROOT_PATH)
  PROJECT_ROOT_PATH := $(call my-dir)
endif

include $(CLEAR_VARS)

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/dependencies/miniupnpc
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/gucefCORE/plugins/dstorepluginPARSIFALXML/dependancy/libparsifal
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/gucefIMAGE/plugins/imgpluginDEVIL
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/gucefIMAGE/plugins/imgpluginFreeImage/dependencies/FreeImage
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/gucefINPUT/plugins/inputdriverOIS/dependency/OIS
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/gucefLOADER
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/gucefMT
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/gucefVFS/plugins/vfspluginZIP/dependencies/zlib
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/gucefCORE
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/gucefMT_TestApp
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/gucefVFS/plugins/vfspluginZIP/dependencies/zziplib/zzip
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/gucefCOMCORE
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/gucefCORE_TestApp
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/gucefIMAGE
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/gucefINPUT
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/gucefMATH
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/gucefVFS
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/gucefVFS/plugins/vfspluginDVP/dependencies/DVPACKSYS
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/tools/CMakeListGenerator
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/tools/DuplicateFileFinder
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/tools/FileReplacer
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/tools/HDFiller
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/tools/ProjectGenerator
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/tools/ReferenceUpdater
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/gucefCOM
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/gucefCOMCORE_TestApp
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/gucefCORE/plugins/dstorepluginPARSIFALXML
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/gucefIMAGE_TestApp
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/gucefINPUT/plugins/inputdriverDIRECTINPUT8
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/gucefINPUT/plugins/inputdriverMSWINMSG
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/gucefINPUT_TestApp
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/gucefVFS/plugins/vfspluginVP
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/tools/DVPPackTool
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/tools/ServerPortExtender
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/gucefCOM_TestApp
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/gucefDRN
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/gucefDRN_TestApp
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/gucefGUI
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/gucefIMAGE/plugins/imgpluginFreeImage
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/gucefINPUT/plugins/inputdriverOIS
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/gucefMULTIPLAY
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/gucefPATCHER
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/tools/PatchSetGenerator
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/tools/ArchiveDiffLib
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/gucefVFS/plugins/vfspluginDVP
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/tools/ArchiveDiff
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/tools/GucefLogServiceLib
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/tools/SVNMagicMerge
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/gucefSMDRN
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/gucefVFS/plugins/vfspluginZIP
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/tools/GucefLogServiceApp
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/tools/GucefLogServiceClientPlugin
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/tools/PatcherGUI/MFCPatcherGUI
include $(MY_MODULE_PATH)/Android.mk

