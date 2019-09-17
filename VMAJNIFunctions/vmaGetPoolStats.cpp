/*
 * vmaGetPoolStats.cpp
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
 * Method:    vmaGetPoolStats
 * Signature: (Lcom/CIMthetics/jvma/Handles/VmaAllocator;Lcom/CIMthetics/jvma/Handles/VmaPool;Lcom/CIMthetics/jvma/Structures/VmaPoolStats;)V
 */
JNIEXPORT void JNICALL Java_com_CIMthetics_jvma_NativeProxies_vmaGetPoolStats
  (JNIEnv *env, jobject, jobject jVmaAllocator, jobject jVmaPool, jobject jVmaPoolStatsObject)
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

    VmaPoolStats poolStats = {};
    vmaGetPoolStats(vmaAllocator, vmaPool, &poolStats);

    std::vector<void *> memoryToFree(5);

    jvma::populateVmaPoolStats(
            env,
            jVmaPoolStatsObject,
            &poolStats,
            &memoryToFree);

    jvulkan::freeMemory(&memoryToFree);

}
