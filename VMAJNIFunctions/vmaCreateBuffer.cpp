/*
 * vmaCreateBuffer.cpp
 *
 *  Created on: Sep 18, 2019
 *      Author: Douglas Kaip
 */

#include "JVmaHelperFunctions.hh"
#include "JVulkanHelperFunctions.hh"
#include "com_CIMthetics_jvma_NativeProxies.h"
#include "slf4j.hh"

/*
 * Class:     com_CIMthetics_jvma_NativeProxies
 * Method:    vmaCreateBuffer
 * Signature: (Lcom/CIMthetics/jvma/Handles/VmaAllocator;Lcom/CIMthetics/jvulkan/VulkanCore/VK11/Structures/CreateInfos/VkBufferCreateInfo;Lcom/CIMthetics/jvma/Structures/CreateInfos/VmaAllocationCreateInfo;Lcom/CIMthetics/jvulkan/VulkanCore/VK11/Handles/VkBuffer;Lcom/CIMthetics/jvma/Handles/VmaAllocation;Lcom/CIMthetics/jvma/Structures/VmaAllocationInfo;)Lcom/CIMthetics/jvulkan/VulkanCore/VK11/Enums/VkResult;
 */
JNIEXPORT jobject JNICALL Java_com_CIMthetics_jvma_NativeProxies_vmaCreateBuffer
  (JNIEnv *env, jobject, jobject jVmaAllocator, jobject jVkBufferCreateInfo, jobject jVmaAllocationCreateInfo, jobject jVkBuffer, jobject jVmaAllocation, jobject jVmaAllocationInfo)
{
    struct VmaAllocator_T *vmaAllocator = (struct VmaAllocator_T *)jvulkan::getHandleValue(env, jVmaAllocator);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Could not retrieve VmaAllocator handle");
        return jvulkan::createVkResult(env, VK_RESULT_MAX_ENUM);
    }

    std::vector<void *> memoryToFree(5);
    VkBufferCreateInfo vkBufferCreateInfo = {};
    jvulkan::getVkBufferCreateInfo(
            env,
            jVkBufferCreateInfo,
            &vkBufferCreateInfo,
            &memoryToFree);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Error calling getVkBufferCreateInfo");
        return jvulkan::createVkResult(env, VK_RESULT_MAX_ENUM);
    }

    VmaAllocationCreateInfo vmaAllocationCreateInfo = {};
    jvma::getVmaAllocationCreateInfo(
            env,
            jVmaAllocationCreateInfo,
            &vmaAllocationCreateInfo,
            &memoryToFree);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Error calling getVmaAllocationCreateInfo");
        return jvulkan::createVkResult(env, VK_RESULT_MAX_ENUM);
    }

    VkBuffer vkBuffer = nullptr;
    VmaAllocation vmaAllocation = nullptr;
    VmaAllocationInfo vmaAllocationInfo = {};
    VkResult result = (VkResult)-1;

    if (jVmaAllocationInfo == nullptr)
    {
        result = vmaCreateBuffer(
                vmaAllocator,
                &vkBufferCreateInfo,
                &vmaAllocationCreateInfo,
                &vkBuffer,
                &vmaAllocation,
                nullptr);
    }
    else
    {
        result = vmaCreateBuffer(
                vmaAllocator,
                &vkBufferCreateInfo,
                &vmaAllocationCreateInfo,
                &vkBuffer,
                &vmaAllocation,
                &vmaAllocationInfo);

        jvma::populateVmaAllocationInfo(
                env,
                jVmaAllocationInfo,
                &vmaAllocationInfo,
                &memoryToFree);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling populateVmaAllocationInfo");
        }

    }

    jvulkan::freeMemory(&memoryToFree);

    jvulkan::setHandleValue(env, jVkBuffer, vkBuffer);

    jvulkan::setHandleValue(env, jVmaAllocation, vmaAllocation);

    return jvulkan::createVkResult(env, result);
}
