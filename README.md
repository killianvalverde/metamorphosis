### metamorphosis ###

Rename a set of files following a specified patern.
For more information, use the `metamorphosis --help` command.

### Build ###

Use the folowing commands to buil and install the CMake project:

1. Create a directory to hold the build output and generate the native build scripts:

        $ cmake -H. -Bbuild

2. Compile the project directly from CMake using the native build scripts:

        $ cmake --build build

3. Install the binary in your environment:

        $ sudo cmake --install build

### Dependencies ###

To compile this software you must use a C++ revision equal to or higher than C++17 
(ISO/IEC 14882:2017). Additionally, the following tools and libraries are required with a 
version equal to or higher than the specified one:
- GCC 8.3.0 (sudo apt-get install g++)
- CMake 3.15 (http://www.cmake.org/)
- speed 0.2.0 (https://github.com/killianvalverde/speed)
