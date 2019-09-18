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
 * populateVmaStatInfo.cpp
 *
 *  Created on: Sep 2, 2019
 *      Author: Douglas Kaip
 */

#include "JVmaHelperFunctions.hh"
#include "JVulkanHelperFunctions.hh"
#include "com_CIMthetics_jvma_NativeProxies.h"
#include "slf4j.hh"

extern const char *voidMethodErrorText;

namespace jvma
{
    void populateVmaStatInfo(
            JNIEnv *env,
            jobject jVmaStatInfoObject,
            const VmaStatInfo *vmaStatInfo,
            std::vector<void *> *memoryToFree)
    {
        if (jVmaStatInfoObject == nullptr)
        {
            LOGERROR(env, "%s", "jVmaStatInfoObject == nullptr");
            env->ThrowNew(env->FindClass("java/lang/Exception"), "jVmaStatInfoObject == nullptr");
            return;
        }

        if (vmaStatInfo == nullptr)
        {
            LOGERROR(env, "%s", "vmaStatInfo == nullptr");
            env->ThrowNew(env->FindClass("java/lang/Exception"), "vmaStatInfo == nullptr");
            return;
        }

        jboolean handlingException = env->ExceptionCheck();
        if (handlingException == true)
        {
            LOGWARN(env, "%s", "handlingException was already true...clearing");
            env->ExceptionClear();
        }

        jclass theClass = env->GetObjectClass(jVmaStatInfoObject);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find class com/CIMthetics/jvma/Structures/VmaStatInfo");
            return;
        }

        ///////////////////////////////////////////////////////////////////////////
        jmethodID methodId = env->GetMethodID(theClass, "setBlockCount", "(I)V");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id setBlockCount");
            return;
        }

        env->CallVoidMethod(jVmaStatInfoObject, methodId, vmaStatInfo->blockCount);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", voidMethodErrorText);
            return;
        }

        ///////////////////////////////////////////////////////////////////////////
        methodId = env->GetMethodID(theClass, "setAllocationCount", "(I)V");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id setAllocationCount");
            return;
        }

        env->CallVoidMethod(jVmaStatInfoObject, methodId, vmaStatInfo->allocationCount);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", voidMethodErrorText);
            return;
        }

        ///////////////////////////////////////////////////////////////////////////
        methodId = env->GetMethodID(theClass, "setUnusedRangeCount", "(I)V");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id setUnusedRangeCount");
            return;
        }

        env->CallVoidMethod(jVmaStatInfoObject, methodId, vmaStatInfo->unusedRangeCount);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", voidMethodErrorText);
            return;
        }

        ///////////////////////////////////////////////////////////////////////////
        methodId = env->GetMethodID(theClass, "setUsedBytes", "(J)V");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id setUsedBytes");
            return;
        }

        env->CallVoidMethod(jVmaStatInfoObject, methodId, vmaStatInfo->usedBytes);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", voidMethodErrorText);
            return;
        }

        ///////////////////////////////////////////////////////////////////////////
        methodId = env->GetMethodID(theClass, "setUnusedBytes", "(J)V");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id setUnusedBytes");
            return;
        }

        env->CallVoidMethod(jVmaStatInfoObject, methodId, vmaStatInfo->unusedBytes);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", voidMethodErrorText);
            return;
        }

        ///////////////////////////////////////////////////////////////////////////
        methodId = env->GetMethodID(theClass, "setAllocationSizeMin", "(J)V");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id setAllocationSizeMin");
            return;
        }

        env->CallVoidMethod(jVmaStatInfoObject, methodId, vmaStatInfo->allocationSizeMin);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", voidMethodErrorText);
            return;
        }

        ///////////////////////////////////////////////////////////////////////////
        methodId = env->GetMethodID(theClass, "setAllocationSizeAvg", "(J)V");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id setAllocationSizeAvg");
            return;
        }

        env->CallVoidMethod(jVmaStatInfoObject, methodId, vmaStatInfo->allocationSizeAvg);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", voidMethodErrorText);
            return;
        }

        ///////////////////////////////////////////////////////////////////////////
        methodId = env->GetMethodID(theClass, "setAllocationSizeMax", "(J)V");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id setAllocationSizeMax");
            return;
        }

        env->CallVoidMethod(jVmaStatInfoObject, methodId, vmaStatInfo->allocationSizeMax);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", voidMethodErrorText);
            return;
        }

        ///////////////////////////////////////////////////////////////////////////
        methodId = env->GetMethodID(theClass, "setUnusedRangeSizeMin", "(J)V");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id setUnusedRangeSizeMin");
            return;
        }

        env->CallVoidMethod(jVmaStatInfoObject, methodId, vmaStatInfo->unusedRangeSizeMin);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", voidMethodErrorText);
            return;
        }

        ///////////////////////////////////////////////////////////////////////////
        methodId = env->GetMethodID(theClass, "setUnusedRangeSizeAvg", "(J)V");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id setUnusedRangeSizeAvg");
            return;
        }

        env->CallVoidMethod(jVmaStatInfoObject, methodId, vmaStatInfo->unusedRangeSizeAvg);
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

        env->CallVoidMethod(jVmaStatInfoObject, methodId, vmaStatInfo->unusedRangeSizeMax);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", voidMethodErrorText);
            return;
        }

//        LOGERROR(env, "blockCount:%u", vmaStatInfo->blockCount);
//        LOGERROR(env, "allocationCount:%u", vmaStatInfo->allocationCount);
//        LOGERROR(env, "unusedRangeCount:%u", vmaStatInfo->unusedRangeCount);
//        LOGERROR(env, "usedBytes:%lu", vmaStatInfo->usedBytes);
//        LOGERROR(env, "unusedBytes:%lu", vmaStatInfo->unusedBytes);
//        LOGERROR(env, "allocationSizeMin:%lu", vmaStatInfo->allocationSizeMin);
//        LOGERROR(env, "allocationSizeAvg:%lu", vmaStatInfo->allocationSizeAvg);
//        LOGERROR(env, "allocationSizeMax:%lu", vmaStatInfo->allocationSizeMax);
//        LOGERROR(env, "unusedRangeSizeMin:%lu", vmaStatInfo->unusedRangeSizeMin);
//        LOGERROR(env, "unusedRangeSizeAvg:%lu", vmaStatInfo->unusedRangeSizeAvg);
//        LOGERROR(env, "unusedRangeSizeMax:%lu", vmaStatInfo->unusedRangeSizeMax);
    }
}



