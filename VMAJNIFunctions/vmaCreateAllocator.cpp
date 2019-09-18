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
 * vmaCreateAllocator.cpp
 *
 *  Created on: Aug 29, 2019
 *      Author: Douglas Kaip
 */


using namespace std;

#include "com_CIMthetics_jvma_NativeProxies.h"
#include "JVmaHelperFunctions.hh"
#include "JVulkanHelperFunctions.hh"
#include "slf4j.hh"

/*
 * Class:     com_CIMthetics_jvma_NativeProxies
 * Method:    vmaCreateAllocator
 * Signature: (Lcom/CIMthetics/jvma/Structures/CreateInfos/VmaAllocatorCreateInfo;Lcom/CIMthetics/jvma/Handles/VmaAllocator;)Lcom/CIMthetics/jvulkan/VulkanCore/VK11/Enums/VkResult;
 */
JNIEXPORT jobject JNICALL Java_com_CIMthetics_jvma_NativeProxies_vmaCreateAllocator
  (JNIEnv *env, jobject, jobject jVmaAllocatorCreateInfo, jobject jVmaAllocator)
{
    std::vector<void *> memoryToFree(5);
    VmaAllocatorCreateInfo vmaAllocatorCreateInfo = {};

    jvma::getVmaAllocatorCreateInfo(
            env,
            jVmaAllocatorCreateInfo,
            &vmaAllocatorCreateInfo,
            &memoryToFree);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Failed on call to getVmaAllocatorCreateInfo");
        return jvulkan::createVkResult(env, VK_RESULT_MAX_ENUM);
    }

    VmaAllocator vmaAllocator = nullptr;

    int result = vmaCreateAllocator(
            &vmaAllocatorCreateInfo,
            &vmaAllocator);
    if (result != VK_SUCCESS)
    {
        LOGERROR(env, "%s error code is %d", "Failed on call to vmaCreateAllocator", result);
    }

    jvulkan::freeMemory(&memoryToFree);

    jvulkan::setHandleValue(env, jVmaAllocator, vmaAllocator);

    return jvulkan::createVkResult(env, result);
}

