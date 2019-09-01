/*
 * getVmaAllocatorCreateInfo.cpp
 *
 *  Created on: Aug 29, 2019
 *      Author: Douglas Kaip
 */


#include "../headers/JVmaHelperFunctions.hh"
#include "slf4j.hh"

namespace jvma
{
    void getVmaAllocatorCreateInfo(
            JNIEnv *env,
            jobject jVmaAllocatorCreateInfoObject,
            VmaAllocatorCreateInfo *vmaAllocatorCreateInfo,
            std::vector<void *> *memoryToFree)
    {
        jclass theClass = env->GetObjectClass(jVmaAllocatorCreateInfoObject);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error trying to get class for jVmaAllocatorCreateInfoObject");
            return;
        }

        ////////////////////////////////////////////////////////////////////////
        jmethodID methodId = env->GetMethodID(theClass, "getFlags", "()Ljava/util/EnumSet;");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id for getFlags");
            return;
        }

        jobject flagsObject = env->CallObjectMethod(jVmaAllocatorCreateInfoObject, methodId);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling CallObjectMethod");
            return;
        }

        VmaAllocatorCreateFlags flags = getEnumSetValue(
                env,
                flagsObject,
                "com/CIMthetics/jvma/Enums/VmaAllocatorCreateFlagBits");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling getEnumSetValue");
            return;
        }


        ////////////////////////////////////////////////////////////////////////
        methodId = env->GetMethodID(theClass, "getPhysicalDevice", "()Lcom/CIMthetics/jvulkan/VulkanCore/VK11/Handles/VkPhysicalDevice;");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id for getPhysicalDevice");
            return;
        }

        jobject jVkPhysicalDeviceHandle = env->CallObjectMethod(jVmaAllocatorCreateInfoObject, methodId);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling CallObjectMethod");
            return;
        }

        VkPhysicalDevice_T *vulkanPhysicalDevice = (VkPhysicalDevice_T *)getHandleValue(env, jVkPhysicalDeviceHandle);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling getHandleValue");
            return;
        }

        ////////////////////////////////////////////////////////////////////////
        methodId = env->GetMethodID(theClass, "getDevice", "()Lcom/CIMthetics/jvulkan/VulkanCore/VK11/Handles/VkDevice;");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id for getDevice");
            return;
        }

        jobject jVkDeviceHandle = env->CallObjectMethod(jVmaAllocatorCreateInfoObject, methodId);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling CallObjectMethod");
            return;
        }

        VkDevice_T *vulkanLogicalDevice = (VkDevice_T *)getHandleValue(env, jVkDeviceHandle);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling getHandleValue");
            return;
        }

        ////////////////////////////////////////////////////////////////////////
        methodId = env->GetMethodID(theClass, "getPreferredLargeHeapBlockSize", "()J");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id for getPreferredLargeHeapBlockSize");
            return;
        }

        jlong preferredLargeHeapBlockSize = env->CallLongMethod(jVmaAllocatorCreateInfoObject, methodId);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling CallLongMethod");
            return;
        }

        // TODO get the getAllocationCallbacks
        // TODO get the getDeviceMemoryCallbacks
        ////////////////////////////////////////////////////////////////////////
        methodId = env->GetMethodID(theClass, "getFrameInUseCount", "()I");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id for getFrameInUseCount");
            return;
        }

        jint frameInUseCount = env->CallIntMethod(jVmaAllocatorCreateInfoObject, methodId);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling CallIntMethod");
            return;
        }

        ////////////////////////////////////////////////////////////////////////
        methodId = env->GetMethodID(theClass, "getHeapSizeLimit", "()[J");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id for getHeapSizeLimit");
            return;
        }

        jlongArray jHeapSizeLimitArrayObject = (jlongArray)env->CallObjectMethod(jVmaAllocatorCreateInfoObject, methodId);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling CallObjectMethod");
            return;
        }

        VkDeviceSize *pHeapSizeLimit = nullptr;
        jsize arrayLength = 0;
        if (jHeapSizeLimitArrayObject != nullptr)
        {
            arrayLength = env->GetArrayLength(jHeapSizeLimitArrayObject);

            pHeapSizeLimit = (uint64_t *)calloc(arrayLength, sizeof(uint64_t));
            memoryToFree->push_back(pHeapSizeLimit);

            env->GetLongArrayRegion(jHeapSizeLimitArrayObject, 0, arrayLength, (long int *)pHeapSizeLimit);
            if (env->ExceptionOccurred())
            {
                LOGERROR(env, "%s", "Error calling GetLongArrayRegion");
                return;
            }
        }

        // TODO implement the pVulkanFunctions stuff

        ////////////////////////////////////////////////////////////////////////
        methodId = env->GetMethodID(theClass, "getRecordSettings", "()Lcom/CIMthetics/jvma/Structures/VmaRecordSettings;");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id for getRecordSettings");
            return;
        }

        jobject jVmaRecordSettingsObject = env->CallObjectMethod(jVmaAllocatorCreateInfoObject, methodId);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling CallObjectMethod");
            return;
        }

        VmaRecordSettings *vmaRecordSettings = nullptr;
        if (jVmaRecordSettingsObject != nullptr)
        {
            vmaRecordSettings = (VmaRecordSettings *)calloc(1, sizeof(VmaRecordSettings));
            getVmaRecordSettings(
                    env,
                    jVmaRecordSettingsObject,
                    vmaRecordSettings,
                    memoryToFree);
            if (env->ExceptionOccurred())
            {
                LOGERROR(env, "%s", "Error calling getVmaRecordSettings");
                return;
            }
        }

        vmaAllocatorCreateInfo->flags = flags;
        vmaAllocatorCreateInfo->physicalDevice = vulkanPhysicalDevice;
        vmaAllocatorCreateInfo->device = vulkanLogicalDevice;
        vmaAllocatorCreateInfo->preferredLargeHeapBlockSize = preferredLargeHeapBlockSize;
        vmaAllocatorCreateInfo->pAllocationCallbacks = nullptr;
        vmaAllocatorCreateInfo->pDeviceMemoryCallbacks = nullptr;
        //TODO implement these
//        vmaAllocatorCreateInfo->pAllocationCallbacks = allocationCallbacks;
//        vmaAllocatorCreateInfo->pDeviceMemoryCallbacks = deviceMemoryCallbacks;
        vmaAllocatorCreateInfo->frameInUseCount = frameInUseCount;
        vmaAllocatorCreateInfo->pHeapSizeLimit = pHeapSizeLimit;
        vmaAllocatorCreateInfo->pVulkanFunctions = nullptr;
        // TODO Implement
//        vmaAllocatorCreateInfo->pVulkanFunctions = vulkanFunctions;
        vmaAllocatorCreateInfo->pRecordSettings = vmaRecordSettings;
    }
}
