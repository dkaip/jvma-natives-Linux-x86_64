/*
 * vmaDestroyAllocator.cpp
 *
 *  Created on: Aug 30, 2019
 *      Author: Douglas Kaip
 */

#include "../headers/JVmaHelperFunctions.hh"
#include "com_CIMthetics_jvma_NativeProxies.h"
#include "slf4j.hh"


/*
 * Class:     com_CIMthetics_jvma_NativeProxies
 * Method:    vmaDestroyAllocator
 * Signature: (Lcom/CIMthetics/jvma/Handles/VmaAllocator;)V
 */
JNIEXPORT void JNICALL Java_com_CIMthetics_jvma_NativeProxies_vmaDestroyAllocator
  (JNIEnv *env, jobject, jobject jVmaAllocator)
{
    struct VmaAllocator_T *vmaAllocator = (struct VmaAllocator_T *)jvma::getHandleValue(env, jVmaAllocator);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Could not retrieve VmaAllocator handle");
        return;
    }

    vmaDestroyAllocator(vmaAllocator);
}

