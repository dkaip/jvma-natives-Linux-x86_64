/*
 * vmaFindMemoryTypeIndex.cpp
 *
 *  Created on: Sep 3, 2019
 *      Author: Douglas Kaip
 */

#include "JVmaHelperFunctions.hh"
#include "JVulkanHelperFunctions.hh"
#include "com_CIMthetics_jvma_NativeProxies.h"
#include "slf4j.hh"

/*
 * Class:     com_CIMthetics_jvma_NativeProxies
 * Method:    vmaFindMemoryTypeIndex
 * Signature: (Lcom/CIMthetics/jvma/Handles/VmaAllocator;Ljava/util/EnumSet;Lcom/CIMthetics/jvma/Structures/CreateInfos/VmaAllocationCreateInfo;Lcom/CIMthetics/jvulkan/VulkanCore/VK11/Structures/IntReturnValue;)Lcom/CIMthetics/jvulkan/VulkanCore/VK11/Enums/VkResult;
 */
JNIEXPORT jobject JNICALL Java_com_CIMthetics_jvma_NativeProxies_vmaFindMemoryTypeIndex
  (JNIEnv *env, jobject, jobject jVmaAllocator, jobject jMemoryTypeBitsObject, jobject jVmaAllocationCreateInfoObject, jobject jMemoryTypeIndex)
{
    struct VmaAllocator_T *vmaAllocator = (struct VmaAllocator_T *)jvulkan::getHandleValue(env, jVmaAllocator);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Could not retrieve VmaAllocator handle");
        return jvulkan::createVkResult(env, VK_RESULT_MAX_ENUM);
    }

    VkMemoryPropertyFlags flags = jvulkan::getEnumSetValue(
            env,
            jMemoryTypeBitsObject,
            "com/CIMthetics/jvulkan/VulkanCore/VK11/Enums/VkMemoryPropertyFlagBits");
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Error calling getEnumSetValue");
        return jvulkan::createVkResult(env, VK_RESULT_MAX_ENUM);
    }

    std::vector<void *> memoryToFree(5);
    VmaAllocationCreateInfo vmaAllocationCreateInfo = {};
    jvma::getVmaAllocationCreateInfo(
            env,
            jVmaAllocationCreateInfoObject,
            &vmaAllocationCreateInfo,
            &memoryToFree);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Error calling getVmaAllocationCreateInfo");
        return jvulkan::createVkResult(env, VK_RESULT_MAX_ENUM);
    }

    uint32_t memoryTypeIndex = -1;
    VkResult result = vmaFindMemoryTypeIndex(vmaAllocator, flags, &vmaAllocationCreateInfo, &memoryTypeIndex);
    LOGERROR(env, "MemoryTypeIndex is %d", memoryTypeIndex);

    jclass theClass = env->GetObjectClass(jMemoryTypeIndex);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Error calling GetObjectClass");
        return jvulkan::createVkResult(env, VK_RESULT_MAX_ENUM);
    }

    jmethodID methodId = env->GetMethodID(theClass, "setValue", "(I)V");
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Could not find method id for setValue");
        return jvulkan::createVkResult(env, VK_RESULT_MAX_ENUM);
    }

    env->CallVoidMethod(jMemoryTypeIndex, methodId, memoryTypeIndex);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Error calling CallVoidMethod");
        return jvulkan::createVkResult(env, VK_RESULT_MAX_ENUM);
    }

    jvulkan::freeMemory(&memoryToFree);

    return jvulkan::createVkResult(env, result);
}
