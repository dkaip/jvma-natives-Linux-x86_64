/*
 * Copyright 2019 Douglas Kaip
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/*
 * vmaAllocateMemoryForBuffer.cpp
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
 * Method:    vmaAllocateMemoryForBuffer
 * Signature: (Lcom/CIMthetics/jvma/Handles/VmaAllocator;Lcom/CIMthetics/jvulkan/VulkanCore/VK11/Handles/VkBuffer;Lcom/CIMthetics/jvma/Structures/CreateInfos/VmaAllocationCreateInfo;Lcom/CIMthetics/jvma/Handles/VmaAllocation;Lcom/CIMthetics/jvma/Structures/VmaAllocationInfo;)Lcom/CIMthetics/jvulkan/VulkanCore/VK11/Enums/VkResult;
 */
JNIEXPORT jobject JNICALL Java_com_CIMthetics_jvma_NativeProxies_vmaAllocateMemoryForBuffer
  (JNIEnv *env, jobject, jobject jVmaAllocator, jobject jVkBuffer, jobject jVmaAllocationCreateInfo, jobject jVmaAllocation, jobject jVmaAllocationInfo)
{
    struct VmaAllocator_T *vmaAllocator = (struct VmaAllocator_T *)jvulkan::getHandleValue(env, jVmaAllocator);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Could not retrieve VmaAllocator handle");
        return jvulkan::createVkResult(env, VK_RESULT_MAX_ENUM);
    }

    VkBuffer_T *vkBuffer = (VkBuffer_T *)jvulkan::getHandleValue(env, jVkBuffer);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Could not retrieve VkBuffer handle");
        return jvulkan::createVkResult(env, VK_RESULT_MAX_ENUM);
    }

    std::vector<void *> memoryToFree(5);
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

    VmaAllocation vmaAllocation = nullptr;
    VmaAllocationInfo vmaAllocationInfo = {};
    VkResult result = (VkResult)-1;

    if (jVmaAllocationInfo == nullptr)
    {
        result = vmaAllocateMemoryForBuffer(
                vmaAllocator,
                vkBuffer,
                &vmaAllocationCreateInfo,
                &vmaAllocation,
                nullptr);
    }
    else
    {
        result = vmaAllocateMemoryForBuffer(
                vmaAllocator,
                vkBuffer,
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
