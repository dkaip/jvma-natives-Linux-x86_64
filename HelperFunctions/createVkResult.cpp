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
 * createVkResult.cpp
 *
 *  Created on: Apr 22, 2019
 *      Author: Douglas Kaip
 */

#include "HelperFunctions.hh"
#include "slf4j.hh"


using namespace std;

namespace jvma
{
	jobject createVkResult(JNIEnv *env, jint value)
	{
		/*
		 * This function is usually called just before the caller is returning
		 * back to Java.  If value does not correspond to VK_SUCCESS it may be
		 * because some other function call has failed and thrown an exception.
		 * In that case our "env" methods will not work properly.  Since the
		 * calling function is most likely going to return with the result of
		 * this call immediately we are going to clear the exception so that
		 * we can properly create the appropriate response.
		 */
		jboolean handlingException = env->ExceptionCheck();
		if (handlingException == true)
		{
			env->ExceptionClear();
		}

		jclass vkResultClass = env->FindClass("com/CIMthetics/jvulkan/VulkanCore/VK11/Enums/VkResult");
		if (env->ExceptionOccurred())
		{
            LOGERROR(env, "createVkResult: could not find class %s", "com/CIMthetics/jvulkan/VulkanCore/VK11/Enums/VkResult");
			return nullptr;
		}

		jmethodID methodId = env->GetStaticMethodID(vkResultClass, "fromValue", "(I)Lcom/CIMthetics/jvulkan/VulkanCore/VK11/Enums/VkResult;");
		if (env->ExceptionOccurred())
		{
            LOGERROR(env, "createVkResult: could not find static method %s", "fromValue with signature (I)Lcom/CIMthetics/jvulkan/VulkanCore/VK11/Enums/VkResult;");
			return nullptr;
		}

		return env->CallStaticObjectMethod(vkResultClass, methodId, value);
	}
}
