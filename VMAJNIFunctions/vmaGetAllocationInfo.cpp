/*
 * vmaGetAllocationInfo.cpp
 *
 *  Created on: Sep 17, 2019
 *      Author: Douglas Kaip
 */

#include "JVmaHelperFunctions.hh"
#include "JVulkanHelperFunctions.hh"
#include "com_CIMthetics_jvma_NativeProxies.h"
#include "slf4j.hh"

/*
 * Class:     com_CIMthetics_jvma_NativeProxies
 * Method:    vmaGetAllocationInfo
 * Signature: (Lcom/CIMthetics/jvma/Handles/VmaAllocator;Lcom/CIMthetics/jvma/Handles/VmaAllocation;Lcom/CIMthetics/jvma/Structures/VmaAllocationInfo;)V
 */
JNIEXPORT void JNICALL Java_com_CIMthetics_jvma_NativeProxies_vmaGetAllocationInfo
  (JNIEnv *env, jobject, jobject jVmaAllocator, jobject jVmaAllocation, jobject jVmaAllocationInfo)
{
    struct VmaAllocator_T *vmaAllocator = (struct VmaAllocator_T *)jvulkan::getHandleValue(env, jVmaAllocator);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Could not retrieve VmaAllocator handle");
        return;
    }

    struct VmaAllocation_T *vmaAllocation = (struct VmaAllocation_T *)jvulkan::getHandleValue(env, jVmaAllocation);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Could not retrieve VmaAllocation handle");
        return;
    }

    VmaAllocationInfo vmaAllocationInfo = {};
    vmaGetAllocationInfo(
            vmaAllocator,
            vmaAllocation,
            &vmaAllocationInfo);

    jvma::populateVmaAllocationInfo(
            env,
            jVmaAllocationInfo,
            &vmaAllocationInfo,
            nullptr);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Error calling populateVmaAllocationInfo");
    }
}
