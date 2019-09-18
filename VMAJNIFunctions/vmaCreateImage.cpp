/*
 * vmaCreateImage.cpp
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
 * Method:    vmaCreateImage
 * Signature: (Lcom/CIMthetics/jvma/Handles/VmaAllocator;Lcom/CIMthetics/jvulkan/VulkanCore/VK11/Structures/CreateInfos/VkImageCreateInfo;Lcom/CIMthetics/jvma/Structures/CreateInfos/VmaAllocationCreateInfo;Lcom/CIMthetics/jvulkan/VulkanCore/VK11/Handles/VkImage;Lcom/CIMthetics/jvma/Handles/VmaAllocation;Lcom/CIMthetics/jvma/Structures/VmaAllocationInfo;)Lcom/CIMthetics/jvulkan/VulkanCore/VK11/Enums/VkResult;
 */
JNIEXPORT jobject JNICALL Java_com_CIMthetics_jvma_NativeProxies_vmaCreateImage
  (JNIEnv *env, jobject, jobject jVmaAllocator, jobject jVkImageCreateInfo, jobject jVmaAllocationCreateInfo, jobject jVkImage, jobject jVmaAllocation, jobject jVmaAllocationInfo)
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
            jVkImageCreateInfo,
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
            jVmaAllocationCreateInfo,
            &vmaAllocationCreateInfo,
            &memoryToFree);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Error calling getVmaAllocationCreateInfo");
        return jvulkan::createVkResult(env, VK_RESULT_MAX_ENUM);
    }

    VkImage vkImage = nullptr;
    VmaAllocation vmaAllocation = nullptr;
    VmaAllocationInfo vmaAllocationInfo = {};
    VkResult result = (VkResult)-1;

    if (jVmaAllocationInfo == nullptr)
    {
        result = vmaCreateImage(
                vmaAllocator,
                &vkImageCreateInfo,
                &vmaAllocationCreateInfo,
                &vkImage,
                &vmaAllocation,
                nullptr);
    }
    else
    {
        result = vmaCreateImage(
                vmaAllocator,
                &vkImageCreateInfo,
                &vmaAllocationCreateInfo,
                &vkImage,
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

    jvulkan::setHandleValue(env, jVkImage, vkImage);

    jvulkan::setHandleValue(env, jVmaAllocation, vmaAllocation);

    return jvulkan::createVkResult(env, result);
}
