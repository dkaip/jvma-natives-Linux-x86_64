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
 * populateVmaPoolStats.cpp
 *
 *  Created on: Sep 9, 2019
 *      Author: Douglas Kaip
 */

#include "JVmaHelperFunctions.hh"
#include "JVulkanHelperFunctions.hh"
#include "com_CIMthetics_jvma_NativeProxies.h"
#include "slf4j.hh"

extern const char *voidMethodErrorText;

namespace jvma
{
    void populateVmaPoolStats(
            JNIEnv *env,
            jobject jVmaPoolStatsObject,
            const VmaPoolStats *vmaPoolStats,
            std::vector<void *> *memoryToFree)
    {
        if (jVmaPoolStatsObject == nullptr)
        {
            LOGERROR(env, "%s", "jVmaPoolStatsObject == nullptr");
            env->ThrowNew(env->FindClass("java/lang/Exception"), "jVmaPoolStatsObject == nullptr");
            return;
        }

        if (vmaPoolStats == nullptr)
        {
            LOGERROR(env, "%s", "vmaPoolStats == nullptr");
            env->ThrowNew(env->FindClass("java/lang/Exception"), "vmaPoolStats == nullptr");
            return;
        }

        jboolean handlingException = env->ExceptionCheck();
        if (handlingException == true)
        {
            LOGWARN(env, "%s", "handlingException was already true...clearing");
            env->ExceptionClear();
        }

        jclass theClass = env->GetObjectClass(
                jVmaPoolStatsObject);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find class com/CIMthetics/jvma/Structures/VmaPoolStats");
            return;
        }

        ///////////////////////////////////////////////////////////////////////////
        jmethodID methodId = env->GetMethodID(theClass, "setSize", "(J)V");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id setSize");
            return;
        }

        env->CallVoidMethod(jVmaPoolStatsObject, methodId, vmaPoolStats->size);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", voidMethodErrorText);
            return;
        }

        ///////////////////////////////////////////////////////////////////////////
        methodId = env->GetMethodID(theClass, "setUnusedSize", "(J)V");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id setUnusedSize");
            return;
        }

        env->CallVoidMethod(jVmaPoolStatsObject, methodId, vmaPoolStats->unusedSize);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", voidMethodErrorText);
            return;
        }

        ///////////////////////////////////////////////////////////////////////////
        methodId = env->GetMethodID(theClass, "setAllocationCount", "(J)V");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id setAllocationCount");
            return;
        }

        env->CallVoidMethod(jVmaPoolStatsObject, methodId, vmaPoolStats->allocationCount);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", voidMethodErrorText);
            return;
        }

        ///////////////////////////////////////////////////////////////////////////
        methodId = env->GetMethodID(theClass, "setUnusedRangeCount", "(J)V");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id setUnusedRangeCount");
            return;
        }

        env->CallVoidMethod(jVmaPoolStatsObject, methodId, vmaPoolStats->unusedRangeCount);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", voidMethodErrorText);
            return;
        }

        ///////////////////////////////////////////////////////////////////////////
        methodId = env->GetMethodID(theClass, "setUnusedRangeSizeMax", "(J)V");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id setUnusedRangeSizeMax");
            return;
        }

        env->CallVoidMethod(jVmaPoolStatsObject, methodId, vmaPoolStats->unusedRangeSizeMax);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", voidMethodErrorText);
            return;
        }

        ///////////////////////////////////////////////////////////////////////////
        methodId = env->GetMethodID(theClass, "setBlockCount", "(J)V");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id setBlockCount");
            return;
        }

        env->CallVoidMethod(jVmaPoolStatsObject, methodId, vmaPoolStats->blockCount);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", voidMethodErrorText);
            return;
        }

    }
}
