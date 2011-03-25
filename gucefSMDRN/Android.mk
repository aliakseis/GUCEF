#-------------------------------------------------------------------
# This file has been automatically generated by ProjectGenerator    
# which is part of a build system designed for GUCEF                
#     (Galaxy Unlimited Framework)                                  
# For the latest info, see http://www.VanvelzenSoftware.com/        
#                                                                   
# The contents of this file are placed in the public domain. Feel   
# free to make use of it in any way you like.                       
#-------------------------------------------------------------------


ifndef $(MY_MODULE_PATH)
  MY_MODULE_PATH := $(call my-dir)
endif
LOCAL_PATH := $(MY_MODULE_PATH)

include $(CLEAR_VARS)

@echo Module path: $(MY_MODULE_PATH)
LOCAL_MODULE := gucefSMDRN
@echo Module name: $(LOCAL_MODULE)

LOCAL_SRC_FILES := \
  src/gucefSMDRN_CModule.cpp \
  src/gucefSMDRN_CSectorGrid.cpp \
  src/gucefSMDRN_CSectorPosition.cpp \
  src/gucefSMDRN_CSectorSegment.cpp \
  src/gucefSMDRN_CZoneArbiter.cpp \
  src/gucefSMDRN_CZoneClient.cpp \
  src/gucefSMDRN_CZoneGrid.cpp

LOCAL_C_INCLUDES := \
  include \
  ../gucefCOM/include \
  ../gucefCOMCORE/include \
  ../gucefCORE/include \
  ../gucefDRN/include \
  ../gucefMT/include


LOCAL_SHARED_LIBRARIES := \
  gucefCORE \
  gucefMT \
  gucefCOMCORE \
  gucefCOM \
  gucefDRN

include $(BUILD_SHARED_LIBRARY)

