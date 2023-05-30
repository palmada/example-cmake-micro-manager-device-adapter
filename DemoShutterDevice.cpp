#include <iostream>
#include "MMDevice.h"
#include "DemoShutterDevice.hpp"

namespace demo {

    void demo::DemoShutterDevice::GetName(char* name) const {
        assert(strlen(DemoShutterDevice::NAME) < CDeviceUtils::GetMaxStringLength());
        CDeviceUtils::CopyLimitedString(name, DemoShutterDevice::NAME);
    }

    int demo::DemoShutterDevice::SetOpen(bool open) {
        this->state = open;
        LogMessage("Setting shutter to: " + std::to_string(open));
        return DEVICE_OK;
    }

    int demo::DemoShutterDevice::GetOpen(bool &open) {
        open = this->state;
        return DEVICE_OK;
    }

    int demo::DemoShutterDevice::Fire(double deltaT) {
        return DEVICE_OK;
    }
}