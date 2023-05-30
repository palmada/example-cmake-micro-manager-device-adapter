cmake_minimum_required(VERSION 3.23)

project(DeviceAdapter
        VERSION 0.1
        DESCRIPTION "An example Micro-Manager device adapter project with CMake"
        LANGUAGES CXX)

# Micro-Manager's code makes heavy use of dynamic exceptions, which MSVC doesn't complain about.
# Other compilers, however, enforce the C++ standard which has deprecated dynamic exceptions since C++17
set(CMAKE_CXX_STANDARD 14)

# Save our binaries to the `libraries` folder, so they are easier to find
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/device_adapters")

# This line creates a new device adapter project (CMake calls these `targets`) called `DeviceAdapter`
# This name will be used later to set properties for our project.
# For now, we're telling it which files to use.
add_library(DeviceAdapter SHARED MMApi.cpp DemoShutterDevice.cpp DemoShutterDevice.hpp)

# Using C++ 14. Same reason as above.
target_compile_features(DeviceAdapter PUBLIC cxx_std_14)

# Make our headers available to callers of the DLL
target_include_directories(DeviceAdapter PUBLIC .)

# Micro-manager dll files require the "mmgr_dal_" prefix.
# The resulting DLL file will be called "mmgr_dal_DeviceAdapter" since CMake will append the target name we set above.
set_target_properties(DeviceAdapter PROPERTIES PREFIX "mmgr_dal_")

# The next block of code will create a micro-manager target that can be used by our DLL

# Load the micro-manager source folder, after parsing the back-slashes
string(REPLACE "\\" "/" MM_SOURCE $ENV{MM_SOURCE}/MMDevice)
message(STATUS "Micro-manager source: ${MM_SOURCE}")

# Find the source files in Micro-Manager's source
file(GLOB SOURCES "${MM_SOURCE}/*.cpp")
file(GLOB HEADERS "${MM_SOURCE}/*.h")

# Create a Micro-Manager target including all of the source files we found above
add_library(Micro-Manager STATIC ${SOURCES} ${HEADERS})
target_compile_features(Micro-Manager PUBLIC cxx_std_14)
target_include_directories(Micro-Manager PUBLIC ${MM_SOURCE})

# Micro-manager's source uses this flag to define the DLL exported functions
add_compile_definitions(MODULE_EXPORTS)

# This is required to compile correctly with non-MSVC compilers, since Micro-Manager defines it's own timezone struct
# Luckily if you pass this flag, the Micro-Manager macros skip that step.
if (NOT CMAKE_CXX_COMPILER_IDN STREQUAL "MSVC")
    add_compile_definitions(MMDEVICE_NO_GETTIMEOFDAY)
endif()

# We now link our DeviceAdapter with Micro-Manager
target_link_libraries(DeviceAdapter PUBLIC Micro-Manager)