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
 * populateVmaStats.cpp
 *
 *  Created on: Sep 2, 2019
 *      Author: Douglas Kaip
 */

#include "JVmaHelperFunctions.hh"
#include "JVulkanHelperFunctions.hh"
#include "com_CIMthetics_jvma_NativeProxies.h"
#include "slf4j.hh"

namespace jvma
{
    void populateVmaStats(
            JNIEnv *env,
            jobject jVmaStatsObject,
            const VmaStats *vmaStats,
            std::vector<void *> *memoryToFree)
    {
        if (jVmaStatsObject == nullptr)
        {
            LOGERROR(env, "%s", "jVmaStatsObject == nullptr");
            env->ThrowNew(env->FindClass("java/lang/Exception"), "jVmaStatsObject == nullptr");
            return;
        }

        if (vmaStats == nullptr)
        {
            LOGERROR(env, "%s", "vmaStats == nullptr");
            env->ThrowNew(env->FindClass("java/lang/Exception"), "vmaStats == nullptr");
            return;
        }

        jboolean handlingException = env->ExceptionCheck();
        if (handlingException == true)
        {
            LOGWARN(env, "%s", "handlingException was already true...clearing");
            env->ExceptionClear();
        }

        jclass theClass = env->GetObjectClass(
                jVmaStatsObject);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find class com/CIMthetics/jvma/Structures/VmaStats");
            return;
        }

        jclass vmaStatInfoClass = env->FindClass("com/CIMthetics/jvma/Structures/VmaStatInfo");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find class com/CIMthetics/jvma/Structures/VmaStatInfo");
            return;
        }

        jmethodID vmaStatInfoConstructor = env->GetMethodID(vmaStatInfoClass, "<init>", "()V");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find constructor method id");
            return;
        }

        jclass linkedListClass = env->FindClass("java/util/LinkedList");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find class java/util/LinkedList");
            return;
        }

        jmethodID linkedListConstructor = env->GetMethodID(linkedListClass, "<init>", "()V");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find constructor method id");
            return;
        }

        jmethodID linkedListAddMethodId = env->GetMethodID(linkedListClass, "add", "(Ljava/lang/Object;)Z");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find constructor method id");
            return;
        }

        int numberOfMemoryHeapEntries = sizeof(vmaStats->memoryHeap)/sizeof(VmaStatInfo);
        int numberOfMemoryTypeEntries = sizeof(vmaStats->memoryType)/sizeof(VmaStatInfo);

        LOGERROR(env, "Number of Heap Entries:%d", numberOfMemoryHeapEntries);
        LOGERROR(env, "Number of Type Entries:%d", numberOfMemoryTypeEntries);

        jobject linkedListObject = env->NewObject(linkedListClass, linkedListConstructor);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not create linked list");
            return;
        }

        jobject vmaStatInfoObject = nullptr;
        for(int i = 0; i < numberOfMemoryHeapEntries; i++)
        {
            vmaStatInfoObject = env->NewObject(vmaStatInfoClass, vmaStatInfoConstructor);
            if (env->ExceptionOccurred())
            {
                LOGERROR(env, "%s", "Error trying to construct vmaStatInfoObject");
                return;
            }

            populateVmaStatInfo(
                    env,
                    vmaStatInfoObject,
                    &vmaStats->memoryHeap[i],
                    memoryToFree);

            jboolean result = env->CallBooleanMethod(linkedListObject, linkedListAddMethodId, vmaStatInfoObject);
            if (env->ExceptionOccurred())
            {
                LOGERROR(env, "%s", "Error calling CallBooleanMethod");
                return;
            }

            if (result != true)
            {
                LOGERROR(env, "%s", "Error trying to add element to collection.");
            }
        }

        jmethodID methodId = env->GetMethodID(theClass, "setMemoryHeap", "(Ljava/util/Collection;)V");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id setMemoryHeap");
            return;
        }

        env->CallVoidMethod(jVmaStatsObject, methodId, linkedListObject);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling CallVoidMethod");
            return;
        }

        linkedListObject = env->NewObject(linkedListClass, linkedListConstructor);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not create linked list");
            return;
        }

        for(int i = 0; i < numberOfMemoryTypeEntries; i++)
        {
            vmaStatInfoObject = env->NewObject(vmaStatInfoClass, vmaStatInfoConstructor);
            if (env->ExceptionOccurred())
            {
                LOGERROR(env, "%s", "Error trying to construct vmaStatInfoObject");
                return;
            }

            populateVmaStatInfo(
                    env,
                    vmaStatInfoObject,
                    &vmaStats->memoryHeap[i],
                    memoryToFree);

            jboolean result = env->CallBooleanMethod(linkedListObject, linkedListAddMethodId, vmaStatInfoObject);
            if (env->ExceptionOccurred())
            {
                LOGERROR(env, "%s", "Error calling CallBooleanMethod");
                return;
            }

            if (result != true)
            {
                LOGERROR(env, "%s", "Error trying to add element to collection.");
            }
        }

        methodId = env->GetMethodID(theClass, "setMemoryType", "(Ljava/util/Collection;)V");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id setMemoryType");
            return;
        }

        env->CallVoidMethod(jVmaStatsObject, methodId, linkedListObject);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling CallVoidMethod");
            return;
        }

        vmaStatInfoObject = env->NewObject(vmaStatInfoClass, vmaStatInfoConstructor);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error trying to construct vmaStatInfoObject");
            return;
        }

        populateVmaStatInfo(
                env,
                vmaStatInfoObject,
                &vmaStats->total,
                memoryToFree);


        methodId = env->GetMethodID(theClass, "setTotal", "(Lcom/CIMthetics/jvma/Structures/VmaStatInfo;)V");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id setTotal");
            return;
        }

        env->CallVoidMethod(jVmaStatsObject, methodId, vmaStatInfoObject);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling CallVoidMethod");
            return;
        }

    }
}
