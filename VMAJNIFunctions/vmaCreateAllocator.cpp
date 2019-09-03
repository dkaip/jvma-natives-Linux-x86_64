/*
 * vmaCreateAllocator.cpp
 *
 *  Created on: Aug 29, 2019
 *      Author: Douglas Kaip
 */


using namespace std;

#include "com_CIMthetics_jvma_NativeProxies.h"
#include "JVmaHelperFunctions.hh"
#include "JVulkanHelperFunctions.hh"
#include "slf4j.hh"

/*
 * Class:     com_CIMthetics_jvma_NativeProxies
 * Method:    vmaCreateAllocator
 * Signature: (Lcom/CIMthetics/jvma/Structures/CreateInfos/VmaAllocatorCreateInfo;Lcom/CIMthetics/jvma/Handles/VmaAllocator;)Lcom/CIMthetics/jvulkan/VulkanCore/VK11/Enums/VkResult;
 */
JNIEXPORT jobject JNICALL Java_com_CIMthetics_jvma_NativeProxies_vmaCreateAllocator
  (JNIEnv *env, jobject, jobject jVmaAllocatorCreateInfo, jobject jVmaAllocator)
{
    std::vector<void *> memoryToFree(5);
    VmaAllocatorCreateInfo vmaAllocatorCreateInfo = {};

    jvma::getVmaAllocatorCreateInfo(
            env,
            jVmaAllocatorCreateInfo,
            &vmaAllocatorCreateInfo,
            &memoryToFree);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Failed on call to getVmaAllocatorCreateInfo");
        return jvulkan::createVkResult(env, VK_RESULT_MAX_ENUM);
    }

    VmaAllocator vmaAllocator = nullptr;

    int result = vmaCreateAllocator(
            &vmaAllocatorCreateInfo,
            &vmaAllocator);
    if (result != VK_SUCCESS)
    {
        LOGERROR(env, "%s error code is %d", "Failed on call to vmaCreateAllocator", result);
    }

    jvulkan::freeMemory(&memoryToFree);

    jvulkan::setHandleValue(env, jVmaAllocator, vmaAllocator);

    return jvulkan::createVkResult(env, result);
}

