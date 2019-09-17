/*
 * populateVmaAllocationInfo.cpp
 *
 *  Created on: Sep 9, 2019
 *      Author: Douglas Kaip
 */

#include "JVmaHelperFunctions.hh"
#include "JVulkanHelperFunctions.hh"
#include "com_CIMthetics_jvma_NativeProxies.h"
#include "slf4j.hh"

extern const char *voidMethodErrorText;

namespace jvma
{
    void populateVmaAllocationInfo(
            JNIEnv *env,
            jobject jVmaAllocationInfoObject,
            const VmaAllocationInfo *vmaAllocationInfo,
            std::vector<void *> *memoryToFree)
    {
        if (jVmaAllocationInfoObject == nullptr)
        {
            LOGERROR(env, "%s", "jVmaAllocationInfoObject == nullptr");
            env->ThrowNew(env->FindClass("java/lang/Exception"), "jVmaAllocationInfoObject == nullptr");
            return;
        }

        if (vmaAllocationInfo == nullptr)
        {
            LOGERROR(env, "%s", "vmaAllocationInfo == nullptr");
            env->ThrowNew(env->FindClass("java/lang/Exception"), "vmaAllocationInfo == nullptr");
            return;
        }

        jboolean handlingException = env->ExceptionCheck();
        if (handlingException == true)
        {
            LOGWARN(env, "%s", "handlingException was already true...clearing");
            env->ExceptionClear();
        }

        jclass theClass = env->GetObjectClass(
                jVmaAllocationInfoObject);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find class com/CIMthetics/jvma/Structures/VmaAllocationInfo");
            return;
        }

        ///////////////////////////////////////////////////////////////////////////
        jmethodID methodId = env->GetMethodID(theClass, "setMemoryType", "(I)V");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id setMemoryType");
            return;
        }

        env->CallVoidMethod(jVmaAllocationInfoObject, methodId, vmaAllocationInfo->memoryType);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", voidMethodErrorText);
            return;
        }

        ///////////////////////////////////////////////////////////////////////////
        methodId = env->GetMethodID(theClass, "setDeviceMemory", "(Lcom/CIMthetics/jvulkan/VulkanCore/VK11/Handles/VkDeviceMemory;)V");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id setDeviceMemory");
            return;
        }

        jobject handle = jvulkan::createVulkanHandle(env, "com/CIMthetics/jvulkan/VulkanCore/VK11/Handles/VkDeviceMemory", vmaAllocationInfo->deviceMemory);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling createVulkanHandle");
            return;
        }

        env->CallVoidMethod(jVmaAllocationInfoObject, methodId, handle);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", voidMethodErrorText);
            return;
        }

        ///////////////////////////////////////////////////////////////////////////
        methodId = env->GetMethodID(theClass, "setOffset", "(J)V");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id setOffset");
            return;
        }

        env->CallVoidMethod(jVmaAllocationInfoObject, methodId, vmaAllocationInfo->offset);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", voidMethodErrorText);
            return;
        }

        ///////////////////////////////////////////////////////////////////////////
        methodId = env->GetMethodID(theClass, "setSize", "(J)V");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id setSize");
            return;
        }

        env->CallVoidMethod(jVmaAllocationInfoObject, methodId, vmaAllocationInfo->size);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", voidMethodErrorText);
            return;
        }

        ///////////////////////////////////////////////////////////////////////////
        methodId = env->GetMethodID(theClass, "setMappedData", "(Lcom/CIMthetics/jvma/Handles/MappedData;)V");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id setMappedData");
            return;
        }

        handle = jvulkan::createVulkanHandle(env, "com/CIMthetics/jvma/Handles/MappedData", vmaAllocationInfo->pMappedData);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling createVulkanHandle");
            return;
        }

        env->CallVoidMethod(jVmaAllocationInfoObject, methodId, handle);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", voidMethodErrorText);
            return;
        }

        // TODO fix user data
    }
}
