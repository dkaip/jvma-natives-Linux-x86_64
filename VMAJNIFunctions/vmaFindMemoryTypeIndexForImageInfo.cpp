/*
 * vmaFindMemoryTypeIndexForImageInfo.cpp
 *
 *  Created on: Sep 4, 2019
 *      Author: Douglas Kaip
 */

#include "JVmaHelperFunctions.hh"
#include "JVulkanHelperFunctions.hh"
#include "com_CIMthetics_jvma_NativeProxies.h"
#include "slf4j.hh"

/*
 * Class:     com_CIMthetics_jvma_NativeProxies
 * Method:    vmaFindMemoryTypeIndexForImageInfo
 * Signature: (Lcom/CIMthetics/jvma/Handles/VmaAllocator;Lcom/CIMthetics/jvulkan/VulkanCore/VK11/Structures/CreateInfos/VkImageCreateInfo;Lcom/CIMthetics/jvma/Structures/CreateInfos/VmaAllocationCreateInfo;Lcom/CIMthetics/jvulkan/VulkanCore/VK11/Structures/IntReturnValue;)Lcom/CIMthetics/jvulkan/VulkanCore/VK11/Enums/VkResult;
 */
JNIEXPORT jobject JNICALL Java_com_CIMthetics_jvma_NativeProxies_vmaFindMemoryTypeIndexForImageInfo
  (JNIEnv *env, jobject, jobject jVmaAllocator, jobject jVkImageCreateInfoObject, jobject jVmaAllocationCreateInfoObject, jobject jMemoryTypeIndex)
{
    struct VmaAllocator_T *vmaAllocator = (struct VmaAllocator_T *)jvulkan::getHandleValue(env, jVmaAllocator);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Could not retrieve VmaAllocator handle");
        return jvulkan::createVkResult(env, VK_RESULT_MAX_ENUM);
    }

    std::vector<void *> memoryToFree(5);
    VkImageCreateInfo vkImageCreateInfo = {};
    jvulkan::getVkImageCreateInfo(
            env,
            jVkImageCreateInfoObject,
            &vkImageCreateInfo,
            &memoryToFree);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Error calling getVkImageCreateInfo");
        return jvulkan::createVkResult(env, VK_RESULT_MAX_ENUM);
    }

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
    VkResult result = vmaFindMemoryTypeIndexForImageInfo(vmaAllocator, &vkImageCreateInfo, &vmaAllocationCreateInfo, &memoryTypeIndex);

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
