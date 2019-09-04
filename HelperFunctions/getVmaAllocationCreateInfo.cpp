/*
 * getVmaAllocationCreateInfo.cpp
 *
 *  Created on: Sep 3, 2019
 *      Author: Douglas Kaip
 */

#include "JVmaHelperFunctions.hh"
#include "JVulkanHelperFunctions.hh"
#include "slf4j.hh"

namespace jvma
{
    void getVmaAllocationCreateInfo(
            JNIEnv *env,
            jobject jVmaAllocationCreateInfoObject,
            VmaAllocationCreateInfo *vmaAllocationCreateInfo,
            std::vector<void *> *memoryToFree)
    {
        jclass theClass = env->GetObjectClass(jVmaAllocationCreateInfoObject);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error trying to get class for jVmaAllocationCreateInfoObject");
            return;
        }

        ////////////////////////////////////////////////////////////////////////
        jmethodID methodId = env->GetMethodID(theClass, "getFlags", "()Ljava/util/EnumSet;");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id for getFlags");
            return;
        }

        jobject flagsObject = env->CallObjectMethod(jVmaAllocationCreateInfoObject, methodId);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling CallObjectMethod");
            return;
        }

        VmaAllocationCreateFlags flags = jvulkan::getEnumSetValue(
                env,
                flagsObject,
                "com/CIMthetics/jvma/Enums/VmaAllocationCreateFlagBits");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling getEnumSetValue");
            return;
        }

        ////////////////////////////////////////////////////////////////////////
        methodId = env->GetMethodID(theClass, "getUsage", "()Lcom/CIMthetics/jvma/Enums/VmaMemoryUsage;");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id for getUsage");
            return;
        }

        jobject jVmaMemoryUsageObject = env->CallObjectMethod(jVmaAllocationCreateInfoObject, methodId);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling CallObjectMethod");
            return;
        }

        jclass jVmaMemoryUsageEnumClass = env->GetObjectClass(jVmaMemoryUsageObject);

        jmethodID valueOfMethodId = env->GetMethodID(jVmaMemoryUsageEnumClass, "valueOf", "()I");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id for valueOf");
            return;
        }

        VmaMemoryUsage memoryUsageEnumValue = (VmaMemoryUsage)env->CallIntMethod(jVmaMemoryUsageObject, valueOfMethodId);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling CallIntMethod");
            return;
        }

        ////////////////////////////////////////////////////////////////////////
        methodId = env->GetMethodID(theClass, "getRequiredFlags", "()Ljava/util/EnumSet;");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id for getRequiredFlags");
            return;
        }

        flagsObject = env->CallObjectMethod(jVmaAllocationCreateInfoObject, methodId);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling CallObjectMethod");
            return;
        }

        VkMemoryPropertyFlags requiredFlags = jvulkan::getEnumSetValue(
                env,
                flagsObject,
                "com/CIMthetics/jvulkan/VulkanCore/VK11/Enums/VkMemoryPropertyFlagBits");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling getEnumSetValue");
            return;
        }

        ////////////////////////////////////////////////////////////////////////
        methodId = env->GetMethodID(theClass, "getPreferredFlags", "()Ljava/util/EnumSet;");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id for getPreferredFlags");
            return;
        }

        flagsObject = env->CallObjectMethod(jVmaAllocationCreateInfoObject, methodId);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling CallObjectMethod");
            return;
        }

        VkMemoryPropertyFlags preferredFlags = jvulkan::getEnumSetValue(
                env,
                flagsObject,
                "com/CIMthetics/jvulkan/VulkanCore/VK11/Enums/VkMemoryPropertyFlagBits");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling getEnumSetValue");
            return;
        }

        ////////////////////////////////////////////////////////////////////////
        methodId = env->GetMethodID(theClass, "getMemoryTypeBits", "()I");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id for getMemoryTypeBits");
            return;
        }

        jint jMemoryTypeBits = env->CallIntMethod(jVmaAllocationCreateInfoObject, methodId);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling CallIntMethod");
            return;
        }

        uint32_t memoryTypeBits = (uint32_t)jMemoryTypeBits;

        ////////////////////////////////////////////////////////////////////////
        methodId = env->GetMethodID(theClass, "getPool", "()Lcom/CIMthetics/jvma/Handles/VmaPool;");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id for getPool");
            return;
        }

        jobject jVmaPool = env->CallObjectMethod(jVmaAllocationCreateInfoObject, methodId);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling CallObjectMethod");
            return;
        }

        struct VmaPool_T *vmaPool = nullptr;
        if(jVmaPool != nullptr)
        {
            vmaPool = (struct VmaPool_T *)jvulkan::getHandleValue(env, jVmaPool);
            if (env->ExceptionOccurred())
            {
                LOGERROR(env, "%s", "Could not retrieve jVmaPool handle");
                return;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        methodId = env->GetMethodID(theClass, "getpUserData", "()Ljava/lang/Object;");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id for getpUserData");
            return;
        }

        jobject jUserDataObject = env->CallObjectMethod(jVmaAllocationCreateInfoObject, methodId);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling CallObjectMethod");
            return;
        }


        vmaAllocationCreateInfo->flags = flags;
        vmaAllocationCreateInfo->usage = memoryUsageEnumValue;
        vmaAllocationCreateInfo->requiredFlags = requiredFlags;
        vmaAllocationCreateInfo->preferredFlags = preferredFlags;
        vmaAllocationCreateInfo->memoryTypeBits = memoryTypeBits;
        vmaAllocationCreateInfo->pool = vmaPool;
        // TODO fix this
        vmaAllocationCreateInfo->pUserData = nullptr;

    }
}
