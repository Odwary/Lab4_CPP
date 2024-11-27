#pragma once
#include "LinearList.h"
#include <string>

class Container {
private:
    LinearList list;
public:
    void addDevice(const Device& device);
    void getDevicesByModelAndDate(const std::string& model, time_t date);
    void removeDevicesByManufacturerAndReading(const std::string& manufacturer, double maxReading);
    void sortDevices();
    void printDevices() const;
    LinearList& getList();
};

