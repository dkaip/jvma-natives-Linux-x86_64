/*
 * vmaAllocateMemoryForImage.cpp
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
 * Method:    vmaAllocateMemoryForImage
 * Signature: (Lcom/CIMthetics/jvma/Handles/VmaAllocator;Lcom/CIMthetics/jvulkan/VulkanCore/VK11/Handles/VkImage;Lcom/CIMthetics/jvma/Structures/CreateInfos/VmaAllocationCreateInfo;Lcom/CIMthetics/jvma/Handles/VmaAllocation;Lcom/CIMthetics/jvma/Structures/VmaAllocationInfo;)Lcom/CIMthetics/jvulkan/VulkanCore/VK11/Enums/VkResult;
 */
JNIEXPORT jobject JNICALL Java_com_CIMthetics_jvma_NativeProxies_vmaAllocateMemoryForImage
  (JNIEnv *env, jobject, jobject jVmaAllocator, jobject jVkImage, jobject jVmaAllocationCreateInfo, jobject jVmaAllocation, jobject jVmaAllocationInfo)
{
    struct VmaAllocator_T *vmaAllocator = (struct VmaAllocator_T *)jvulkan::getHandleValue(env, jVmaAllocator);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Could not retrieve VmaAllocator handle");
        return jvulkan::createVkResult(env, VK_RESULT_MAX_ENUM);
    }

    VkImage_T *vkImage = (VkImage_T *)jvulkan::getHandleValue(env, jVkImage);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Could not retrieve VkImage handle");
        return jvulkan::createVkResult(env, VK_RESULT_MAX_ENUM);
    }

    std::vector<void *> memoryToFree(5);
    VmaAllocationCreateInfo vmaAllocationCreateInfo = {};
    jvma::getVmaAllocationCreateInfo(
            env,
            jVmaAllocationCreateInfo,
            &vmaAllocationCreateInfo,
            &memoryToFree);

    VmaAllocation vmaAllocation = nullptr;
    VmaAllocationInfo vmaAllocationInfo = {};
    VkResult result = (VkResult)-1;

    if (jVmaAllocationInfo == nullptr)
    {
        result = vmaAllocateMemoryForImage(
                vmaAllocator,
                vkImage,
                &vmaAllocationCreateInfo,
                &vmaAllocation,
                nullptr);
    }
    else
    {
        result = vmaAllocateMemoryForImage(
                vmaAllocator,
                vkImage,
                &vmaAllocationCreateInfo,
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

    jvulkan::setHandleValue(env, jVmaAllocation, vmaAllocation);

    return jvulkan::createVkResult(env, result);
}
