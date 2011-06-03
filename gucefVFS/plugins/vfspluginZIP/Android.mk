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
LOCAL_MODULE := vfspluginZIP
@echo Module name: $(LOCAL_MODULE)

LOCAL_SRC_FILES := \
  src/vfspluginZIP.cpp \
  src/vfspluginZIP_CZIPArchive.cpp \
  src/vfspluginZIP_CZipIOAccess.cpp

LOCAL_C_INCLUDES := \
  $(MY_MODULE_PATH)/include \
  $(MY_MODULE_PATH)/../../../common/include \
  $(MY_MODULE_PATH)/../../../gucefCORE/include \
  $(MY_MODULE_PATH)/../../../gucefCORE/include/android \
  $(MY_MODULE_PATH)/../../../gucefMT/include \
  $(MY_MODULE_PATH)/../../../gucefVFS/include \
  $(MY_MODULE_PATH)/dependencies/zziplib \
  $(MY_MODULE_PATH)/dependencies/zziplib/zzip

LOCAL_CFLAGS := -DZZIP_HAVE_STDINT_H -DGUCEF_VFSPLUGIN_ZIP_BUILD_MODULE


LOCAL_SHARED_LIBRARIES := \
  zziplib \
  gucefMT \
  gucefVFS \
  gucefCORE


LOCAL_LDLIBS := \
  -lzlib \
  -lz

include $(BUILD_SHARED_LIBRARY)

