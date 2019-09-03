/*
 * getVmaRecordSettings.cpp
 *
 *  Created on: Aug 29, 2019
 *      Author: Douglas Kaip
 */

#include "JVmaHelperFunctions.hh"
#include "JVulkanHelperFunctions.hh"
#include "slf4j.hh"

namespace jvma
{
    void getVmaRecordSettings(
            JNIEnv *env,
            jobject jVmaRecordSettingsObject,
            VmaRecordSettings *vmaRecordSettings,
            std::vector<void *> *memoryToFree)
    {
        jclass theClass = env->GetObjectClass(jVmaRecordSettingsObject);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error trying to get class for jVmaRecordSettingsObject");
            return;
        }

        ////////////////////////////////////////////////////////////////////////
        jmethodID methodId = env->GetMethodID(theClass, "getFlags", "()Ljava/util/EnumSet;");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id for getFlags");
            return;
        }

        jobject flagsObject = env->CallObjectMethod(jVmaRecordSettingsObject, methodId);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling CallObjectMethod");
            return;
        }

        VmaRecordFlags flags = jvulkan::getEnumSetValue(
                env,
                flagsObject,
                "com/CIMthetics/jvma/Enums/VmaRecordFlagBits");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling getEnumSetValue");
            return;
        }

        ////////////////////////////////////////////////////////////////////////
        methodId = env->GetMethodID(theClass, "getpFilePath", "()Ljava/lang/String;");
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Could not find method id for getFlags");
            return;
        }

        jstring jTheFileName = (jstring)env->CallObjectMethod(jVmaRecordSettingsObject, methodId);
        if (env->ExceptionOccurred())
        {
            LOGERROR(env, "%s", "Error calling CallObjectMethod");
            return;
        }

        const char *tempString = env->GetStringUTFChars(jTheFileName, 0);

        char *theFileName = (char *)calloc(1, strlen(tempString) + 1);
        memoryToFree->push_back(theFileName);

        strcpy(theFileName, tempString);
        env->ReleaseStringUTFChars(jTheFileName, tempString);


        vmaRecordSettings->flags = flags;
        vmaRecordSettings->pFilePath = theFileName;
    }
}



