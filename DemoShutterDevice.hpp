#ifndef CMAKE_TUTORIAL_DEMO_DEVICE_H
#define CMAKE_TUTORIAL_DEMO_DEVICE_H

#include <DeviceBase.h>
#include "MMDevice.h"

namespace demo {
    class DemoShutterDevice : public CShutterBase<DemoShutterDevice> {
    public:
        explicit DemoShutterDevice() = default;
        ~DemoShutterDevice() override = default;

        inline static const char* NAME = "CMade shutter";
        inline static const char* DESCRIPTION = "A mock device adapter whose code can be managed by CMake";

        // MMDevice API
        int Initialize() override {
            return DEVICE_OK;
        }

        int Shutdown() override {
            return DEVICE_OK;
        }

        // MM Shutter device API
        bool Busy() override {
            return false;
        }

        void GetName(char * name) const override;
        int SetOpen(bool open) override;
        int GetOpen(bool & open) override;
        int Fire(double deltaT) override;

    private:
        bool state = false;
    };
}

#endif //CMAKE_TUTORIAL_DEMO_DEVICE_H
