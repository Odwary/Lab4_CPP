#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <Windows.h>
#include "Container.h"
//5. Информация о приборах учета: идентификационный номер, производитель,
//модель, дата последней поверки, последнее показание.
//Методы Контейнера :
//•Получить список всех приборов учета с датой поверки не позже заданной,
//имеющих заданную модель.
//• Получить список всех приборов учета, показание которых ниже
//заданного, имеющих заданного производителя.При этом удалить
//выбранные товары из Контейнера.
//• Упорядочить товары по дате поверки, производителю, модели.


// Функция для разбора даты из строки
time_t parseDate(const std::string& dateStr);

// Вывод меню программы
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
            std::cout << "Неверный пункт меню\n";
            continue;
        } 
        try {
            switch (choice) {
            case 1: {
                // Добавить в начало
                int id;
                std::string manufacturer, model, dateStr;
                double reading;
                std::cout << "Введите идентификационный номер: ";
                std::cin >> id;
                std::cin.ignore();
                std::cout << "Введите производителя: ";
                std::getline(std::cin, manufacturer);
                std::cout << "Введите модель: ";
                std::getline(std::cin, model);
                std::cout << "Введите дату последней поверки (YYYY-MM-DD): ";
                std::getline(std::cin, dateStr);
                std::cout << "Введите последнее показание: ";
                std::cin >> reading;
                time_t lastCalibrationDate = parseDate(dateStr);
                Device* device = new Device(id, manufacturer, model, lastCalibrationDate, reading);
                container.getList().addToStart(device);
                std::cout << "Элемент добавлен в начало.\n";
                break;
            }
            case 2: {
                // Добавить в конец
                int id;
                std::string manufacturer, model, dateStr;
                double reading;
                std::cout << "Введите идентификационный номер: ";
                std::cin >> id;
                std::cin.ignore();
                std::cout << "Введите производителя: ";
                std::getline(std::cin, manufacturer);
                std::cout << "Введите модель: ";
                std::getline(std::cin, model);
                std::cout << "Введите дату последней поверки (YYYY-MM-DD): ";
                std::getline(std::cin, dateStr);
                std::cout << "Введите последнее показание: ";
                std::cin >> reading;
                time_t lastCalibrationDate = parseDate(dateStr);
                Device* device = new Device(id, manufacturer, model, lastCalibrationDate, reading);
                container.getList().addToEnd(device);
                std::cout << "Элемент добавлен в конец.\n";
                break;
            }
            case 3: {
                // Добавить за указанным номером
                int id, index;
                std::string manufacturer, model, dateStr;
                double reading;
                std::cout << "Введите индекс для вставки после: ";
                std::cin >> index;
                std::cin.ignore();
                std::cout << "Введите идентификационный номер: ";
                std::cin >> id;
                std::cin.ignore();
                std::cout << "Введите производителя: ";
                std::getline(std::cin, manufacturer);
                std::cout << "Введите модель: ";
                std::getline(std::cin, model);
                std::cout << "Введите дату последней поверки (YYYY-MM-DD): ";
                std::getline(std::cin, dateStr);
                std::cout << "Введите последнее показание: ";
                std::cin >> reading;

                time_t lastCalibrationDate = parseDate(dateStr);
                Device* device = new Device(id, manufacturer, model, lastCalibrationDate, reading);
                container.getList().addAfterIndex(index, device);
                std::cout << "Элемент добавлен после индекса " << index << ".\n";
                break;
            }
            case 4:
                container.getList().removeFromStart();
                std::cout << "Элемент удален из начала.\n";
                break;
            case 5:
                container.getList().removeFromEnd();
                std::cout << "Элемент удален из конца.\n";
                break;
            case 6: {
                int index;
                std::cout << "Введите индекс для удаления: ";
                std::cin >> index;
                container.getList().removeByIndex(index);
                std::cout << "Элемент удален.\n";
                break;
            }
            case 7: {
                int index;
                std::cout << "Введите индекс для поиска: ";
                std::cin >> index;
                Device* device = container.getList().findByIndex(index);
                if (device) {
                    std::cout << "Найденный элемент:\n";
                    device->print();
                }
                else {
                    std::cout << "Элемент с таким индексом не найден.\n";
                }
                break;
            }
            case 8:
                container.getList().clear();
                std::cout << "Все элементы удалены.\n";
                break;
            case 9:
                container.getList().print();
                break;
            case 10: {
                std::string model, dateStr;
                std::cout << "Введите модель: ";
                std::cin.ignore();
                std::getline(std::cin, model);
                std::cout << "Введите дату (YYYY-MM-DD): ";
                std::getline(std::cin, dateStr);

                time_t maxDate = parseDate(dateStr);
                container.getDevicesByModelAndDate(model, maxDate);
                break;
            }
            case 11: {
                std::string manufacturer;
                double maxReading;
                container.printDevices();
                std::cout << "Введите производителя: ";
                std::cin.ignore();
                std::getline(std::cin, manufacturer);
                std::cout << "Введите максимальное показание: ";
                std::cin >> maxReading;
                container.removeDevicesByManufacturerAndReading(manufacturer, maxReading);
                container.printDevices();
                break;
            }
            case 12:
                container.sortDevices();
                std::cout << "Приборы упорядочены.\n";
                break;
            case 13:
                std::cout << "Выход из программы.\n";
                break;
            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
            }
        }
        catch (const std::exception& ex) {
            std::cout << "Ошибка: " << ex.what() << '\n';
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
    // Устанавливаем время на полночь
    timeStruct.tm_hour = 0;
    timeStruct.tm_min = 0;
    timeStruct.tm_sec = 0;
    return std::mktime(&timeStruct);
}

void printMenu()
{
    std::cout << "\nМеню:\n";
    std::cout << "1. Добавить в начало\n";
    std::cout << "2. Добавить в конец\n";
    std::cout << "3. Добавить за указанным номером\n";
    std::cout << "4. Удалить из начала\n";
    std::cout << "5. Удалить из конца\n";
    std::cout << "6. Удалить элемент по номеру\n";
    std::cout << "7. Найти элемент по номеру\n";
    std::cout << "8. Удалить все элементы\n";
    std::cout << "9. Вывести все элементы\n";
    std::cout << "10. Получить список приборов с датой поверки не позже заданной и заданной моделью\n";
    std::cout << "11. Получить список и удалить приборы с показанием ниже заданного и заданным производителем\n";
    std::cout << "12. Упорядочить приборы по дате поверки, производителю, модели\n";
    std::cout << "13. Выход\n";
    std::cout << "Выберите действие: ";
}
