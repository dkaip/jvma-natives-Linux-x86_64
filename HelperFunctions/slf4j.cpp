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
 * slf4j.cpp
 *
 *  Created on: Apr 22, 2019
 *      Author: Douglas Kaip
 */

#include "../headers/slf4j.hh"

#include <stdarg.h>
#include <string.h>
#include <mutex>

#define LOGGER_NAME "jvma-natives"

namespace slf4j
{
	Logger *Logger::instance = nullptr;
	std::mutex Logger::creation_Mutex;
	jmethodID Logger::infoMethodId = nullptr;
	jmethodID Logger::debugMethodId = nullptr;
	jmethodID Logger::traceMethodId = nullptr;
	jmethodID Logger::warnMethodId = nullptr;
	jmethodID Logger::errorMethodId = nullptr;
	jobject   Logger::slf4jLoggerObject = nullptr;

	Logger::Logger(JNIEnv *env)
	{
		jclass loggerClass = nullptr;

		loggerClass = env->FindClass("org/slf4j/Logger");
		if (loggerClass == nullptr)
		{
			std::cerr << "Could not find class org/slf4j/Logger...it is required." << std::endl;
		}

		jclass loggerFactoryClass = env->FindClass("org/slf4j/LoggerFactory");
		if (loggerClass == nullptr)
		{
			std::cerr << "Could not find class org/slf4j/LoggerFactory...it is required." << std::endl;
		}

		jmethodID methodId = env->GetStaticMethodID(loggerFactoryClass, "getLogger", "(Ljava/lang/String;)Lorg/slf4j/Logger;");
		if (methodId == nullptr)
		{
			std::cerr << "Could not find method getLogger in org/slf4j/LoggerFactory with signature \"(Ljava/lang/String;)Lorg/slf4j/Logger;\"...it is required." << std::endl;
		}

		jstring loggerNameString = env->NewStringUTF(LOGGER_NAME);

		if (env->ExceptionOccurred())
		{
			return;
		}

		jobject localLoggerObject = env->CallObjectMethod(loggerFactoryClass, methodId, loggerNameString);

		env->DeleteLocalRef(loggerNameString);

		/*
		 * We need to get a global ref because this will be used later in all logging calls.
		 *
		 * We are not deleting the global ref anywhere because it should hang around until
		 * the program exits.
		 */
		slf4jLoggerObject = reinterpret_cast<jobject>(env->NewGlobalRef(localLoggerObject));

		infoMethodId = env->GetMethodID(loggerClass, "info", "(Ljava/lang/String;)V");
		if (methodId == nullptr)
		{
			std::cerr << "Could not find method info in org/slf4j/Logger with signature \"(Ljava/lang/String;)V\"...it is required." << std::endl;
		}

		debugMethodId = env->GetMethodID(loggerClass, "debug", "(Ljava/lang/String;)V");
		if (methodId == nullptr)
		{
			std::cerr << "Could not find method debug in org/slf4j/Logger with signature \"(Ljava/lang/String;)V\"...it is required." << std::endl;
		}

		traceMethodId = env->GetMethodID(loggerClass, "trace", "(Ljava/lang/String;)V");
		if (methodId == nullptr)
		{
			std::cerr << "Could not find method trace in org/slf4j/Logger with signature \"(Ljava/lang/String;)V\"...it is required." << std::endl;
		}

		warnMethodId = env->GetMethodID(loggerClass, "warn", "(Ljava/lang/String;)V");
		if (methodId == nullptr)
		{
			std::cerr << "Could not find method warn in org/slf4j/Logger with signature \"(Ljava/lang/String;)V\"...it is required." << std::endl;
		}

		errorMethodId = env->GetMethodID(loggerClass, "error", "(Ljava/lang/String;)V");
		if (methodId == nullptr)
		{
			std::cerr << "Could not find method error in org/slf4j/Logger with signature \"(Ljava/lang/String;)V\"...it is required." << std::endl;
		}
	}

	void Logger::info(JNIEnv *env, const char *textString)
	{
        jstring jTextString = env->NewStringUTF(textString);

		env->CallVoidMethod(slf4jLoggerObject, infoMethodId, jTextString);

        env->DeleteLocalRef(jTextString);
	}

	void Logger::debug(JNIEnv *env, const char *textString)
	{
        jstring jTextString = env->NewStringUTF(textString);

		env->CallVoidMethod(slf4jLoggerObject, debugMethodId, jTextString);

        env->DeleteLocalRef(jTextString);
	}

	void Logger::trace(JNIEnv *env, const char *textString)
	{
        jstring jTextString = env->NewStringUTF(textString);

		env->CallVoidMethod(slf4jLoggerObject, traceMethodId, jTextString);

        env->DeleteLocalRef(jTextString);
	}

	void Logger::warn(JNIEnv *env, const char *textString)
	{
        jstring jTextString = env->NewStringUTF(textString);

		env->CallVoidMethod(slf4jLoggerObject, warnMethodId, jTextString);

        env->DeleteLocalRef(jTextString);
	}

	void Logger::error(JNIEnv *env, const char *textString)
	{
        jstring jTextString = env->NewStringUTF(textString);

		env->CallVoidMethod(slf4jLoggerObject, errorMethodId, jTextString);

        env->DeleteLocalRef(jTextString);
	}
}

