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
 * Signature: (Lcom/CIMthetics/jvma/Handles/VmaAllocator;ILcom/CIMthetics/jvma/Structures/CreateInfos/VmaAllocationCreateInfo;Lcom/CIMthetics/jvulkan/VulkanCore/VK11/Structures/IntReturnValue;)Lcom/CIMthetics/jvulkan/VulkanCore/VK11/Enums/VkResult;
 */
JNIEXPORT jobject JNICALL Java_com_CIMthetics_jvma_NativeProxies_vmaFindMemoryTypeIndex
  (JNIEnv *env, jobject, jobject jVmaAllocator, jint jMemoryTypeBits, jobject jVmaAllocationCreateInfoObject, jobject jMemoryTypeIndex)
{
    struct VmaAllocator_T *vmaAllocator = (struct VmaAllocator_T *)jvulkan::getHandleValue(env, jVmaAllocator);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Could not retrieve VmaAllocator handle");
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

    uint32_t memoryTypeBits = 0;
    if (jMemoryTypeBits == 0)
    {
        memoryTypeBits = UINT32_MAX;
    }
    else
    {
        memoryTypeBits = jMemoryTypeBits;
    }

    uint32_t memoryTypeIndex = -1;
    VkResult result = vmaFindMemoryTypeIndex(vmaAllocator, memoryTypeBits, &vmaAllocationCreateInfo, &memoryTypeIndex);

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
