#pragma once
#include <string>
#include <ctime>
#include <iostream>

class Device {
private:
	int id;                       // ����������������� �����
	std::string manufacturer;     // �������������
	std::string model;            // ������
	time_t lastCalibrationDate;   // ���� ��������� �������
	double lastReading;           // ��������� ���������

public:
	Device* next; // ��������� �� ��������� ������� ������
	Device(int id, const std::string& manufacturer, const std::string& model, time_t date, double reading);
	int getId() const;
	std::string getManufacturer() const;
	std::string getModel() const;
	time_t getLastCalibrationDate() const;
	double getLastReading() const;
	void print() const;
};