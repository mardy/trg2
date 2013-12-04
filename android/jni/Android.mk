LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := libtrg2
LOCAL_SRC_FILES := $(wildcard ../../src/*.cpp) ../../build/l44_texture.c ../../external/stb_image.c
LOCAL_CPPFLAGS := -DANDROID
LOCAL_LDFLAGS := -lGLESv1_CM -llog

include $(BUILD_SHARED_LIBRARY)
