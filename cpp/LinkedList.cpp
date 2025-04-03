#include "LinkedList.h"

template<typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), length(0) {}

template<typename T>
void LinkedList<T>::Append(T& item) {
    Node* node = new Node(item);
    if (!head)
        head = tail = node;
    else {
        tail->next = node;
        tail = node;
    }
    length++;
}

template<typename T>
LinkedList<T>::LinkedList(T* items, int count) : head(nullptr), tail(nullptr), length(0) {
    for (int i = 0; i < count; i++)
        Append(items[i]);
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list) : head(nullptr), tail(nullptr), length(0) {
    Node* cur = list.head;
    while (cur) {
        Append(cur->data);
        cur = cur->next;
    }
}

template<typename T>
LinkedList<T>::~LinkedList() {
    while (head) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }
}

template<typename T>
T LinkedList<T>::GetFirst() const{
    if (!head)
        throw std::out_of_range("EMPTY LIST");
    return head->data;
}

template<typename T>
T LinkedList<T>::GetLast() const{
    if (!tail)
        throw std::out_of_range("EMPTY LIST");
    return tail->data;
}

template<typename T>
T LinkedList<T>::Get(int index) const{
    if (index < 0 || index >= length)
        throw std::out_of_range("INDEX OUT RANGE");
    Node* cur = head;
    for (int i = 0; i < index; i++)
        cur = cur->next;
    return cur->data;
}

template<typename T>
int LinkedList<T>::GetLength() const{
    return length;
}

template<typename T>
LinkedList<T>* LinkedList<T>::GetSubList(int startIndex, int endIndex){
    if (startIndex < 0 || endIndex >= length || startIndex > endIndex)
        throw std::out_of_range("INDEX OUT RANGE");
    LinkedList<T>* sublist = new LinkedList<T>();
    Node* cur = head;
    for (int i = 0; i < startIndex; ++i)
        cur = cur->next;
    for (int i = startIndex; i <= endIndex; i++) {
        sublist->Append(cur->data);
        cur = cur->next;
    }
    return sublist;
}

template<typename T>
void LinkedList<T>::Prepend(T& item) {
    Node* node = new Node(item);
    node->next = head;
    head = node;
    if (!tail)
        tail = node;
    length++;
}


template<typename T>
void LinkedList<T>::InsertAt(T& item, int index) {
    if (index < 0 || index > length)
        throw std::out_of_range("INDEX OUT RANGE");
    if (index == 0) {
        Prepend(item);
        return;
    }
    if (index == length) {
        Append(item);
        return;
    }
    Node* cur = head;
   for (int i=0;i<index-1;i++)
        cur=cur->next;
    Node* node=new Node(item);
    node->next=cur->next;
    cur->next=node;
    length++;
}

template<typename T>
LinkedList<T>* LinkedList<T>::Concat(LinkedList<T>* list) {
    LinkedList<T>* sum = new LinkedList<T>(*this);
    Node* cur = list->head;
    for (int i=0;i<list->length;i++){
        sum->Append(cur->data);
        cur=cur->next;
    }
    return sum;
}

template class LinkedList<int>;
