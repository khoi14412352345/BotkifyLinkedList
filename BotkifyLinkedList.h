#ifndef BOTKIFY_LINKED_LIST_H
#define BOTKIFY_LINKED_LIST_H

#include "main.h"

template <class T>
class BotkifyLinkedList
{
private:
    class Node
    {
    public:
        T data;
        Node* next;
        Node* extra;

        Node();
        Node(const T& data, Node* next = nullptr, Node* extra = nullptr);
    };

    Node* head;
    Node* tail;
    int count;

public:
    BotkifyLinkedList();
    ~BotkifyLinkedList();

    void add(T e);
    void add(int index, T e);
    T removeAt(int index);
    bool removeItem(T item);

    bool empty() const;
    int size() const;
    void clear();

    T& get(int index) const;

    string toString() const;
};

// ==================== Template Implementation ====================

template <class T>
BotkifyLinkedList<T>::Node::Node()
    : data(T()), next(nullptr), extra(nullptr) {}

template <class T>
BotkifyLinkedList<T>::Node::Node(const T& data, Node* next, Node* extra)
    : data(data), next(next), extra(extra) {}

template <class T>
BotkifyLinkedList<T>::BotkifyLinkedList()
    : head(nullptr), tail(nullptr), count(0) {}

template <class T>
BotkifyLinkedList<T>::~BotkifyLinkedList()
{
    clear();
}

template <class T>
void BotkifyLinkedList<T>::add(T e)
{
    Node* newNode = new Node(e);
    if (head == nullptr)
    {
        head = tail = newNode;
    }
    else
    {
        tail->next = newNode;
        tail = newNode;
    }
    count++;
}

template <class T>
void BotkifyLinkedList<T>::add(int index, T e)
{
    if (index < 0 || index > count)
    {
        throw out_of_range("Index is invalid!");
    }

    Node* newNode = new Node(e);

    if (index == 0)
    {
        newNode->next = head;
        head = newNode;
        if (tail == nullptr)
        {
            tail = newNode;
        }
    }
    else if (index == count)
    {
        tail->next = newNode;
        tail = newNode;
    }
    else
    {
        Node* current = head;
        for (int i = 0; i < index - 1; i++)
        {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    count++;
}

template <class T>
T BotkifyLinkedList<T>::removeAt(int index)
{
    if (index < 0 || index >= count || head == nullptr)
    {
        throw out_of_range("Index is invalid!");
    }

    Node* toRemove;
    T data;

    if (index == 0)
    {
        toRemove = head;
        head = head->next;
        if (head == nullptr)
        {
            tail = nullptr;
        }
    }
    else
    {
        Node* current = head;
        for (int i = 0; i < index - 1; i++)
        {
            current = current->next;
        }
        toRemove = current->next;
        current->next = toRemove->next;
        if (toRemove == tail)
        {
            tail = current;
        }
    }

    data = toRemove->data;
    delete toRemove;
    count--;
    return data;
}

template <class T>
bool BotkifyLinkedList<T>::removeItem(T item)
{
    Node* current = head;
    Node* prev = nullptr;

    while (current != nullptr)
    {
        if (current->data == item)
        {
            if (prev == nullptr)
            {
                head = current->next;
                if (head == nullptr)
                {
                    tail = nullptr;
                }
            }
            else
            {
                prev->next = current->next;
                if (current == tail)
                {
                    tail = prev;
                }
            }
            delete current;
            count--;
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

template <class T>
bool BotkifyLinkedList<T>::empty() const
{
    return count == 0;
}

template <class T>
int BotkifyLinkedList<T>::size() const
{
    return count;
}

template <class T>
void BotkifyLinkedList<T>::clear()
{
    while (head != nullptr)
    {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    count = 0;
}

template <class T>
T& BotkifyLinkedList<T>::get(int index) const
{
    if (index < 0 || index >= count)
    {
        throw out_of_range("Index is invalid!");
    }

    Node* current = head;
    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }
    return current->data;
}

template <class T>
string BotkifyLinkedList<T>::toString() const
{
    if (count == 0)
    {
        return "";
    }

    stringstream ss;
    Node* current = head;

    while (current != nullptr)
    {
        ss << current->data;
        if (current->next != nullptr)
        {
            ss << ",";
        }
        current = current->next;
    }

    return ss.str();
}

#endif // BOTKIFY_LINKED_LIST_H
