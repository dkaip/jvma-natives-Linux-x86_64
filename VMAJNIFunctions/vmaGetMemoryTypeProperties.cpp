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
 * vmaGetMemoryTypeProperties.cpp
 *
 *  Created on: Sep 2, 2019
 *      Author: Douglas Kaip
 */

#include "JVmaHelperFunctions.hh"
#include "JVulkanHelperFunctions.hh"
#include "com_CIMthetics_jvma_NativeProxies.h"
#include "slf4j.hh"

/*
 * Class:     com_CIMthetics_jvma_NativeProxies
 * Method:    vmaGetMemoryTypeProperties
 * Signature: (Lcom/CIMthetics/jvma/Handles/VmaAllocator;ILjava/util/EnumSet;)V
 */
JNIEXPORT void JNICALL Java_com_CIMthetics_jvma_NativeProxies_vmaGetMemoryTypeProperties
  (JNIEnv *env, jobject, jobject jVmaAllocator, jint memoryTypeIndex, jobject jVkMemoryPropertyFlags)
{
    struct VmaAllocator_T *vmaAllocator = (struct VmaAllocator_T *)jvulkan::getHandleValue(env, jVmaAllocator);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Could not retrieve VmaAllocator handle.");
        return;
    }

    if (jVkMemoryPropertyFlags == nullptr)
    {
        LOGERROR(env, "%s", "jVkMemoryPropertyFlags must nor be nullptr.");
        return;
    }

    unsigned int flags = 0;
    vmaGetMemoryTypeProperties(vmaAllocator, memoryTypeIndex, &flags);

    jclass enumSetClass = env->GetObjectClass(jVkMemoryPropertyFlags);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Could not get class for jVkMemoryPropertyFlags.");
        return;
    }

    char const *enumClassString = "com/CIMthetics/jvulkan/VulkanCore/VK11/Enums/VkMemoryPropertyFlagBits";
    char const *enumObjectString = "Lcom/CIMthetics/jvulkan/VulkanCore/VK11/Enums/VkMemoryPropertyFlagBits;";

    jclass enumClass = env->FindClass(enumClassString);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s %s", "Could not get class for", enumClassString);
        return;
    }

    jclass setClass = env->FindClass("java/util/Set");
    jmethodID setAddMethod = env->GetMethodID(setClass, "add", "(Ljava/lang/Object;)Z");
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Could not find method id for add.");
        return;
    }

    /*
     * Make sure that flags does not have an unexpected value.  This would
     * indicate that this code is out of sync with the LunarG Vulkan SDK.
     */
    if ((flags &
         !(VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT |
           VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
           VK_MEMORY_PROPERTY_HOST_COHERENT_BIT |
           VK_MEMORY_PROPERTY_HOST_CACHED_BIT |
           VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT |
           VK_MEMORY_PROPERTY_PROTECTED_BIT)) != 0)
    {
        LOGERROR(env, "%s %d", "ERROR: Unhandled case for memoryPropertyFlags...value is", flags);
        return;
    }

    if (flags & VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
    {
        jfieldID fieldId = env->GetStaticFieldID(enumClass, "VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT", enumObjectString);
        jobject theEnum = env->GetStaticObjectField(enumClass, fieldId);

        bool addResult = env->CallBooleanMethod(jVkMemoryPropertyFlags, setAddMethod, theEnum);
        if (addResult == false)
        {
            LOGERROR(env, "%s", "ERROR: could not add VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT to EnumSet");
            return;
        }
    }

    if (flags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)
    {
        jfieldID fieldId = env->GetStaticFieldID(enumClass, "VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT", enumObjectString);
        jobject theEnum = env->GetStaticObjectField(enumClass, fieldId);

        bool addResult = env->CallBooleanMethod(jVkMemoryPropertyFlags, setAddMethod, theEnum);
        if (addResult == false)
        {
            LOGERROR(env, "%s", "ERROR: could not add VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT to EnumSet");
            return;
        }
    }

    if (flags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
    {
        jfieldID fieldId = env->GetStaticFieldID(enumClass, "VK_MEMORY_PROPERTY_HOST_COHERENT_BIT", enumObjectString);
        jobject theEnum = env->GetStaticObjectField(enumClass, fieldId);

        bool addResult = env->CallBooleanMethod(jVkMemoryPropertyFlags, setAddMethod, theEnum);
        if (addResult == false)
        {
            LOGERROR(env, "%s", "ERROR: could not add VK_MEMORY_PROPERTY_HOST_COHERENT_BIT to EnumSet");
            return;
        }
    }

    if (flags & VK_MEMORY_PROPERTY_HOST_CACHED_BIT)
    {
        jfieldID fieldId = env->GetStaticFieldID(enumClass, "VK_MEMORY_PROPERTY_HOST_CACHED_BIT", enumObjectString);
        jobject theEnum = env->GetStaticObjectField(enumClass, fieldId);

        bool addResult = env->CallBooleanMethod(jVkMemoryPropertyFlags, setAddMethod, theEnum);
        if (addResult == false)
        {
            LOGERROR(env, "%s", "ERROR: could not add VK_MEMORY_PROPERTY_HOST_CACHED_BIT to EnumSet");
            return;
        }
    }

    if (flags & VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT)
    {
        jfieldID fieldId = env->GetStaticFieldID(enumClass, "VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT", enumObjectString);
        jobject theEnum = env->GetStaticObjectField(enumClass, fieldId);

        bool addResult = env->CallBooleanMethod(jVkMemoryPropertyFlags, setAddMethod, theEnum);
        if (addResult == false)
        {
            LOGERROR(env, "%s", "ERROR: could not add VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT to EnumSet");
            return;
        }
    }

    if (flags & VK_MEMORY_PROPERTY_PROTECTED_BIT)
    {
        jfieldID fieldId = env->GetStaticFieldID(enumClass, "VK_MEMORY_PROPERTY_PROTECTED_BIT", enumObjectString);
        jobject theEnum = env->GetStaticObjectField(enumClass, fieldId);

        bool addResult = env->CallBooleanMethod(jVkMemoryPropertyFlags, setAddMethod, theEnum);
        if (addResult == false)
        {
            LOGERROR(env, "%s", "ERROR: could not add VK_MEMORY_PROPERTY_PROTECTED_BIT to EnumSet");
            return;
        }
    }
}
