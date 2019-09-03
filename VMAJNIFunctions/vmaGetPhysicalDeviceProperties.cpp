/*
 * vmaGetPhysicalDeviceProperties.cpp
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
 * Method:    vmaGetPhysicalDeviceProperties
 * Signature: (Lcom/CIMthetics/jvma/Handles/VmaAllocator;Lcom/CIMthetics/jvulkan/VulkanCore/VK11/Structures/VkPhysicalDeviceProperties;)V
 */
JNIEXPORT void JNICALL Java_com_CIMthetics_jvma_NativeProxies_vmaGetPhysicalDeviceProperties
  (JNIEnv *env, jobject, jobject jVmaAllocator, jobject jVkPhysicalDevicePropertiesObject)
{
    struct VmaAllocator_T *vmaAllocator = (struct VmaAllocator_T *)jvulkan::getHandleValue(env, jVmaAllocator);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Could not retrieve VmaAllocator handle");
        return;
    }

    const VkPhysicalDeviceProperties *vkPhysicalDeviceProperties = nullptr;

    vmaGetPhysicalDeviceProperties(vmaAllocator, &vkPhysicalDeviceProperties);

    jvulkan::populateVkPhysicalDeviceProperties(
            env,
            jVkPhysicalDevicePropertiesObject,
            vkPhysicalDeviceProperties);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Error calling createVkPhysicalDeviceProperties");
        return;
    }
}
