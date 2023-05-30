# CMAKE project for Micro-Manager device adapters

This is a minimum working example on how to manage a Micro-manager device adapter using CMake.
It's not intended to show any advanced or "correct" CMake features or project structures.
Instead, the goal is to demonstrate the minimum viable code needed to manage a working device adapter project
using CMake.

## Requirements

### Micro-Manager source code
You'll need to download Micro-Manager's source code.
You can find information on how to do that [here](https://micro-manager.org/Micro-Manager_Source_Code), 
but we advise using the [separate Micro-Manager 2.0 repository](https://github.com/micro-manager/mmCoreAndDevices)
for device adapters.

### Set an environmental property

This project was designed to use an environmental property (`MM_SOURCE`) pointing to the root of the source code.
You'll need to set that property pointing to the top level Micro-Manager source folder.
This will be the folder containing a `MMDevice` folder, 
which will be slightly different whether you are using 1.4 or 2.0.

* `1.4`: If you've pulled the subversion repository,
         then it should be the folder you pulled to, appended with `trunk`.
* `2.0`: 
  * If you've pulled and initialized the main git repository,
           then it should be the folder you pulled to, appended with `mmCoreAndDevices`.
  * Otherwise, if you've only pulled the separate repository for device adapters,
    you only need to set the variable to that folder.

#### MM Device API interface version

Aside from the major 1.4/2.0 versions,
the device adapter interface has its own version number.
To find out which version applies to the source code you are using,
look at `DEVICE_INTERFACE_VERSION` in `MMDevice.h`.
If you pulled the latest source code, 
this version is likely incompatible with the latest stable release of Micro-Manager
and is only compatible with the latest nightly builds.
If you'd like to use the latest stable one,
look at the release tags in the
[separate Micro-Manager 2.0 repository](https://github.com/micro-manager/mmCoreAndDevices/tags)

## Build instructions

* Tell CMake to generate your build files with `cmake -S . -B build`.
  This will generate the build files under a folder called `build`.
  This can be changed to another folder name of your choice.
* Compile your device adapter with `cmake --build build`,
  or change the last argument to where you told CMake to generate the build files.