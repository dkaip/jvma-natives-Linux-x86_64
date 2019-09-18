/*
 * getVmaDefragmentationInfo2.cpp
 *
 *  Created on: Sep 17, 2019
 *      Author: Douglas Kaip
 */

#include "JVmaHelperFunctions.hh"
#include "JVulkanHelperFunctions.hh"
#include "slf4j.hh"

namespace jvma
{
    void getVmaDefragmentationInfo2(
            JNIEnv *env,
            jobject jVmaDefragmentationInfo2Object,
            VmaDefragmentationInfo2 *vmaDefragmentationInfo2,
            std::vector<void *> *memoryToFree)
    {
        jclass theClass = env->GetObjectClass(jVmaDefragmentationInfo2Object);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error trying to get class for jVmaDefragmentationInfo2Object");
            return;
        }

        ////////////////////////////////////////////////////////////////////////
        jmethodID methodId = env->GetMethodID(theClass, "getFlags", "()Ljava/util/EnumSet;");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id for getFlags");
            return;
        }

        jobject flagsObject = env->CallObjectMethod(jVmaDefragmentationInfo2Object, methodId);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling CallObjectMethod");
            return;
        }

        VmaDefragmentationFlags flags = jvulkan::getEnumSetValue(
                env,
                flagsObject,
                "com/CIMthetics/jvma/Enums/VmaDefragmentationFlagBits");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling getEnumSetValue");
            return;
        }

        ////////////////////////////////////////////////////////////////////////
        methodId = env->GetMethodID(theClass, "getAllocations", "()Ljava/util/Collection;");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id for getAllocations");
            return;
        }

        jobject jAllocationsCollectionObject = env->CallObjectMethod(jVmaDefragmentationInfo2Object, methodId);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling CallObjectMethod");
            return;
        }

        if (jAllocationsCollectionObject == nullptr)
        {
            LOGERROR(env, "%s", "jAllocationsObject is nullptr");
            return;
        }

        int numberOfAllocationHandles = 0;
        VmaAllocation *vmaAllocations = nullptr;
        jvulkan::getVulkanHandleCollection(
                env,
                jAllocationsCollectionObject,
                (void **)&vmaAllocations,
                &numberOfAllocationHandles,
                memoryToFree);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling getVulkanHandleCollection");
            return;
        }

        ////////////////////////////////////////////////////////////////////////
        methodId = env->GetMethodID(theClass, "getAllocationsChanged", "()[Z");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id for getAllocationsChanged");
            return;
        }

        jobject jAllocationsChangedObject = env->CallObjectMethod(jVmaDefragmentationInfo2Object, methodId);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling CallObjectMethod");
            return;
        }

        VkBool32 *allocationsChangedArray = nullptr;
        if (jAllocationsChangedObject != nullptr)
        {
            /*
             * Since it is not null we need to allocate the memory for the
             * outgoing information.  It needs to have the same number of
             * elements as the allocations collection.
             */
            allocationsChangedArray = (VkBool32 *)calloc(numberOfAllocationHandles, sizeof(VkBool32));
            memoryToFree->push_back(allocationsChangedArray);
        }

        ////////////////////////////////////////////////////////////////////////
        methodId = env->GetMethodID(theClass, "getPools", "()Ljava/util/Collection;");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id for getPools");
            return;
        }

        jobject jPoolsCollectionObject = env->CallObjectMethod(jVmaDefragmentationInfo2Object, methodId);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling CallObjectMethod");
            return;
        }

        int numberOfPoolHandles = 0;
        VmaPool *vmaPools = nullptr;
        if (jPoolsCollectionObject != nullptr)
        {
            jvulkan::getVulkanHandleCollection(
                    env,
                    jPoolsCollectionObject,
                    (void **)&vmaPools,
                    &numberOfPoolHandles,
                    memoryToFree);
            if (env->ExceptionOccurred())
            {
                LOGERROR(env, "%s", "Error calling getVulkanHandleCollection");
                return;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        methodId = env->GetMethodID(theClass, "getMaxCpuBytesToMove", "()J");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id for getMaxCpuBytesToMove");
            return;
        }

        jlong maxCpuBytesToMove = env->CallLongMethod(jVmaDefragmentationInfo2Object, methodId);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling CallLongMethod");
            return;
        }

        ////////////////////////////////////////////////////////////////////////
        methodId = env->GetMethodID(theClass, "getMaxCpuAllocationsToMove", "()I");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id for getMaxCpuAllocationsToMove");
            return;
        }

        jint maxCpuAllocationsToMove = env->CallIntMethod(jVmaDefragmentationInfo2Object, methodId);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling CallIntMethod");
            return;
        }

        ////////////////////////////////////////////////////////////////////////
        methodId = env->GetMethodID(theClass, "getMaxGpuBytesToMove", "()J");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id for getMaxGpuBytesToMove");
            return;
        }

        jlong maxGpuBytesToMove = env->CallLongMethod(jVmaDefragmentationInfo2Object, methodId);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling CallLongMethod");
            return;
        }

        ////////////////////////////////////////////////////////////////////////
        methodId = env->GetMethodID(theClass, "getMaxGpuAllocationsToMove", "()I");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id for getMaxGpuAllocationsToMove");
            return;
        }

        jint maxGpuAllocationsToMove = env->CallIntMethod(jVmaDefragmentationInfo2Object, methodId);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling CallIntMethod");
            return;
        }

        ////////////////////////////////////////////////////////////////////////
        methodId = env->GetMethodID(theClass, "getCommandBuffer", "()Lcom/CIMthetics/jvulkan/VulkanCore/VK11/Handles/VkCommandBuffer;");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id for getCommandBuffer");
            return;
        }

        jobject jCommandBuffer = env->CallObjectMethod(jVmaDefragmentationInfo2Object, methodId);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling CallObjectMethod");
            return;
        }

        VkCommandBuffer commandBuffer = nullptr;
        if (jCommandBuffer != nullptr)
        {
            commandBuffer = (VkCommandBuffer)jvulkan::getHandleValue(env, jCommandBuffer);
            if (env->ExceptionOccurred())
            {
                LOGERROR(env, "%s", "Could not retrieve VkCommandBuffer handle");
                return;
            }
        }

        vmaDefragmentationInfo2->flags = flags;
        vmaDefragmentationInfo2->allocationCount = numberOfAllocationHandles;
        vmaDefragmentationInfo2->pAllocations = vmaAllocations;
        vmaDefragmentationInfo2->pAllocationsChanged = allocationsChangedArray;
        vmaDefragmentationInfo2->poolCount = numberOfPoolHandles;
        vmaDefragmentationInfo2->pPools = vmaPools;
        vmaDefragmentationInfo2->maxCpuBytesToMove = maxCpuBytesToMove;
        vmaDefragmentationInfo2->maxCpuAllocationsToMove = maxCpuAllocationsToMove;
        vmaDefragmentationInfo2->maxGpuBytesToMove = maxGpuBytesToMove;
        vmaDefragmentationInfo2->maxGpuAllocationsToMove = maxGpuAllocationsToMove;
        vmaDefragmentationInfo2->commandBuffer = commandBuffer;
    }
}
