#include "Container.h"
#include <algorithm>

void Container::addDevice(const Device& device) {
    Device* newDevice = new Device(device);
    list.addToEnd(newDevice);
}

void Container::getDevicesByModelAndDate(const std::string& model, time_t date) {
    Device* current = list.getHead();
    while (current != nullptr) {
        if (current->getModel() == model && current->getLastCalibrationDate() <= date) {
            current->print();
        }
        current = current->next;
    }
}

void Container::removeDevicesByManufacturerAndReading(const std::string& manufacturer, double maxReading) {
    Device* current = list.getHead();
    Device* prev = nullptr;
    while (current != nullptr) {
        if (current->getManufacturer() == manufacturer && current->getLastReading() < maxReading) {
            Device* temp = current;
            if (prev == nullptr) { // Удаляем первый элемент
                list.setHead(current->next);
            }
            else {
                prev->next = current->next;
            }
            current = current->next;
            delete temp;
            list.decrementSize();
        }
        else {
            prev = current;
            current = current->next;
        }
    }
}

void Container::sortDevices() {
    if (list.getSize() < 2) return;
    bool swapped;
    do {
        swapped = false;
        Device* prev = nullptr;
        Device* current = list.getHead();
        while (current != nullptr && current->next != nullptr) {
            Device* next = current->next;
            if (current->getLastCalibrationDate() > next->getLastCalibrationDate() ||
                (current->getLastCalibrationDate() == next->getLastCalibrationDate() &&
                    current->getManufacturer() > next->getManufacturer()) ||
                (current->getLastCalibrationDate() == next->getLastCalibrationDate() &&
                    current->getManufacturer() == next->getManufacturer() &&
                    current->getModel() > next->getModel())) {
                // Переставляем указатели
                if (prev == nullptr) {
                    list.setHead(next);
                }
                else {
                    prev->next = next;
                }
                current->next = next->next;
                next->next = current;
                swapped = true;
            }
            prev = current;
            current = current->next;
        }
    } while (swapped);
}

void Container::printDevices() const {
    list.print();
}

LinearList& Container::getList()
{
    return list;
}
