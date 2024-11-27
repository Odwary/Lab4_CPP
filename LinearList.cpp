#include "LinearList.h"

LinearList::LinearList() : head(nullptr), tail(nullptr), size(0) {}

LinearList::~LinearList() {
    clear();
}

void LinearList::addToStart(Device* device) {
    if (head == nullptr) {
        head = tail = device;
    }
    else {
        device->next = head;
        head = device;
    }
    size++;
}

void LinearList::addToEnd(Device* device) {
    if (tail == nullptr) {
        head = tail = device;
    }
    else {
        tail->next = device;
        tail = device;
    }
    size++;
}

void LinearList::addAfterIndex(int index, Device* device) {
    if (index < 0 || index >= size) return;
    Device* current = head;
    for (int i = 0; i < index; i++) current = current->next;
    device->next = current->next;
    current->next = device;
    if (current == tail) tail = device;
    size++;
}

void LinearList::removeFromStart() {
    if (head == nullptr) return;
    Device* temp = head;
    head = head->next;
    delete temp;
    size--;
    if (head == nullptr) tail = nullptr;
}

void LinearList::removeFromEnd() {
    if (tail == nullptr) return;
    if (head == tail) {
        delete head;
        head = tail = nullptr;
    }
    else {
        Device* current = head;
        while (current->next != tail) current = current->next;
        delete tail;
        tail = current;
        current->next = nullptr;
    }
    size--;
}

void LinearList::removeByIndex(int index) {
    if (index < 0 || index >= size) return;
    if (index == 0) {
        removeFromStart();
        return;
    }
    Device* current = head;
    for (int i = 0; i < index - 1; i++) current = current->next;
    Device* temp = current->next;
    current->next = temp->next;
    if (temp == tail) tail = current;
    delete temp;
    size--;
}

Device* LinearList::findByIndex(int index) {
    if (index < 0 || index >= size) {
        return nullptr; 
    }
    Device* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current;
}

void LinearList::clear() {
    while (head != nullptr) removeFromStart();
}

void LinearList::decrementSize() {
    if (size > 0) size--;
}

void LinearList::print() const {
    Device* current = head;
    while (current != nullptr) {
        current->print();
        current = current->next;
    }
}

Device* LinearList::getHead() const { return head; }
int LinearList::getSize() const { return size; }