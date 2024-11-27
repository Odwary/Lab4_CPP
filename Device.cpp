#include "Device.h"

Device::Device(int id, const std::string& manufacturer, const std::string& model, time_t date, double reading)
    : id(id), manufacturer(manufacturer), model(model), lastCalibrationDate(date), lastReading(reading), next(nullptr) {}

int Device::getId() const { return id; }
std::string Device::getManufacturer() const { return manufacturer; }
std::string Device::getModel() const { return model; }
time_t Device::getLastCalibrationDate() const { return lastCalibrationDate; }
double Device::getLastReading() const { return lastReading; }

void Device::print() const {
    std::cout << "ID: " << id
        << ", Производитель: " << manufacturer
        << ", Модель: " << model
        << ", Последняя дата поверки: " << ctime(&lastCalibrationDate)
        << ", Последнее показание: " << lastReading << std::endl;
}