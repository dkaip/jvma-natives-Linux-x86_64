/*
 * vmaCheckPoolCorruption.cpp
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
 * Method:    vmaCheckPoolCorruption
 * Signature: (Lcom/CIMthetics/jvma/Handles/VmaAllocator;Lcom/CIMthetics/jvma/Handles/VmaPool;)Lcom/CIMthetics/jvulkan/VulkanCore/VK11/Enums/VkResult;
 */
JNIEXPORT jobject JNICALL Java_com_CIMthetics_jvma_NativeProxies_vmaCheckPoolCorruption
  (JNIEnv *env, jobject, jobject jVmaAllocator, jobject jVmaPool)
{
    struct VmaAllocator_T *vmaAllocator = (struct VmaAllocator_T *)jvulkan::getHandleValue(env, jVmaAllocator);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Could not retrieve VmaAllocator handle");
        return jvulkan::createVkResult(env, VK_RESULT_MAX_ENUM);
    }

    struct VmaPool_T *vmaPool = (struct VmaPool_T *)jvulkan::getHandleValue(env, jVmaPool);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Could not retrieve jVmaPool handle");
        return jvulkan::createVkResult(env, VK_RESULT_MAX_ENUM);
    }

    VkResult result = vmaCheckPoolCorruption(
            vmaAllocator,
            vmaPool);

    return jvulkan::createVkResult(env, result);
}
