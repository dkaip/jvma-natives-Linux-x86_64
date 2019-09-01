/*
 * vmaGetMemoryProperties.cpp
 *
 *  Created on: Aug 30, 2019
 *      Author: Douglas Kaip
 */

#include "JVmaHelperFunctions.hh"
#include "JVulkanHelperFunctions.hh"
#include "com_CIMthetics_jvma_NativeProxies.h"
#include "slf4j.hh"

/*
 * Class:     com_CIMthetics_jvma_NativeProxies
 * Method:    vmaGetMemoryProperties
 * Signature: (Lcom/CIMthetics/jvma/Handles/VmaAllocator;Lcom/CIMthetics/jvulkan/VulkanCore/VK11/Structures/VkPhysicalDeviceMemoryProperties;)V
 */
JNIEXPORT void JNICALL Java_com_CIMthetics_jvma_NativeProxies_vmaGetMemoryProperties
  (JNIEnv *env, jobject, jobject jVmaAllocator, jobject jVkPhysicalDeviceMemoryPropertiesObject)
{
    struct VmaAllocator_T *vmaAllocator = (struct VmaAllocator_T *)jvma::getHandleValue(env, jVmaAllocator);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Could not retrieve VmaAllocator handle");
        return;
    }

    const VkPhysicalDeviceMemoryProperties *vkPhysicalDeviceMemoryProperties = nullptr;

    vmaGetMemoryProperties(vmaAllocator, &vkPhysicalDeviceMemoryProperties);

    jvulkan::populateVkPhysicalDeviceMemoryProperties(
            env,
            jVkPhysicalDeviceMemoryPropertiesObject,
            vkPhysicalDeviceMemoryProperties);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Error calling populateVkPhysicalDeviceMemoryProperties");
        return;
    }

}

