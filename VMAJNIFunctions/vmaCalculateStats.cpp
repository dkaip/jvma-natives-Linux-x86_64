/*
 * vmaCalculateStats.cpp
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
 * Method:    vmaCalculateStats
 * Signature: (Lcom/CIMthetics/jvma/Handles/VmaAllocator;Lcom/CIMthetics/jvma/Structures/VmaStats;)V
 */
JNIEXPORT void JNICALL Java_com_CIMthetics_jvma_NativeProxies_vmaCalculateStats
  (JNIEnv *env, jobject, jobject jVmaAllocator, jobject jVmaStatsObject)
{
    struct VmaAllocator_T *vmaAllocator = (struct VmaAllocator_T *)jvulkan::getHandleValue(env, jVmaAllocator);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Could not retrieve VmaAllocator handle");
        return;
    }

    std::vector<void *> memoryToFree(5);
    VmaStats stats = {};
    vmaCalculateStats(vmaAllocator, &stats);

    jvma::populateVmaStats(
            env,
            jVmaStatsObject,
            &stats,
            &memoryToFree);

    jvulkan::freeMemory(&memoryToFree);
}
