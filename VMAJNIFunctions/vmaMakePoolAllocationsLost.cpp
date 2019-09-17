/*
 * vmaMakePoolAllocationsLost.cpp
 *
 *  Created on: Sep 9, 2019
 *      Author: Douglas Kaip
 */

#include "JVmaHelperFunctions.hh"
#include "JVulkanHelperFunctions.hh"
#include "com_CIMthetics_jvma_NativeProxies.h"
#include "slf4j.hh"

/*
 * Class:     com_CIMthetics_jvma_NativeProxies
 * Method:    vmaMakePoolAllocationsLost
 * Signature: (Lcom/CIMthetics/jvma/Handles/VmaAllocator;Lcom/CIMthetics/jvma/Handles/VmaPool;Lcom/CIMthetics/jvma/Structures/LongReturnValue;)V
 */
JNIEXPORT void JNICALL Java_com_CIMthetics_jvma_NativeProxies_vmaMakePoolAllocationsLost
  (JNIEnv *env, jobject, jobject jVmaAllocator, jobject jVmaPool, jobject jLostAllocationCountObject)
{
    struct VmaAllocator_T *vmaAllocator = (struct VmaAllocator_T *)jvulkan::getHandleValue(env, jVmaAllocator);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Could not retrieve VmaAllocator handle");
        return;
    }

    struct VmaPool_T *vmaPool = (struct VmaPool_T *)jvulkan::getHandleValue(env, jVmaPool);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Could not retrieve jVmaPool handle");
        return;
    }

    uint64_t allocationCount = 0;

    vmaMakePoolAllocationsLost(
            vmaAllocator,
            vmaPool,
            &allocationCount);

    if (jLostAllocationCountObject != nullptr)
    {
        jclass theClass = env->GetObjectClass(jLostAllocationCountObject);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling GetObjectClass");
            return;
        }

        jmethodID methodId = env->GetMethodID(theClass, "setValue", "(J)V");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id for setValue");
            return;
        }

        env->CallVoidMethod(jLostAllocationCountObject, methodId, allocationCount);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling CallVoidMethod");
            return;
        }
    }
}
