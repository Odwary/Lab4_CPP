#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <Windows.h>
#include "Container.h"
//5. ���������� � �������� �����: ����������������� �����, �������������,
//������, ���� ��������� �������, ��������� ���������.
//������ ���������� :
//��������� ������ ���� �������� ����� � ����� ������� �� ����� ��������,
//������� �������� ������.
//� �������� ������ ���� �������� �����, ��������� ������� ����
//���������, ������� ��������� �������������.��� ���� �������
//��������� ������ �� ����������.
//� ����������� ������ �� ���� �������, �������������, ������.


// ������� ��� ������� ���� �� ������
time_t parseDate(const std::string& dateStr);

// ����� ���� ���������
void printMenu();

int main() {
    setlocale(LC_ALL, "Russian");
    Container container;
    int choice{};
    do {
        printMenu();
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "�������� ����� ����\n";
            continue;
        } 
        try {
            switch (choice) {
            case 1: {
                // �������� � ������
                int id;
                std::string manufacturer, model, dateStr;
                double reading;
                std::cout << "������� ����������������� �����: ";
                std::cin >> id;
                std::cin.ignore();
                std::cout << "������� �������������: ";
                std::getline(std::cin, manufacturer);
                std::cout << "������� ������: ";
                std::getline(std::cin, model);
                std::cout << "������� ���� ��������� ������� (YYYY-MM-DD): ";
                std::getline(std::cin, dateStr);
                std::cout << "������� ��������� ���������: ";
                std::cin >> reading;
                time_t lastCalibrationDate = parseDate(dateStr);
                Device* device = new Device(id, manufacturer, model, lastCalibrationDate, reading);
                container.getList().addToStart(device);
                std::cout << "������� �������� � ������.\n";
                break;
            }
            case 2: {
                // �������� � �����
                int id;
                std::string manufacturer, model, dateStr;
                double reading;
                std::cout << "������� ����������������� �����: ";
                std::cin >> id;
                std::cin.ignore();
                std::cout << "������� �������������: ";
                std::getline(std::cin, manufacturer);
                std::cout << "������� ������: ";
                std::getline(std::cin, model);
                std::cout << "������� ���� ��������� ������� (YYYY-MM-DD): ";
                std::getline(std::cin, dateStr);
                std::cout << "������� ��������� ���������: ";
                std::cin >> reading;
                time_t lastCalibrationDate = parseDate(dateStr);
                Device* device = new Device(id, manufacturer, model, lastCalibrationDate, reading);
                container.getList().addToEnd(device);
                std::cout << "������� �������� � �����.\n";
                break;
            }
            case 3: {
                // �������� �� ��������� �������
                int id, index;
                std::string manufacturer, model, dateStr;
                double reading;
                std::cout << "������� ������ ��� ������� �����: ";
                std::cin >> index;
                std::cin.ignore();
                std::cout << "������� ����������������� �����: ";
                std::cin >> id;
                std::cin.ignore();
                std::cout << "������� �������������: ";
                std::getline(std::cin, manufacturer);
                std::cout << "������� ������: ";
                std::getline(std::cin, model);
                std::cout << "������� ���� ��������� ������� (YYYY-MM-DD): ";
                std::getline(std::cin, dateStr);
                std::cout << "������� ��������� ���������: ";
                std::cin >> reading;

                time_t lastCalibrationDate = parseDate(dateStr);
                Device* device = new Device(id, manufacturer, model, lastCalibrationDate, reading);
                container.getList().addAfterIndex(index, device);
                std::cout << "������� �������� ����� ������� " << index << ".\n";
                break;
            }
            case 4:
                container.getList().removeFromStart();
                std::cout << "������� ������ �� ������.\n";
                break;
            case 5:
                container.getList().removeFromEnd();
                std::cout << "������� ������ �� �����.\n";
                break;
            case 6: {
                int index;
                std::cout << "������� ������ ��� ��������: ";
                std::cin >> index;
                container.getList().removeByIndex(index);
                std::cout << "������� ������.\n";
                break;
            }
            case 7: {
                int index;
                std::cout << "������� ������ ��� ������: ";
                std::cin >> index;
                Device* device = container.getList().findByIndex(index);
                if (device) {
                    std::cout << "��������� �������:\n";
                    device->print();
                }
                else {
                    std::cout << "������� � ����� �������� �� ������.\n";
                }
                break;
            }
            case 8:
                container.getList().clear();
                std::cout << "��� �������� �������.\n";
                break;
            case 9:
                container.getList().print();
                break;
            case 10: {
                std::string model, dateStr;
                std::cout << "������� ������: ";
                std::cin.ignore();
                std::getline(std::cin, model);
                std::cout << "������� ���� (YYYY-MM-DD): ";
                std::getline(std::cin, dateStr);

                time_t maxDate = parseDate(dateStr);
                container.getDevicesByModelAndDate(model, maxDate);
                break;
            }
            case 11: {
                std::string manufacturer;
                double maxReading;
                container.printDevices();
                std::cout << "������� �������������: ";
                std::cin.ignore();
                std::getline(std::cin, manufacturer);
                std::cout << "������� ������������ ���������: ";
                std::cin >> maxReading;
                container.removeDevicesByManufacturerAndReading(manufacturer, maxReading);
                container.printDevices();
                break;
            }
            case 12:
                container.sortDevices();
                std::cout << "������� �����������.\n";
                break;
            case 13:
                std::cout << "����� �� ���������.\n";
                break;
            default:
                std::cout << "�������� �����. ���������� �����.\n";
            }
        }
        catch (const std::exception& ex) {
            std::cout << "������: " << ex.what() << '\n';
        }
    } while (choice != 13);
    return 0;
}

time_t parseDate(const std::string& dateStr)
{
    std::tm timeStruct = {};
    std::istringstream ss(dateStr);
    ss >> std::get_time(&timeStruct, "%Y-%m-%d");
    if (ss.fail()) {
        throw std::invalid_argument("Invalid date format. Use YYYY-MM-DD.");
    }
    // ������������� ����� �� �������
    timeStruct.tm_hour = 0;
    timeStruct.tm_min = 0;
    timeStruct.tm_sec = 0;
    return std::mktime(&timeStruct);
}

void printMenu()
{
    std::cout << "\n����:\n";
    std::cout << "1. �������� � ������\n";
    std::cout << "2. �������� � �����\n";
    std::cout << "3. �������� �� ��������� �������\n";
    std::cout << "4. ������� �� ������\n";
    std::cout << "5. ������� �� �����\n";
    std::cout << "6. ������� ������� �� ������\n";
    std::cout << "7. ����� ������� �� ������\n";
    std::cout << "8. ������� ��� ��������\n";
    std::cout << "9. ������� ��� ��������\n";
    std::cout << "10. �������� ������ �������� � ����� ������� �� ����� �������� � �������� �������\n";
    std::cout << "11. �������� ������ � ������� ������� � ���������� ���� ��������� � �������� ��������������\n";
    std::cout << "12. ����������� ������� �� ���� �������, �������������, ������\n";
    std::cout << "13. �����\n";
    std::cout << "�������� ��������: ";
}
