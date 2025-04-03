#pragma once
#include <stdexcept>

template<typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };
    Node* head;
    Node* tail;
    int length;
public:
    LinkedList();                                  
    LinkedList(T* items, int count);               
    LinkedList(const LinkedList<T>& list);        

    ~LinkedList();

    T GetFirst() const;                     
    T GetLast() const;                           
    T Get(int index) const;                      
    LinkedList<T>* GetSubList(int startIndex, int endIndex);  
    int GetLength() const;                      
    void Append(T& item);                    
    void Prepend(T& item);                  
    void InsertAt(T& item, int index);    
    LinkedList<T>* Concat(LinkedList<T>* list);  

    T& operator[](int index) {
        if (index < 0 || index >= GetLength())
            throw std::out_of_range("INDEX OUT OF RANGE");
        Node* current = head;
        for (int i = 0; i < index; i++)
            current = current->next;
        return current->data;
    }
    const T& operator[](int index) const {
        if (index < 0 || index >= GetLength())
            throw std::out_of_range("INDEX OUT OF RANGE");
        Node* current = head;
        for (int i = 0; i < index; i++)
            current = current->next;
        return current->data;
    }
};
