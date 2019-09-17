/*
 * vmaDestroyPool.cpp
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
 * Method:    vmaDestroyPool
 * Signature: (Lcom/CIMthetics/jvma/Handles/VmaAllocator;Lcom/CIMthetics/jvma/Handles/VmaPool;)V
 */
JNIEXPORT void JNICALL Java_com_CIMthetics_jvma_NativeProxies_vmaDestroyPool
  (JNIEnv *env, jobject, jobject jVmaAllocator, jobject jVmaPool)
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

    vmaDestroyPool(vmaAllocator, vmaPool);
}
