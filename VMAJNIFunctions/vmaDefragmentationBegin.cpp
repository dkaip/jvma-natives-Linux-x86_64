/*
 * vmaDefragmentationBegin.cpp
 *
 *  Created on: Sep 17, 2019
 *      Author: Douglas Kaip
 */

#include "JVmaHelperFunctions.hh"
#include "JVulkanHelperFunctions.hh"
#include "com_CIMthetics_jvma_NativeProxies.h"
#include "slf4j.hh"

static void updateAllocationsChanged(
        JNIEnv *env,
        jobject jVmaDefragmentationInfo2,
        VmaDefragmentationInfo2 *vmaDefragmentationInfo2);

/*
 * Class:     com_CIMthetics_jvma_NativeProxies
 * Method:    vmaDefragmentationBegin
 * Signature: (Lcom/CIMthetics/jvma/Handles/VmaAllocator;Lcom/CIMthetics/jvma/Structures/VmaDefragmentationInfo2;Lcom/CIMthetics/jvma/Structures/VmaDefragmentationStats;Lcom/CIMthetics/jvma/Handles/VmaDefragmentationContext;)Lcom/CIMthetics/jvulkan/VulkanCore/VK11/Enums/VkResult;
 */
JNIEXPORT jobject JNICALL Java_com_CIMthetics_jvma_NativeProxies_vmaDefragmentationBegin
  (JNIEnv *env, jobject, jobject jVmaAllocator, jobject jVmaDefragmentationInfo2, jobject jVmaDefragmentationStats, jobject jVmaDefragmentationContext)
{
    struct VmaAllocator_T *vmaAllocator = (struct VmaAllocator_T *)jvulkan::getHandleValue(env, jVmaAllocator);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Could not retrieve VmaAllocator handle");
        return jvulkan::createVkResult(env, VK_RESULT_MAX_ENUM);
    }

    std::vector<void *> memoryToFree(5);
    VmaDefragmentationInfo2 vmaDefragmentationInfo2 = {};
    jvma::getVmaDefragmentationInfo2(
            env,
            jVmaDefragmentationInfo2,
            &vmaDefragmentationInfo2,
            &memoryToFree);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Error calling getVmaDefragmentationInfo2");
        return jvulkan::createVkResult(env, VK_RESULT_MAX_ENUM);
    }


    VmaDefragmentationContext vmaDefragmentationContext = nullptr;
    VmaDefragmentationStats vmaDefragmentationStats = {};
    VkResult result = (VkResult)-1;

    if (jVmaDefragmentationStats == nullptr)
    {
        result = vmaDefragmentationBegin(
                vmaAllocator,
                &vmaDefragmentationInfo2,
                nullptr,
                &vmaDefragmentationContext);

        if (vmaDefragmentationInfo2.pAllocationsChanged != nullptr)
        {
            /*
             * They want the allocations changed data returned.
             */
            updateAllocationsChanged(
                    env,
                    jVmaDefragmentationInfo2,
                    &vmaDefragmentationInfo2);
            if (env->ExceptionOccurred())
            {
                LOGERROR(env, "%s", "Error calling updateAllocationsChanged");
                return jvulkan::createVkResult(env, VK_RESULT_MAX_ENUM);
            }
        }
    }
    else
    {
        result = vmaDefragmentationBegin(
                vmaAllocator,
                &vmaDefragmentationInfo2,
                &vmaDefragmentationStats,
                &vmaDefragmentationContext);

        jvma::populateVmaDefragmentationStats(
                env,
                jVmaDefragmentationStats,
                &vmaDefragmentationStats,
                &memoryToFree);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling populateVmaDefragmentationStats");
        }

        if (vmaDefragmentationInfo2.pAllocationsChanged != nullptr)
        {
            /*
             * They want the allocations changed data returned.
             */
            updateAllocationsChanged(
                    env,
                    jVmaDefragmentationInfo2,
                    &vmaDefragmentationInfo2);
            if (env->ExceptionOccurred())
            {
                LOGERROR(env, "%s", "Error calling updateAllocationsChanged");
                return jvulkan::createVkResult(env, VK_RESULT_MAX_ENUM);
            }
        }
    }

    jvulkan::freeMemory(&memoryToFree);

    jvulkan::setHandleValue(env, jVmaDefragmentationContext, vmaDefragmentationContext);

    return jvulkan::createVkResult(env, result);
}

static void updateAllocationsChanged(
        JNIEnv *env,
        jobject jVmaDefragmentationInfo2,
        VmaDefragmentationInfo2 *vmaDefragmentationInfo2)
{
    jbooleanArray jReturnData = env->NewBooleanArray(vmaDefragmentationInfo2->allocationCount);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Error calling NewBooleanArray");
        return;
    }

    /*
     * We are copying to an intermediate form because the
     * allocationsChanged data is a VKBool32 array and I don't think
     * the SetBooleanArrayRegion will handle that correctly.
     */
    bool dataToReturn[vmaDefragmentationInfo2->allocationCount];
    for(int i = 0; i < vmaDefragmentationInfo2->allocationCount; i++)
    {
        if (vmaDefragmentationInfo2->pAllocationsChanged[i] != 0)
        {
            dataToReturn[i] = true;
        }
        else
        {
            dataToReturn[i] = false;
        }
    }

    env->SetBooleanArrayRegion(jReturnData, 0, vmaDefragmentationInfo2->allocationCount, (unsigned char *)dataToReturn);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Error calling SetBooleanArrayRegion");
        return;
    }

    jclass theClass = env->GetObjectClass(jVmaDefragmentationInfo2);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Could not find class for jVmaDefragmentationInfo2");
        return;
    }

    jmethodID methodId = env->GetMethodID(theClass, "setAllocationsChanged", "([Z)V");
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Could not get method id for setAllocationsChanged");
        return;
    }

    env->CallVoidMethod(jVmaDefragmentationInfo2, methodId, jReturnData);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Error calling CallVoidMethod");
        return;
    }
}
