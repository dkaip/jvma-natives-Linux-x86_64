/*
 * vmaFreeMemoryPages.cpp
 *
 *  Created on: Sep 16, 2019
 *      Author: Douglas Kaip
 */

#include "JVmaHelperFunctions.hh"
#include "JVulkanHelperFunctions.hh"
#include "com_CIMthetics_jvma_NativeProxies.h"
#include "slf4j.hh"

//static void getHandleCollection(
//        JNIEnv *env,
//        const jobject jVmaAllocationCollectionObject,
//        VmaAllocation **vmaAllocations,
//        int *numberOfVmaAllocations,
//        std::vector<void *> *memoryToFree);
//
/*
 * Class:     com_CIMthetics_jvma_NativeProxies
 * Method:    vmaFreeMemoryPages
 * Signature: (Lcom/CIMthetics/jvma/Handles/VmaAllocator;Ljava/util/Collection;)V
 */
JNIEXPORT void JNICALL Java_com_CIMthetics_jvma_NativeProxies_vmaFreeMemoryPages
  (JNIEnv *env, jobject, jobject jVmaAllocator, jobject jVmaAllocationCollection)
{
    struct VmaAllocator_T *vmaAllocator = (struct VmaAllocator_T *)jvulkan::getHandleValue(env, jVmaAllocator);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Could not retrieve VmaAllocator handle");
        return;
    }

    if (jVmaAllocationCollection == nullptr)
    {
        LOGERROR(env, "%s", "jVmaAllocationCollection may not be null");
        return;
    }

    std::vector<void *> memoryToFree(5);
    int numberOfHandles = 0;
    VmaAllocation *vmaAllocations = nullptr;
    jvulkan::getVulkanHandleCollection(
            env,
            jVmaAllocationCollection,
            (void **)&vmaAllocations,
            &numberOfHandles,
            &memoryToFree);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Error calling getVulkanHandleCollection");
        return;
    }

    vmaFreeMemoryPages(
            vmaAllocator,
            numberOfHandles,
            vmaAllocations);
}

//static void getHandleCollection(
//        JNIEnv *env,
//        const jobject jVmaAllocationCollectionObject,
//        VmaAllocation **vmaAllocations,
//        int *numberOfVmaAllocations,
//        std::vector<void *> *memoryToFree)
//{
//    jclass theClass = env->GetObjectClass(jVmaAllocationCollectionObject);
//    if (env->ExceptionOccurred())
//    {
//        LOGERROR(env, "%s", "Could not find class for jVmaAllocationCollectionObject.");
//        return;
//    }
//
//    jmethodID methodId = env->GetMethodID(theClass, "size", "()I");
//    if (env->ExceptionOccurred())
//    {
//        LOGERROR(env, "%s", "Could not find method id for size");
//        return;
//    }
//
//    jint numberOfElements = env->CallIntMethod(jVmaAllocationCollectionObject, methodId);
//    if (env->ExceptionOccurred())
//    {
//        LOGERROR(env, "%s", "Error calling CallIntMethod");
//        return;
//    }
//
//    *numberOfVmaAllocations = numberOfElements;
//    *vmaAllocations = (VmaAllocation *)calloc(numberOfElements, sizeof(VmaAllocation));
//    if (*vmaAllocations == nullptr)
//    {
//        LOGERROR(env, "%s", "Error trying to allocate memory for *vmaAllocations");
//        return;
//    }
//
//    memoryToFree->push_back(*vmaAllocations);
//
//    jmethodID iteratorMethodId = env->GetMethodID(theClass, "iterator", "()Ljava/util/Iterator;");
//    if (env->ExceptionOccurred())
//    {
//        LOGERROR(env, "%s", "Could not find method id for iterator");
//        return;
//    }
//
//    jobject iteratorObject = env->CallObjectMethod(jVmaAllocationCollectionObject, iteratorMethodId);
//    if (env->ExceptionOccurred())
//    {
//        LOGERROR(env, "%s", "Error calling CallObjectMethod");
//        return;
//    }
//
//    jclass iteratorClass = env->GetObjectClass(iteratorObject);
//    if (env->ExceptionOccurred())
//    {
//        LOGERROR(env, "%s", "Could not find class for iteratorObject.");
//        return;
//    }
//
//    jmethodID hasNextMethodId = env->GetMethodID(iteratorClass, "hasNext", "()Z");
//    if (env->ExceptionOccurred())
//    {
//        LOGERROR(env, "%s", "Could not find method id for hasNext");
//        return;
//    }
//
//    jmethodID nextMethod = env->GetMethodID(iteratorClass, "next", "()Ljava/lang/Object;");
//    if (env->ExceptionOccurred())
//    {
//        LOGERROR(env, "%s", "Could not find method id for next");
//        return;
//    }
//
//    int i = 0;
//    do
//    {
//        jboolean hasNext = env->CallBooleanMethod(iteratorObject, hasNextMethodId);
//        if (env->ExceptionOccurred())
//        {
//            LOGERROR(env, "%s", "Error calling CallBooleanMethod");
//            break;
//        }
//
//        if (hasNext == false)
//        {
//            break;
//        }
//
//        jobject jVmaAllocationObject = env->CallObjectMethod(iteratorObject, nextMethod);
//        if (env->ExceptionOccurred())
//        {
//            LOGERROR(env, "%s", "Error calling CallObjectMethod");
//            break;
//        }
//
//        VmaAllocation vmaAllocation = (VmaAllocation)jvulkan::getHandleValue(env, jVmaAllocationObject);
//        if (env->ExceptionOccurred())
//        {
//            LOGERROR(env, "%s", "Could not retrieve VmaAllocation handle");
//            return;
//        }
//
//        (*vmaAllocations)[i] = vmaAllocation;
//
//        i++;
//    } while(true);
//}
