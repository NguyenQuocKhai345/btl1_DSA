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
        Node *next;
        Node *extra;

        Node();
        Node(const T &data, Node *next = nullptr, Node *extra = nullptr);
    };

    Node *head;
    Node *tail;
    int count;

public:
    BotkifyLinkedList() : head(nullptr), tail(nullptr), count(0) {}
    ~BotkifyLinkedList()
    {
        clear();
    }

    void add(T e)
    {
        Node *newNode = new Node(e);
        if (count == 0)
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

    void add(int index, T e)
    {
        if (index < 0 || index > count)
        {
            throw std::out_of_range("Index out of bounds");
        }
        if (index == count)
        {
            add(e);
            return;
        }
        Node *newNode = new Node(e);
        if (index == 0)
        {
            newNode->next = head;
            head = newNode;
            if (count == 0)
            {
                tail = newNode;
            }
        }
        else
        {
            Node *curr = head;
            for (int i = 0; i < index - 1; i++)
            {
                curr = curr->next;
            }
            newNode->next = curr->next;
            curr->next = newNode;
        }
        count++;
    }
    T removeAt(int index)
    {
        if (index < 0 || index >= count)
        {
            throw std::out_of_range("Index out of bounds");
        }
        Node *toDelete = head;
        T retData;
        if (index == 0)
        {
            head = head->next;
            retData = toDelete->data;
            if (count == 1)
            {
                tail = nullptr;
            }
        }
        else
        {
            Node *curr = head;
            for (int i = 0; i < index - 1; i++)
            {
                curr = curr->next;
            }
            toDelete = curr->next;
            curr->next = toDelete->next;
            retData = toDelete->data;
            if (toDelete == tail)
            {
                tail = curr;
            }
        }
        T data = toDelete->data;
        delete toDelete;
        count--;
        return data;
    }
    bool removeItem(T item)
    {
        Node *toRemove = head;
        if (head->data == item)
        {
            head = head->next;
            if (head == nullptr)
            {
                tail = nullptr;
            }
            count--;
            return true;
        }
        Node *curr = head;
        while (curr->next != nullptr)
        {
            toRemove = curr->next;
            if (toRemove->data == item)
            {
                curr->next = toRemove->next;
                if (toRemove == tail)
                {
                    tail = curr;
                }
                delete toRemove;
                count--;
                return true;
            }
            curr = curr->next;
        }
        return false;
    }

    bool empty() const { return count == 0; }
    int size() const { return count; }
    void clear()
    {
        while (head != nullptr)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        count = 0;
    }

    T &get(int index) const
    {
        if (index < 0 || index >= count)
        {
            throw std::out_of_range("Index out of bounds");
        }
        Node *curr = head;
        for (int i = 0; i < index; i++)
        {
            curr = curr->next;
        }
        return curr->data;
    }

    string toString() const
    {
        stringstream ss;
        Node *curr = head;
        while (curr != nullptr)
        {
            ss << curr->data->toString();
            if (curr->next != nullptr)
            {
                ss << ",";
            }
            curr = curr->next;
        }
        return ss.str();
    }
};

#endif // BOTKIFY_LINKED_LIST_H
