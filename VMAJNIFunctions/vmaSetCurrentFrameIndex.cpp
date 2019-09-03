/*
 * vmaSetCurrentFrameIndex.cpp
 *
 *  Created on: Sep 2, 2019
 *      Author: Douglas Kaip
 */

#include "JVmaHelperFunctions.hh"
#include "JVulkanHelperFunctions.hh"
#include "com_CIMthetics_jvma_NativeProxies.h"
#include "slf4j.hh"

/*
 * Class:     com_CIMthetics_jvma_NativeProxies
 * Method:    vmaSetCurrentFrameIndex
 * Signature: (Lcom/CIMthetics/jvma/Handles/VmaAllocator;I)V
 */
JNIEXPORT void JNICALL Java_com_CIMthetics_jvma_NativeProxies_vmaSetCurrentFrameIndex
  (JNIEnv *env, jobject, jobject jVmaAllocator, jint frameIndex)
{
    struct VmaAllocator_T *vmaAllocator = (struct VmaAllocator_T *)jvulkan::getHandleValue(env, jVmaAllocator);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Could not retrieve VmaAllocator handle");
        return;
    }

    vmaSetCurrentFrameIndex(vmaAllocator, frameIndex);
}
