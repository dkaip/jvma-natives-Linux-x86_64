/*
 * getVmaPoolCreateInfo.cpp
 *
 *  Created on: Sep 9, 2019
 *      Author: Douglas Kaip
 */

#include "JVmaHelperFunctions.hh"
#include "JVulkanHelperFunctions.hh"
#include "slf4j.hh"

namespace jvma
{
    void getVmaPoolCreateInfo(
            JNIEnv *env,
            jobject jVmaPoolCreateInfoObject,
            VmaPoolCreateInfo *vmaPoolCreateInfo,
            std::vector<void *> *memoryToFree)
    {
        jclass theClass = env->GetObjectClass(jVmaPoolCreateInfoObject);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error trying to get class for jVmaPoolCreateInfoObject");
            return;
        }

        ////////////////////////////////////////////////////////////////////////
        jmethodID methodId = env->GetMethodID(theClass, "getMemoryTypeIndex", "()I");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id for getMemoryTypeIndex");
            return;
        }

        jint memoryTypeIndex = env->CallIntMethod(jVmaPoolCreateInfoObject, methodId);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling CallIntMethod");
            return;
        }

        ////////////////////////////////////////////////////////////////////////
        methodId = env->GetMethodID(theClass, "getFlags", "()Ljava/util/EnumSet;");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id for getFlags");
            return;
        }

        jobject flagsObject = env->CallObjectMethod(jVmaPoolCreateInfoObject, methodId);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling CallObjectMethod");
            return;
        }

        VmaPoolCreateFlags flags = jvulkan::getEnumSetValue(
                env,
                flagsObject,
                "com/CIMthetics/jvma/Enums/VmaPoolCreateFlagBits");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling getEnumSetValue");
            return;
        }

        ////////////////////////////////////////////////////////////////////////
        methodId = env->GetMethodID(theClass, "getBlockSize", "()J");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id for getBlockSize");
            return;
        }

        jlong blockSize = env->CallLongMethod(jVmaPoolCreateInfoObject, methodId);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling CallLongMethod");
            return;
        }

        ////////////////////////////////////////////////////////////////////////
        methodId = env->GetMethodID(theClass, "getMinBlockCount", "()J");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id for getMinBlockCount");
            return;
        }

        jlong minBlockCount = env->CallLongMethod(jVmaPoolCreateInfoObject, methodId);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling CallLongMethod");
            return;
        }

        ////////////////////////////////////////////////////////////////////////
        methodId = env->GetMethodID(theClass, "getMaxBlockCount", "()J");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id for getMaxBlockCount");
            return;
        }

        jlong maxBlockCount = env->CallLongMethod(jVmaPoolCreateInfoObject, methodId);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling CallLongMethod");
            return;
        }

        ////////////////////////////////////////////////////////////////////////
        methodId = env->GetMethodID(theClass, "getFrameInUseCount", "()I");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id for getFrameInUseCount");
            return;
        }

        jint frameInUseCount = env->CallIntMethod(jVmaPoolCreateInfoObject, methodId);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling CallIntMethod");
            return;
        }


        vmaPoolCreateInfo->memoryTypeIndex = memoryTypeIndex;
        vmaPoolCreateInfo->flags = flags;
        vmaPoolCreateInfo->blockSize = blockSize;
        vmaPoolCreateInfo->minBlockCount = minBlockCount;
        vmaPoolCreateInfo->maxBlockCount = maxBlockCount;
        vmaPoolCreateInfo->frameInUseCount = frameInUseCount;
    }
}
