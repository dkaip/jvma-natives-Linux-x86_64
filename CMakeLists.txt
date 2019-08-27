cmake_minimum_required(VERSION 3.8)

# This batch of set statements will need their values changed to values
# that are appropriate for your development environment.
set(NormalSystemLibraries "/usr/lib64")
set(VulkanSDKLibraries "/home/dkaip/Downloads/VulkanSDK/1.1.106.0/x86_64/lib")

set(JNIHeaders1 "/usr/lib/jvm/java-1.8.0/include/linux")
set(JNIHeaders2 "/usr/lib/jvm/java-1.8.0/include")

set(VulkanSDKHeaders "/home/dkaip/Downloads/VulkanSDK/1.1.106.0/x86_64/include")

# Now get on with business and get the library built
project(jVma-natives-Linux-x86_64)

# The additional / is important to remove the last character from the path.
# Note that it does not matter if the OS uses / or \, because we are only
# saving the path size.
string(LENGTH "${CMAKE_SOURCE_DIR}/" SOURCE_PATH_SIZE)
add_definitions("-DSOURCE_PATH_SIZE=${SOURCE_PATH_SIZE}")

file(GLOB jVma_natives_sources ./*.cpp ./*/*.cpp)
set(jVma_natives_srcs ${jVma_natives_sources}) 

# Add link library paths, BTW, this line needs to be before the add_library line below
link_directories(${NormalSystemLibraries} ${VulkanSDKLibraries})

add_library(jVma-natives-Linux-x86_64 SHARED ${jVma_natives_srcs})

target_include_directories(jVma-natives-Linux-x86_64 PRIVATE ./headers)

# Headers for JNI stuff
target_include_directories(jVma-natives-Linux-x86_64 PRIVATE ${JNIHeaders1})
target_include_directories(jVma-natives-Linux-x86_64 PRIVATE ${JNIHeaders2})

# Headers for Vulkan SDK, currently 1.1.106.0
target_include_directories(jVma-natives-Linux-x86_64 PRIVATE ${VulkanSDKHeaders})
