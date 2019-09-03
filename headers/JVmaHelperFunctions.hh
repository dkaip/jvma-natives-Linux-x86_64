#include <vector>
#include <jni.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>
#include "vk_mem_alloc.h"

#ifndef HELPERFUNCTIONS_HH_
#define HELPERFUNCTIONS_HH_

namespace jvma
{
//    jobject createVkResult(JNIEnv *env, jint value);

//    int32_t getEnumSetValue(
//            JNIEnv *env,
//            const jobject enumSetObject,
//            const char *enumClassName);

//    void *getHandleValue(JNIEnv *env, jobject jHandle);

//    void setHandleValue(JNIEnv *env, jobject jHandle, void *value);

//    void freeMemory(std::vector<void *> *memoryToFree);

    void getVmaAllocatorCreateInfo(
            JNIEnv *env,
            jobject jVmaAllocatorCreateInfoObject,
            VmaAllocatorCreateInfo *vmaAllocatorCreateInfo,
            std::vector<void *> *memoryToFree);

    void getVmaRecordSettings(
            JNIEnv *env,
            jobject jVmaRecordSettingsObject,
            VmaRecordSettings *vmaRecordSettings,
            std::vector<void *> *memoryToFree);
}
#endif /* HELPERFUNCTIONS_HH_ */
