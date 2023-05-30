/*
 This file registers the device classes so Micro-Manager can identify our device.
 */

#include "DemoShutterDevice.hpp"

MODULE_API void InitializeModuleData()
{
    RegisterDevice(demo::DemoShutterDevice::NAME, MM::ShutterDevice, demo::DemoShutterDevice::DESCRIPTION);
}

MODULE_API MM::Device* CreateDevice(const char* deviceName)
{
    if (deviceName == nullptr)
        return nullptr;

    if (strcmp(deviceName, demo::DemoShutterDevice::NAME) == 0)
        return new demo::DemoShutterDevice();

    return DEVICE_OK;
}

MODULE_API void DeleteDevice(MM::Device* pDevice)
{
    delete pDevice;
}
