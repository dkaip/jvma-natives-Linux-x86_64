/*
 * populateVmaDefragmentationStats.cpp
 *
 *  Created on: Sep 17, 2019
 *      Author: Douglas Kaip
 */

#include "JVmaHelperFunctions.hh"
#include "JVulkanHelperFunctions.hh"
#include "com_CIMthetics_jvma_NativeProxies.h"
#include "slf4j.hh"

extern const char *voidMethodErrorText;

namespace jvma
{
    void populateVmaDefragmentationStats(
            JNIEnv *env,
            jobject jVmaDefragmentationStatsObject,
            const VmaDefragmentationStats *vmaDefragmentationStats,
            std::vector<void *> *memoryToFree)
    {
        if (jVmaDefragmentationStatsObject == nullptr)
        {
            LOGERROR(env, "%s", "jVmaDefragmentationStatsObject == nullptr");
            env->ThrowNew(env->FindClass("java/lang/Exception"), "jVmaDefragmentationStatsObject == nullptr");
            return;
        }

        if (vmaDefragmentationStats == nullptr)
        {
            LOGERROR(env, "%s", "vmaDefragmentationStats == nullptr");
            env->ThrowNew(env->FindClass("java/lang/Exception"), "vmaDefragmentationStats == nullptr");
            return;
        }

        jboolean handlingException = env->ExceptionCheck();
        if (handlingException == true)
        {
            LOGWARN(env, "%s", "handlingException was already true...clearing");
            env->ExceptionClear();
        }

        jclass theClass = env->GetObjectClass(jVmaDefragmentationStatsObject);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find class com/CIMthetics/jvma/Structures/VmaDefragmentationStats");
            return;
        }

        ///////////////////////////////////////////////////////////////////////////
        jmethodID methodId = env->GetMethodID(theClass, "setBytesMoved", "(J)V");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id setBytesMoved");
            return;
        }

        env->CallVoidMethod(jVmaDefragmentationStatsObject, methodId, vmaDefragmentationStats->bytesMoved);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", voidMethodErrorText);
            return;
        }

        ///////////////////////////////////////////////////////////////////////////
        methodId = env->GetMethodID(theClass, "setBytesFreed", "(J)V");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id setBytesFreed");
            return;
        }

        env->CallVoidMethod(jVmaDefragmentationStatsObject, methodId, vmaDefragmentationStats->bytesFreed);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", voidMethodErrorText);
            return;
        }

        ///////////////////////////////////////////////////////////////////////////
        methodId = env->GetMethodID(theClass, "setAllocationsMoved", "(I)V");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id setAllocationsMoved");
            return;
        }

        env->CallVoidMethod(jVmaDefragmentationStatsObject, methodId, vmaDefragmentationStats->allocationsMoved);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", voidMethodErrorText);
            return;
        }

        ///////////////////////////////////////////////////////////////////////////
        methodId = env->GetMethodID(theClass, "setDeviceMemoryBlocksFreed", "(I)V");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id setDeviceMemoryBlocksFreed");
            return;
        }

        env->CallVoidMethod(jVmaDefragmentationStatsObject, methodId, vmaDefragmentationStats->deviceMemoryBlocksFreed);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", voidMethodErrorText);
            return;
        }

    }
}
