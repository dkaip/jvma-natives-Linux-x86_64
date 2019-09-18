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

    void populateVmaStats(
            JNIEnv *env,
            jobject jVmaStatsObject,
            const VmaStats *vmaStats,
            std::vector<void *> *memoryToFree);

    void populateVmaStatInfo(
            JNIEnv *env,
            jobject jVmaStatInfoObject,
            const VmaStatInfo *vmaStatInfo,
            std::vector<void *> *memoryToFree);

    void getVmaAllocationCreateInfo(
            JNIEnv *env,
            jobject jVmaAllocationCreateInfoObject,
            VmaAllocationCreateInfo *vmaAllocationCreateInfo,
            std::vector<void *> *memoryToFree);

    void getVmaAllocationCreateInfoCollection(
            JNIEnv *env,
            const jobject jVmaAllocationCreateInfoCollectionObject,
            VmaAllocationCreateInfo **vmaAllocationCreateInfos,
            int *numberOfVmaAllocationCreateInfos,
            std::vector<void *> *memoryToFree);

    void getVmaPoolCreateInfo(
            JNIEnv *env,
            jobject jVmaPoolCreateInfoObject,
            VmaPoolCreateInfo *vmaPoolCreateInfo,
            std::vector<void *> *memoryToFree);

    void populateVmaPoolStats(
            JNIEnv *env,
            jobject jVmaPoolStatsObject,
            const VmaPoolStats *vmaPoolStats,
            std::vector<void *> *memoryToFree);

    void populateVmaAllocationInfo(
            JNIEnv *env,
            jobject jVmaAllocationInfoObject,
            const VmaAllocationInfo *vmaAllocationInfo,
            std::vector<void *> *memoryToFree);

    void getVmaDefragmentationInfo2(
            JNIEnv *env,
            jobject jVmaDefragmentationInfo2Object,
            VmaDefragmentationInfo2 *vmaDefragmentationInfo2,
            std::vector<void *> *memoryToFree);

    void populateVmaDefragmentationStats(
            JNIEnv *env,
            jobject jVmaDefragmentationStatsObject,
            const VmaDefragmentationStats *vmaDefragmentationStats,
            std::vector<void *> *memoryToFree);
}
#endif /* HELPERFUNCTIONS_HH_ */
