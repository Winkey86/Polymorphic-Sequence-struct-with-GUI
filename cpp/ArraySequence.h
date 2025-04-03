#pragma once
#include "Sequence.h"
#include "DynamicArray.h"
#include <stdexcept>

template <class T>
class MutableArraySequence : public Sequence<T> {
private:
    DynamicArray<T> items;
public:
    MutableArraySequence();               
    MutableArraySequence(T* input, int count);
    MutableArraySequence(DynamicArray<T>& arr);
    MutableArraySequence(MutableArraySequence<T>& arr);

    virtual T GetFirst() const override;
    virtual T GetLast() const override;
    virtual T Get(int index) const override;
    virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override;
    virtual int GetLength() const override;
    virtual Sequence<T>* Append(T item) override;
    virtual Sequence<T>* Prepend(T item) override;
    virtual Sequence<T>* InsertAt(T item, int index) override;
    virtual Sequence<T>* Concat(const Sequence<T>* arr) const override;

    T& operator[](int index) {
        if (index < 0 || index >= GetLength())
            throw std::out_of_range("INDEX OUT OF RANGE");
        return items[index];
    }
    const T& operator[](int index) const {
        if (index < 0 || index >= GetLength())
            throw std::out_of_range("INDEX OUT OF RANGE");
        return items[index];
    }
};

template <class T>
class ImmutableArraySequence : public Sequence<T> {
private:
    DynamicArray<T> items;
public:
    ImmutableArraySequence();                 
    ImmutableArraySequence(T* input, int count); 
    ImmutableArraySequence(const DynamicArray<T>& arr);
    ImmutableArraySequence(const ImmutableArraySequence<T>& arr);
    
    virtual T GetFirst() const override;
    virtual T GetLast() const override;
    virtual T Get(int index) const override;
    virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override;
    virtual int GetLength() const override;
    
    virtual Sequence<T>* Append(T item) override;
    virtual Sequence<T>* Prepend(T item) override;
    virtual Sequence<T>* InsertAt(T item, int index) override;
    virtual Sequence<T>* Concat(const Sequence<T>* list) const override;

    T& operator[](int index) {
        if (index < 0 || index >= GetLength())
            throw std::out_of_range("INDEX OUT OF RANGE");
        return items[index];
    }
    const T& operator[](int index) const {
        if (index < 0 || index >= GetLength())
            throw std::out_of_range("INDEX OUT OF RANGE");
        return items[index];
    }
};
