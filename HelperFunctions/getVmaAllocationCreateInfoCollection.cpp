/*
 * getVmaAllocationCreateInfoCollection.cpp
 *
 *  Created on: Sep 16, 2019
 *      Author: Douglas Kaip
 */

#include "JVmaHelperFunctions.hh"
#include "JVulkanHelperFunctions.hh"
#include "com_CIMthetics_jvma_NativeProxies.h"
#include "slf4j.hh"

namespace jvma
{
    void getVmaAllocationCreateInfoCollection(
            JNIEnv *env,
            const jobject jVmaAllocationCreateInfoCollectionObject,
            VmaAllocationCreateInfo **vmaAllocationCreateInfos,
            int *numberOfVmaAllocationCreateInfos,
            std::vector<void *> *memoryToFree)
    {
        jclass vmaAllocationCreateInfoCollectionClass = env->GetObjectClass(jVmaAllocationCreateInfoCollectionObject);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not get class for jVkDeviceQueueCreateInfoCollectionObject");
            return;
        }

        jmethodID methodId = env->GetMethodID(vmaAllocationCreateInfoCollectionClass, "size", "()I");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id size");
            return;
        }

        jint numberOfElements = env->CallIntMethod(jVmaAllocationCreateInfoCollectionObject, methodId);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "CallIntMethod failed to get the size for jVmaAllocationCreateInfoCollectionObject");
            return;
        }

        *numberOfVmaAllocationCreateInfos = numberOfElements;
        *vmaAllocationCreateInfos = (VmaAllocationCreateInfo *)calloc(numberOfElements, sizeof(VmaAllocationCreateInfo));
        if (*vmaAllocationCreateInfos == nullptr)
        {
            LOGERROR(env, "%s", "Could not allocate memory for vmaAllocationCreateInfos");
            return;
        }
        memoryToFree->push_back(*vmaAllocationCreateInfos);

        jmethodID iteratorMethodId = env->GetMethodID(vmaAllocationCreateInfoCollectionClass, "iterator", "()Ljava/util/Iterator;");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id iterator");
            return;
        }

        jobject iteratorObject = env->CallObjectMethod(jVmaAllocationCreateInfoCollectionObject, iteratorMethodId);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling CallObjectMethod.");
            return;
        }

        jclass iteratorClass = env->GetObjectClass(iteratorObject);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find object class for iteratorObject.");
            return;
        }

        jmethodID hasNextMethodId = env->GetMethodID(iteratorClass, "hasNext", "()Z");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id hasNext");
            return;
        }

        jmethodID nextMethod = env->GetMethodID(iteratorClass, "next", "()Ljava/lang/Object;");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id next");
            return;
        }

        int i = 0;
        do
        {
            jboolean hasNext = env->CallBooleanMethod(iteratorObject, hasNextMethodId);
            if (env->ExceptionOccurred())
            {
                LOGERROR(env, "%s", "Error calling CallBooleanMethod.");
                break;
            }

            if (hasNext == false)
            {
                break;
            }

            jobject jVmaAllocationCreateInfoObject = env->CallObjectMethod(iteratorObject, nextMethod);
            if (env->ExceptionOccurred())
            {
                LOGERROR(env, "%s", "Error calling CallObjectMethod.");
                break;
            }

            jvma::getVmaAllocationCreateInfo(
                    env,
                    jVmaAllocationCreateInfoObject,
                    &((*vmaAllocationCreateInfos)[i]),
                    memoryToFree);
            if (env->ExceptionOccurred())
            {
                LOGERROR(env, "%s", "Failed calling getVmaAllocationCreateInfo");
                break;
            }

            i++;
        } while(true);
    }
}
