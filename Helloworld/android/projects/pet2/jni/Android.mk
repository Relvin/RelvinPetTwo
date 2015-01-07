LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_CFLAGS += -DTARGET_PLATFORM_ANDROID=1 -DNDEBUG

define all-cpp-files-under
$(patsubst ./%,%, $(shell find $(1) -name "platform" -prune -o -name "*.cpp" -and -not -name ".*"))
endef


EXTRA_SRC1 := $(call all-cpp-files-under, $(LOCAL_PATH)/../../gamenative) \
			$(call all-cpp-files-under, $(LOCAL_PATH)/../../../platform-mgr/native)\
			$(call all-cpp-files-under, $(LOCAL_PATH)/../../../../Data)\
			$(call all-cpp-files-under, $(LOCAL_PATH)/../../../../Classes)\
			$(call all-cpp-files-under, $(LOCAL_PATH)/../../../../Network)\
			$(call all-cpp-files-under, $(LOCAL_PATH)/../../../../Support)\
			$(call all-cpp-files-under, $(LOCAL_PATH)/../../../../../../../share)

LOCAL_SRC_FILES := hellocpp/main.cpp \
					../../../../../../CocosDenshion/include/sound_system_fmod.cpp\
                   $(EXTRA_SRC1:$(LOCAL_PATH)/%=%)

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../../Classes
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../gamenative
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../platform-mgr/native
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../Classes/
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../Classes/Scenes
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../Classes/platform_Code
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../Classes/UmengShare
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../Classes/UmengShare/Android
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../Classes/UmengShare/Common
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../Classes/UmengShare/ShareButton
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../Data
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../Network
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../Support
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../../../../share/
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../../../../share/Packet
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../../../../share/reader
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../../../../share/stringReader


LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static
LOCAL_SHARED_LIBRARIES  := third_fmod_shared

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,CocosDenshion/android)
$(call import-module,extensions)
$(call import-module,external/Box2D)
$(call import-module,external/chipmunk)
$(call import-module,CocosDenshion/android/lib)
