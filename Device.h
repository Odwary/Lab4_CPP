#pragma once
#include <string>
#include <ctime>
#include <iostream>

class Device {
private:
	int id;                       // Идентификационный номер
	std::string manufacturer;     // Производитель
	std::string model;            // Модель
	time_t lastCalibrationDate;   // Дата последней поверки
	double lastReading;           // Последнее показание

public:
	Device* next; // Указатель на следующий элемент списка
	Device(int id, const std::string& manufacturer, const std::string& model, time_t date, double reading);
	int getId() const;
	std::string getManufacturer() const;
	std::string getModel() const;
	time_t getLastCalibrationDate() const;
	double getLastReading() const;
	void print() const;
};