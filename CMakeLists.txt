cmake_minimum_required(VERSION 3.8)

# This batch of set statements will need their values changed to values
# that are appropriate for your development environment.
set(NormalSystemLibraries "/usr/lib64")
set(VulkanSDKLibraries "/home/dkaip/Downloads/VulkanSDK/1.1.106.0/x86_64/lib")
set(JVulkanNativeLibraries "/home/dkaip/git/jvulkan-natives-Linux-x86_64/Release")

set(JNIHeaders1 "/usr/lib/jvm/java-1.8.0/include/linux")
set(JNIHeaders2 "/usr/lib/jvm/java-1.8.0/include")

set(VulkanSDKHeaders "/home/dkaip/Downloads/VulkanSDK/1.1.106.0/x86_64/include")

# Now get on with business and get the library built
project(jvma-natives-Linux-x86_64)

# The additional / is important to remove the last character from the path.
# Note that it does not matter if the OS uses / or \, because we are only
# saving the path size.
string(LENGTH "${CMAKE_SOURCE_DIR}/" SOURCE_PATH_SIZE)
add_definitions("-DSOURCE_PATH_SIZE=${SOURCE_PATH_SIZE}")

file(GLOB jvma_natives_sources ./*.cpp ./*/*.cpp)
set(jvma_natives_srcs ${jvma_natives_sources}) 

# Add link library paths, BTW, this line needs to be before the add_library line below
link_directories(${NormalSystemLibraries} ${VulkanSDKLibraries} ${JVulkanNativeLibraries})

add_library(jvma-natives-Linux-x86_64 SHARED ${jvma_natives_srcs})

target_include_directories(jvma-natives-Linux-x86_64 PRIVATE ./headers)

# Headers for JNI stuff
target_include_directories(jvma-natives-Linux-x86_64 PRIVATE ${JNIHeaders1})
target_include_directories(jvma-natives-Linux-x86_64 PRIVATE ${JNIHeaders2})

# Headers for Vulkan SDK, currently 1.1.106.0
target_include_directories(jvma-natives-Linux-x86_64 PRIVATE ${VulkanSDKHeaders})

# Add vulkan modules
target_link_libraries(jvma-natives-Linux-x86_64 PRIVATE vulkan)
# For 106
target_link_libraries(jvma-natives-Linux-x86_64 PRIVATE VkLayer_api_dump)
target_link_libraries(jvma-natives-Linux-x86_64 PRIVATE VkLayer_assistant_layer)
target_link_libraries(jvma-natives-Linux-x86_64 PRIVATE VkLayer_core_validation)
target_link_libraries(jvma-natives-Linux-x86_64 PRIVATE VkLayer_demo_layer)
target_link_libraries(jvma-natives-Linux-x86_64 PRIVATE VkLayer_device_simulation)
target_link_libraries(jvma-natives-Linux-x86_64 PRIVATE VkLayer_khronos_validation)
target_link_libraries(jvma-natives-Linux-x86_64 PRIVATE VkLayer_monitor)
target_link_libraries(jvma-natives-Linux-x86_64 PRIVATE VkLayer_object_lifetimes)
target_link_libraries(jvma-natives-Linux-x86_64 PRIVATE VkLayer_screenshot)
target_link_libraries(jvma-natives-Linux-x86_64 PRIVATE VkLayer_starter_layer)
target_link_libraries(jvma-natives-Linux-x86_64 PRIVATE VkLayer_stateless_validation)
target_link_libraries(jvma-natives-Linux-x86_64 PRIVATE VkLayer_thread_safety)
target_link_libraries(jvma-natives-Linux-x86_64 PRIVATE VkLayer_unique_objects)
target_link_libraries(jvma-natives-Linux-x86_64 PRIVATE VkLayer_vktrace_layer)

# Add jvulkan Natives module
target_link_libraries(jvma-natives-Linux-x86_64 PRIVATE jvulkan-natives-Linux-x86_64)
