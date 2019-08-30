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
 * slf4j.hh
 *
 *  Created on: Apr 22, 2019
 *      Author: Douglas Kaip
 */

#include <cstdarg>
#include <iostream>
#include <string.h>
#include <jni.h>
#include <mutex>

#ifndef HEADERS_SLF4J_H_
#define HEADERS_SLF4J_H_

#define FORMAT_BUFFER_SIZE 256
#define TEXT_BUFFER_SIZE 4096

// The following define (SOURCE_PATH_SIZE) comes from the CMakeLists.txt file.
#define __SHORTFILENAME__ (__FILE__ + SOURCE_PATH_SIZE)

#ifdef __GNUC__

#define BASE_FORMAT_STRING "%s:Line %d:Function %s:"

#define LOGINFO(env, format, ...) (\
{\
	char formatString[FORMAT_BUFFER_SIZE];\
	formatString[0] = '\0';\
    strcpy(formatString, BASE_FORMAT_STRING);\
    strcat(formatString, format);\
	char textBuffer[TEXT_BUFFER_SIZE];\
    textBuffer[0] = '\0';\
    sprintf(textBuffer, formatString, __SHORTFILENAME__, __LINE__, __func__, ##__VA_ARGS__);\
    slf4j::Logger::getInstance(env)->info(env, textBuffer);\
})
#define LOGDEBUG(env, format, ...) (\
{\
	char formatString[FORMAT_BUFFER_SIZE];\
	formatString[0] = '\0';\
    strcpy(formatString, BASE_FORMAT_STRING);\
    strcat(formatString, format);\
	char textBuffer[TEXT_BUFFER_SIZE];\
    textBuffer[0] = '\0';\
    sprintf(textBuffer, formatString, __SHORTFILENAME__, __LINE__, __func__, ##__VA_ARGS__);\
    slf4j::Logger::getInstance(env)->debug(env, textBuffer);\
})
#define LOGTRACE(env, format, ...) (\
{\
	char formatString[FORMAT_BUFFER_SIZE];\
	formatString[0] = '\0';\
    strcpy(formatString, BASE_FORMAT_STRING);\
    strcat(formatString, format);\
	char textBuffer[TEXT_BUFFER_SIZE];\
    textBuffer[0] = '\0';\
    sprintf(textBuffer, formatString, __SHORTFILENAME__, __LINE__, __func__, ##__VA_ARGS__);\
    slf4j::Logger::getInstance(env)->trace(env, textBuffer);\
})
#define LOGWARN(env, format, ...) (\
{\
	char formatString[FORMAT_BUFFER_SIZE];\
	formatString[0] = '\0';\
    strcpy(formatString, BASE_FORMAT_STRING);\
    strcat(formatString, format);\
	char textBuffer[TEXT_BUFFER_SIZE];\
    textBuffer[0] = '\0';\
    sprintf(textBuffer, formatString, __SHORTFILENAME__, __LINE__, __func__, ##__VA_ARGS__);\
    slf4j::Logger::getInstance(env)->warn(env, textBuffer);\
})
#define LOGERROR(env, format, ...) (\
{\
	char formatString[FORMAT_BUFFER_SIZE];\
	formatString[0] = '\0';\
    strcpy(formatString, BASE_FORMAT_STRING);\
    strcat(formatString, format);\
	char textBuffer[TEXT_BUFFER_SIZE];\
    textBuffer[0] = '\0';\
    sprintf(textBuffer, formatString, __SHORTFILENAME__, __LINE__, __func__, ##__VA_ARGS__);\
    slf4j::Logger::getInstance(env)->error(env, textBuffer);\
})

#else

#define BASE_FORMAT_STRING "%s:Line %d:"

#define LOGINFO(env, format, ...) (\
{\
	char formatString[FORMAT_BUFFER_SIZE];\
	formatString[0] = '\0';\
    strcpy(formatString, BASE_FORMAT_STRING);\
    strcat(formatString, format);\
	char textBuffer[TEXT_BUFFER_SIZE];\
    textBuffer[0] = '\0';\
    sprintf(textBuffer, formatString, __SHORTFILENAME__, __LINE__, __func__, ##__VA_ARGS__);\
    slf4j::Logger::getInstance(env)->info(env, textBuffer);\
})
#define LOGDEBUG(env, format, ...) (\
{\
	char formatString[FORMAT_BUFFER_SIZE];\
	formatString[0] = '\0';\
    strcpy(formatString, BASE_FORMAT_STRING);\
    strcat(formatString, format);\
	char textBuffer[TEXT_BUFFER_SIZE];\
    textBuffer[0] = '\0';\
    sprintf(textBuffer, formatString, __SHORTFILENAME__, __LINE__, __func__, ##__VA_ARGS__);\
    slf4j::Logger::getInstance(env)->debug(env, textBuffer);\
})
#define LOGTRACE(env, format, ...) (\
{\
	char formatString[FORMAT_BUFFER_SIZE];\
	formatString[0] = '\0';\
    strcpy(formatString, BASE_FORMAT_STRING);\
    strcat(formatString, format);\
	char textBuffer[TEXT_BUFFER_SIZE];\
    textBuffer[0] = '\0';\
    sprintf(textBuffer, formatString, __SHORTFILENAME__, __LINE__, __func__, ##__VA_ARGS__);\
    slf4j::Logger::getInstance(env)->trace(env, textBuffer);\
})
#define LOGWARN(env, format, ...) (\
{\
	char formatString[FORMAT_BUFFER_SIZE];\
	formatString[0] = '\0';\
    strcpy(formatString, BASE_FORMAT_STRING);\
    strcat(formatString, format);\
	char textBuffer[TEXT_BUFFER_SIZE];\
    textBuffer[0] = '\0';\
    sprintf(textBuffer, formatString, __SHORTFILENAME__, __LINE__, __func__, ##__VA_ARGS__);\
    slf4j::Logger::getInstance(env)->warn(env, textBuffer);\
})
#define LOGERROR(env, format, ...) (\
{\
	char formatString[FORMAT_BUFFER_SIZE];\
	formatString[0] = '\0';\
    strcpy(formatString, BASE_FORMAT_STRING);\
    strcat(formatString, format);\
	char textBuffer[TEXT_BUFFER_SIZE];\
    textBuffer[0] = '\0';\
    sprintf(textBuffer, formatString, __SHORTFILENAME__, __LINE__, __func__, ##__VA_ARGS__);\
    slf4j::Logger::getInstance(env)->error(env, textBuffer);\
})

#endif

namespace slf4j
{
    class Logger
	{
		private:
    		static Logger *instance;
    		static std::mutex creation_Mutex;
    		static jclass loggerClass;
    		static jmethodID infoMethodId;
    		static jmethodID debugMethodId;
    		static jmethodID traceMethodId;
    		static jmethodID warnMethodId;
    		static jmethodID errorMethodId;
    		static jobject slf4jLoggerObject;

    		Logger(JNIEnv *env);

		public:
    		static Logger* getInstance(JNIEnv *env)
    	 	{
    			{
					std::lock_guard<std::mutex> lock(creation_Mutex);
					if (instance == nullptr)
					{
						instance = new Logger(env);
					}
    			}

    	 		return instance;
    	 	}

			 Logger(Logger const&)			= delete;
			 Logger(Logger const&&)			= delete;
    	 	 void operator=(Logger const&)	= delete;
    	 	 void operator=(Logger const&&)	= delete;

    	 	 void info(JNIEnv *env, const char *textString);
    	 	 void debug(JNIEnv *env, const char *textString);
    	 	 void trace(JNIEnv *env, const char *textString);
    	 	 void warn(JNIEnv *env, const char *textString);
    	 	 void error(JNIEnv *env, const char *textString);
	};
}

#endif /* HEADERS_SLF4J_H_ */
