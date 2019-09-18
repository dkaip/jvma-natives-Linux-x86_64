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
 * vmaAllocateMemoryPages.cpp
 *
 *  Created on: Sep 16, 2019
 *      Author: Douglas Kaip
 */

#include "JVmaHelperFunctions.hh"
#include "JVulkanHelperFunctions.hh"
#include "com_CIMthetics_jvma_NativeProxies.h"
#include "slf4j.hh"

static void fillHandleCollection(
        JNIEnv *env,
        VmaAllocation *vmaAllocations,
        int numberOfMemoryRequirements,
        jobject jVmaAllocationCollection);

static void fillAllocationInfos(
        JNIEnv *env,
        VmaAllocationInfo *vmaAllocationInfos,
        int numberOfElements,
        jobject jVmaAllocationInfoCollection);

/*
 * Class:     com_CIMthetics_jvma_NativeProxies
 * Method:    vmaAllocateMemoryPages
 * Signature: (Lcom/CIMthetics/jvma/Handles/VmaAllocator;Ljava/util/Collection;Ljava/util/Collection;Ljava/util/Collection;Ljava/util/Collection;)Lcom/CIMthetics/jvulkan/VulkanCore/VK11/Enums/VkResult;
 */
JNIEXPORT jobject JNICALL Java_com_CIMthetics_jvma_NativeProxies_vmaAllocateMemoryPages
(JNIEnv *env, jobject, jobject jVmaAllocator, jobject jVkMemoryRequirementsCollection, jobject jVmaAllocationCreateInfoCollection, jobject jVmaAllocationCollection, jobject jVmaAllocationInfoCollection)
{
    struct VmaAllocator_T *vmaAllocator = (struct VmaAllocator_T *)jvulkan::getHandleValue(env, jVmaAllocator);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Could not retrieve VmaAllocator handle");
        return jvulkan::createVkResult(env, VK_RESULT_MAX_ENUM);
    }

    if (jVmaAllocationCollection == nullptr)
    {
        LOGERROR(env, "%s", "jVmaAllocationCollection may not be null");
        return jvulkan::createVkResult(env, VK_RESULT_MAX_ENUM);
    }

    std::vector<void *> memoryToFree(5);
    int numberOfMemoryRequirements = 0;
    VkMemoryRequirements *vkMemoryRequirements = nullptr;
    jvulkan::getVkMemoryRequirementsCollection(
            env,
            jVkMemoryRequirementsCollection,
            &vkMemoryRequirements,
            &numberOfMemoryRequirements,
            &memoryToFree);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Error calling getVkMemoryRequirementsCollection");
        return jvulkan::createVkResult(env, VK_RESULT_MAX_ENUM);
    }

    int numberOfVmaAllocationCreateInfos = 0;
    VmaAllocationCreateInfo *vmaAllocationCreateInfos = nullptr;
    jvma::getVmaAllocationCreateInfoCollection(
            env,
            jVmaAllocationCreateInfoCollection,
            &vmaAllocationCreateInfos,
            &numberOfVmaAllocationCreateInfos,
            &memoryToFree);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Error calling getVmaAllocationCreateInfoCollection");
        return jvulkan::createVkResult(env, VK_RESULT_MAX_ENUM);
    }

    if (numberOfMemoryRequirements != numberOfVmaAllocationCreateInfos)
    {
        LOGERROR(env, "%s", "There must be the same number of VmaAllocationCreateInfos as VkMemoryRequirements passed into this function.");
        return jvulkan::createVkResult(env, VK_RESULT_MAX_ENUM);
    }

    VmaAllocation *vmaAllocations = (VmaAllocation *)calloc(numberOfMemoryRequirements, sizeof(VmaAllocation));
    VkResult result = (VkResult)-1;

    if (jVmaAllocationInfoCollection == nullptr)
    {
        result = vmaAllocateMemoryPages(
                vmaAllocator,
                vkMemoryRequirements,
                vmaAllocationCreateInfos,
                (uint64_t)numberOfMemoryRequirements,
                vmaAllocations,
                nullptr);

        if (result == VK_SUCCESS)
        {
            fillHandleCollection(
                    env,
                    vmaAllocations,
                    numberOfMemoryRequirements,
                    jVmaAllocationCollection);
            if (env->ExceptionOccurred())
            {
                LOGERROR(env, "%s", "Error calling fillHandleCollection");
            }
        }
    }
    else
    {
        VmaAllocationInfo *vmaAllocationInfos = (VmaAllocationInfo *)calloc(numberOfMemoryRequirements, sizeof(VmaAllocationInfo));

        result = vmaAllocateMemoryPages(
                vmaAllocator,
                vkMemoryRequirements,
                vmaAllocationCreateInfos,
                (uint64_t)numberOfMemoryRequirements,
                vmaAllocations,
                vmaAllocationInfos);

        if (result == VK_SUCCESS)
        {
            fillHandleCollection(
                    env,
                    vmaAllocations,
                    numberOfMemoryRequirements,
                    jVmaAllocationCollection);
            if (env->ExceptionOccurred())
            {
                LOGERROR(env, "%s", "Error calling fillHandleCollection");
            }

            fillAllocationInfos(
                    env,
                    vmaAllocationInfos,
                    numberOfMemoryRequirements,
                    jVmaAllocationInfoCollection);
            if (env->ExceptionOccurred())
            {
                LOGERROR(env, "%s", "Error calling fillAllocationInfos");
            }
        }

        if (vmaAllocationInfos != nullptr)
        {
            free(vmaAllocationInfos);
            vmaAllocationInfos = nullptr;
        }
    }

    jvulkan::freeMemory(&memoryToFree);

    if (vmaAllocations != nullptr)
    {
        free(vmaAllocations);
        vmaAllocations = nullptr;
    }

    return jvulkan::createVkResult(env, result);
}

static void fillAllocationInfos(
        JNIEnv *env,
        VmaAllocationInfo *vmaAllocationInfos,
        int numberOfElements,
        jobject jVmaAllocationInfoCollection)
{
    jclass theClass = env->FindClass("java/util/Collection");
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Could not find class java/util/Collection");
        return;
    }

    jmethodID addMethodId = env->GetMethodID(theClass, "add", "(Ljava/lang/Object;)Z");
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Could not find method id for add");
        return;
    }

    jclass theObjectClass = env->FindClass("com/CIMthetics/jvma/Structures/VmaAllocationInfo");
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Could not find class com/CIMthetics/jvma/Structures/VmaAllocationInfo");
        return;
    }

    jmethodID constructorMethodId = env->GetMethodID(theObjectClass, "<init>", "()V");
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Could not find method id for add");
        return;
    }

    for(int i = 0; i < numberOfElements; i++)
    {
        jobject vmaAllocationInfoObject = env->NewObject(theObjectClass, constructorMethodId);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not construct vmaAllocationInfoObject");
            return;
        }

        jvma::populateVmaAllocationInfo(
                env,
                vmaAllocationInfoObject,
                &vmaAllocationInfos[i],
                nullptr);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling populateVmaAllocationInfo");
        }

        jboolean result = env->CallBooleanMethod(jVmaAllocationInfoCollection, addMethodId, vmaAllocationInfoObject);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling CallBooleanMethod");
            return;
        }

        if (result != true)
        {
            LOGERROR(env, "%s", "Error adding VmaAllocationInfo to collection");
        }
    }
}

static void fillHandleCollection(
        JNIEnv *env,
        VmaAllocation *vmaAllocations,
        int numberOfElements,
        jobject jVmaAllocationCollection)
{
    jclass theClass = env->FindClass("java/util/Collection");
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Could not find class java/util/Collection");
        return;
    }

    jmethodID addMethodId = env->GetMethodID(theClass, "add", "(Ljava/lang/Object;)Z");
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Could not find method id for add");
        return;
    }

    for(int i = 0; i < numberOfElements; i++)
    {
        jobject handle = jvulkan::createVulkanHandle(env, "com/CIMthetics/jvma/Handles/VmaAllocation", vmaAllocations[i]);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling createVulkanHandle");
            return;
        }

        jboolean result = env->CallBooleanMethod(jVmaAllocationCollection, addMethodId, handle);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling CallBooleanMethod");
            return;
        }

        if (result != true)
        {
            LOGERROR(env, "%s", "Error adding handle to collection");
        }
    }
}

