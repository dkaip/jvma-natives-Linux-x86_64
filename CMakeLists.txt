cmake_minimum_required(VERSION 3.8)

# This batch of set statements will need their values changed to values
# that are appropriate for your development environment.
set(VulkanSDKLibraries "/home/dkaip/Downloads/VulkanSDK/1.1.126.0/x86_64/lib")
set(JVulkanNativeLibrary "/home/dkaip/git/jvulkan-natives-Linux-x86_64/Release")

set(JNIHeaders1 "/usr/lib/jvm/java-1.8.0/include/linux")
set(JNIHeaders2 "/usr/lib/jvm/java-1.8.0/include")

set(VulkanSDKHeaders "/home/dkaip/Downloads/VulkanSDK/1.1.126.0/x86_64/include")

# Now get on with business and get the library built
project(jvma-natives-Linux-x86_64)

find_library(VULKAN_NATIVE_LIBRARIES
	NAMES 	vulkan
		VkLayer_starter_layer
		VkLayer_vktrace_layer
		VkLayer_khronos_validation 
		VkLayer_monitor 
		VkLayer_api_dump 
		VkLayer_screenshot PATHS ${VulkanSDKLibraries} NO_DEFAULT_PATH)


find_library(JVULKAN_NATIVE_LIBRARY NAMES jvulkan-natives-Linux-x86_64 PATHS ${JVulkanNativeLibrary} NO_DEFAULT_PATH)


# The additional / is important to remove the last character from the path.
# Note that it does not matter if the OS uses / or \, because we are only
# saving the path size.
string(LENGTH "${CMAKE_SOURCE_DIR}/" SOURCE_PATH_SIZE)
add_definitions("-DSOURCE_PATH_SIZE=${SOURCE_PATH_SIZE}")

file(GLOB jvma_natives_sources ./*.cpp ./*/*.cpp)
set(jvma_natives_srcs ${jvma_natives_sources}) 

add_library(jvma-natives-Linux-x86_64 SHARED ${jvma_natives_srcs})

# Headers for JVMA native stuff
target_include_directories(jvma-natives-Linux-x86_64 PRIVATE ./headers)

# Headers for JNI stuff
target_include_directories(jvma-natives-Linux-x86_64 PRIVATE ${JNIHeaders1})
target_include_directories(jvma-natives-Linux-x86_64 PRIVATE ${JNIHeaders2})

# Headers for Vulkan SDK, currently 1.1.126.0
target_include_directories(jvma-natives-Linux-x86_64 PRIVATE ${VulkanSDKHeaders})

# Add libraries
target_link_libraries(jvma-natives-Linux-x86_64 PRIVATE ${VULKAN_NATIVE_LIBRARIES})
target_link_libraries(jvma-natives-Linux-x86_64 PRIVATE ${JVULKAN_NATIVE_LIBRARY})


