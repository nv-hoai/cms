#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include <iostream>
#include <stdexcept>

template <typename T>
class DoubleLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& data) : data(data), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    int size;

public:
    DoubleLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~DoubleLinkedList() {
        // clear();
    }

    void clear() {
        Node* current = head;
        while (current) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        head = tail = nullptr;
        size = 0;
    }

    int getSize() const {
        return size;
    }

    void append(const T& value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }

    T& operator[](int index) {
        if (index >= size) throw std::out_of_range("Index out of range");

        Node* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }

    const T& operator[](int index) const {
        if (index >= size) throw std::out_of_range("Index out of range");

        Node* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }

    void remove(const T& value) {
        Node* current = head;

        while (current && current->data != value) {
            current = current->next;
        }

        if (!current) return;

        if (current == head) {
            head = head->next;
            if (head) head->prev = nullptr;
            else tail = nullptr;
        } else if (current == tail) {
            tail = tail->prev;
            if (tail) tail->next = nullptr;
        } else {
            current->prev->next = current->next;
            current->next->prev = current->prev;
        }

        // delete current;
        size--;
    }


    class Iterator {
    private:
        Node* node;

    public:
        Iterator(Node* node) : node(node) {}

        T& operator*() const {
            return node->data;
        }

        Iterator& operator++() { // prefix ++
            if (node) node = node->next;
            return *this;
        }

        Iterator operator++(int) { // postfix ++
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        Iterator& operator--() { // prefix --
            if (node) node = node->prev;
            return *this;
        }

        Iterator operator--(int) { // postfix --
            Iterator temp = *this;
            --(*this);
            return temp;
        }

        bool operator==(const Iterator& other) const {
            return node == other.node;
        }

        bool operator!=(const Iterator& other) const {
            return node != other.node;
        }
    };

    Iterator begin() const {
        return Iterator(head);
    }

    Iterator end() const {
        return Iterator(nullptr);
    }
};

#endif // DOUBLELINKEDLIST_H
