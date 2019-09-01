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
 * setHandleValue.cpp
 *
 *  Created on: Jun 20, 2019
 *      Author: Douglas Kaip
 */

#include "../headers/JVmaHelperFunctions.hh"
#include "slf4j.hh"

using namespace std;

namespace jvma
{
	void setHandleValue(JNIEnv *env, jobject jHandle, void *value)
	{
		jclass handleClass = env->GetObjectClass(jHandle);
		if (env->ExceptionOccurred())
		{
        	LOGERROR(env, "%s", "Could not find class for jHandle.");
			return;
		}

		jmethodID methodId = env->GetMethodID(handleClass, "setHandleValue", "(J)V");
		if (env->ExceptionOccurred())
		{
        	LOGERROR(env, "%s", "Could not find method id for setHandleValue.");
			return;
		}

		env->CallVoidMethod(jHandle, methodId, (jlong)value);
		if (env->ExceptionOccurred())
		{
        	LOGERROR(env, "%s", "Error calling CallVoidMethod.");
			return;
		}
	}
}
