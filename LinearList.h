#pragma once
#include "Device.h"

class LinearList {
private:
	Device* head; // Указатель на первый элемент
	Device* tail; // Указатель на последний элемент
	int size;     // Размер списка
public:
	LinearList();
	~LinearList();
	void addToStart(Device* device);
	void addToEnd(Device* device);
	void addAfterIndex(int index, Device* device);
	void removeFromStart();
	void removeFromEnd();
	void removeByIndex(int index);
	Device* findByIndex(int index);
	void clear();
	void decrementSize();
	void print() const;
	void setHead(Device* device) {
		head = device;
	}
	Device* getHead() const;
	int getSize() const;
};
