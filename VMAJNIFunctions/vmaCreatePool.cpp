/*
 * vmaCreatePool.cpp
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
 * Method:    vmaCreatePool
 * Signature: (Lcom/CIMthetics/jvma/Handles/VmaAllocator;Lcom/CIMthetics/jvma/Structures/CreateInfos/VmaPoolCreateInfo;Lcom/CIMthetics/jvma/Handles/VmaPool;)Lcom/CIMthetics/jvulkan/VulkanCore/VK11/Enums/VkResult;
 */
JNIEXPORT jobject JNICALL Java_com_CIMthetics_jvma_NativeProxies_vmaCreatePool
  (JNIEnv *env, jobject, jobject jVmaAllocator, jobject jVmaPoolCreateInfo, jobject jVmaPool)
{
    struct VmaAllocator_T *vmaAllocator = (struct VmaAllocator_T *)jvulkan::getHandleValue(env, jVmaAllocator);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Could not retrieve VmaAllocator handle");
        return jvulkan::createVkResult(env, VK_RESULT_MAX_ENUM);
    }

    std::vector<void *> memoryToFree(5);
    VmaPoolCreateInfo vmaPoolCreateInfo = {};

    jvma::getVmaPoolCreateInfo(
            env,
            jVmaPoolCreateInfo,
            &vmaPoolCreateInfo,
            &memoryToFree);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Failed on call to getVmaPoolCreateInfo");
        return jvulkan::createVkResult(env, VK_RESULT_MAX_ENUM);
    }

    VmaPool vmaPool = nullptr;

    int result = vmaCreatePool(
            vmaAllocator,
            &vmaPoolCreateInfo,
            &vmaPool);
    if (result != VK_SUCCESS)
    {
        LOGERROR(env, "%s error code is %d", "Failed on call to vmaCreatePool", result);
    }

    jvulkan::freeMemory(&memoryToFree);

    jvulkan::setHandleValue(env, jVmaPool, vmaPool);

    return jvulkan::createVkResult(env, result);
}
