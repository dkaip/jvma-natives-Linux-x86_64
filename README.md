# jvma-natives-Linux-x86_64

**jvma-natives-Linux-x86_64** is a native library written in C++ that is used (required) by the 
[jvma](https://github.com/dkaip/jvma) (Java Vulkan Memory Allocator) project.  This project provides the interface between **jvma** 
and the [Vulkan Memory Allocator Project](https://github.com/GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator) which is written in C++.

## Prerequisites
There are currently no prerequisites for this project.
It contains the <code>vk&lowbar;mem&lowbar;alloc.h</code> 
file that is the code as well as the header required for the 
[Vulkan Memory Allocator](https://github.com/GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator). 
The file that is currently included corresponds to release <code>2.2.0</code> dated 
13-dec-2018.

If you desire a more current release of the Vulkan Memory Allocator you will need to go 
and get the version of the file <code>vk&lowbar;mem&lowbar;alloc.h</code> you 
want / need, replace the version that is currently included in this project with it, and
then rebuild this project.

## Get the code
Use the <code>git clone</code> command to get the code. 

<code>git clone https://github.com/dkaip/jvma-natives-Linux-x86_64 jvma-natives-Linux-x86_64</code> 

This will create a <code>jvma-natives-Linux-x86_64</code> directory in your current directory


## Building
Change your current directory (<code>cd</code>) to the project root directory.  If you used the 
command above it would be <code>cd jvma-natives-Linux-x86_64</code>.    

Edit the <code>CMakeLists.txt</code> file.</br>
Alter the second arguments of the <code>set</code> statements that are 
before the <code>project</code> statement and replace the values that are 
currently there with values that are appropriate for your system / development 
environment.

Just as a side note, I was not able to debug the native code with a debugger while 
developing it.  Possibly since this code's job is to interface between code written
in Java and the code provided in the 
[Vulkan Memory Allocator Project](https://github.com/GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator). 
I had to debug the old fashioned way with print statements (<code>cout</code>), although now slf4j logging
 is available via the MACROs in the header file 
<code>slf4j.hh</code>.  These MACROs are <code>LOGINFO</code>, <code>LOGDEBUG</code>, <code>LOGTRACE</code>, 
<code>LOGWARN</code>, <code>LOGERROR</code>. The <code>Logger</code> used is 
<code>&quot;jvulkan-natives&quot;</code> 
so make sure it is configured into your <code>log4j2.xml</code>.

To produce a debug version:

<code>
mkdir Debug </br>
cd Debug </br>
cmake -DCMAKE_BUILD_TYPE=Debug .. </br>
make -j32 (You may leave out the -j option it just tells make how many cores it may use.) </code>

To produce a release version:

<code>
mkdir Release</br>
cd Release</br>
cmake -DCMAKE_BUILD_TYPE=Release ..</br>
make -j32 (You may leave out the -j option it just tells make how many cores it may use.)</br> </code>

In both of these cases the file of interest is <code>libjvma-natives-Linux-x86_64.so</code>.

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.  

Please do not reformat the source code for the existing code.  If you make additions, go ahead and format 
the source files as you like.

Please make sure to update tests as appropriate.  Note:There are no tests at the moment for this project.

In the event you are upgrading or adding to this software the command to recreate the 
JNI header file for the native functions is:

<code>javah -classpath &quot;my-jma-project-path/src/main/java:my-jvulkan-project-path/src/main/java&quot; com.CIMthetics.jvma.NativeProxies</code>

This will create the file <code>com&lowbar;CIMthetics&lowbar;jvma&lowbar;NativeProxies.h</code>  
that will need to be placed in the <code>headers</code> directory of 
the **jvma-natives-Linux-x86_64** project on your machine.  You will then need to implement 
any new functions you have added here in that project as well. 

The value of <code>&quot;my-jvma-project-path&quot;</code> will be the path to where you have the **jvma** project stored 
on your machine.

The value of <code>&quot;my-jvulkan-project-path&quot;</code> will be the path to where you have the **jvulkan** project stored 
on your machine.


## License
[Apache 2.0](http://www.apache.org/licenses/LICENSE-2.0)

Note: <code>vk&lowbar;mem&lowbar;alloc.h</code> is licensed under the MIT license.
