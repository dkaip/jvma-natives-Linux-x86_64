/*
 * Copyright 2019 Douglas Kaip
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/*
 * vmaBuildStatsString.cpp
 *
 *  Created on: Sep 3, 2019
 *      Author: Douglas Kaip
 */

#include "JVmaHelperFunctions.hh"
#include "JVulkanHelperFunctions.hh"
#include "com_CIMthetics_jvma_NativeProxies.h"
#include "slf4j.hh"

/*
 * Class:     com_CIMthetics_jvma_NativeProxies
 * Method:    vmaBuildStatsString
 * Signature: (Lcom/CIMthetics/jvma/Handles/VmaAllocator;Lcom/CIMthetics/jvma/Structures/StringReturnValue;Z)V
 */
JNIEXPORT void JNICALL Java_com_CIMthetics_jvma_NativeProxies_vmaBuildStatsString
  (JNIEnv *env, jobject, jobject jVmaAllocator, jobject jStatsString, jboolean detailedMap)
{
    struct VmaAllocator_T *vmaAllocator = (struct VmaAllocator_T *)jvulkan::getHandleValue(env, jVmaAllocator);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Could not retrieve VmaAllocator handle");
        return;
    }

    char *returnedStatsString = nullptr;
    vmaBuildStatsString(vmaAllocator, &returnedStatsString, detailedMap);

    jclass theClass = env->FindClass("com/CIMthetics/jvma/Structures/StringReturnValue");
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Could not find class com/CIMthetics/jvma/Structures/StringReturnValue");
        return;
    }

    jmethodID methodId = env->GetMethodID(theClass, "setValue", "(Ljava/lang/String;)V");
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Could not find method id setValue");
        return;
    }

    jstring statsString = env->NewStringUTF(returnedStatsString);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Error calling NewStringUTF");
        return;
    }

    env->CallVoidMethod(jStatsString, methodId, statsString);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Error calling CallVoidMethod");
        return;
    }

    env->DeleteLocalRef(statsString);
    if (env->ExceptionOccurred())
    {
        LOGERROR(env, "%s", "Error calling DeleteLocalRef");
        return;
    }

    /*
     * Since the copy of the returned string is now in the Java world
     * (subject to garbage collection) we can go ahead and
     * release the local string returnedStatsString now.
     */
    vmaFreeStatsString(vmaAllocator, returnedStatsString);
}
