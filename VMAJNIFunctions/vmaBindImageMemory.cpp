/*
 * vmaBindImageMemory.cpp
 *
 *  Created on: Sep 17, 2019
 *      Author: Douglas Kaip
 */

#include "JVmaHelperFunctions.hh"
#include "JVulkanHelperFunctions.hh"
#include "com_CIMthetics_jvma_NativeProxies.h"
#include "slf4j.hh"

/*
 * Class:     com_CIMthetics_jvma_NativeProxies
 * Method:    vmaBindImageMemory
 * Signature: (Lcom/CIMthetics/jvma/Handles/VmaAllocator;Lcom/CIMthetics/jvma/Handles/VmaAllocation;Lcom/CIMthetics/jvulkan/VulkanCore/VK11/Handles/VkImage;)Lcom/CIMthetics/jvulkan/VulkanCore/VK11/Enums/VkResult;
 */
JNIEXPORT jobject JNICALL Java_com_CIMthetics_jvma_NativeProxies_vmaBindImageMemory
  (JNIEnv *env, jobject, jobject jVmaAllocator, jobject jVmaAllocation, jobject jVkImage)
{
    struct VmaAllocator_T *vmaAllocator = (struct VmaAllocator_T *)jvulkan::getHandleValue(env, jVmaAllocator);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Could not retrieve VmaAllocator handle");
        return jvulkan::createVkResult(env, VK_RESULT_MAX_ENUM);
    }

    struct VmaAllocation_T *vmaAllocation = (struct VmaAllocation_T *)jvulkan::getHandleValue(env, jVmaAllocation);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Could not retrieve VmaAllocation handle");
        return jvulkan::createVkResult(env, VK_RESULT_MAX_ENUM);
    }

    VkImage_T *vkImage = (VkImage_T *)jvulkan::getHandleValue(env, jVkImage);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Could not retrieve VkImage handle");
        return jvulkan::createVkResult(env, VK_RESULT_MAX_ENUM);
    }

    VkResult result = vmaBindImageMemory(
            vmaAllocator,
            vmaAllocation,
            vkImage);

    return jvulkan::createVkResult(env, result);
}
