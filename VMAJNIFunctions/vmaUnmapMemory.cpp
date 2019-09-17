/*
 * vmaUnmapMemory.cpp
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
 * Method:    vmaUnmapMemory
 * Signature: (Lcom/CIMthetics/jvma/Handles/VmaAllocator;Lcom/CIMthetics/jvma/Handles/VmaAllocation;)V
 */
JNIEXPORT void JNICALL Java_com_CIMthetics_jvma_NativeProxies_vmaUnmapMemory
  (JNIEnv *env, jobject, jobject jVmaAllocator, jobject jVmaAllocation)
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

    vmaUnmapMemory(vmaAllocator, vmaAllocation);
}
