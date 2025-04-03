#include "DynamicArray.h"
#include <algorithm>

template<class T>
DynamicArray<T>::DynamicArray(int size): data(new T[(size > 0 ? size : 1)]), cnt(0), capacity((size > 0 ? size : 1)){
    for (int i = 0; i < size; ++i)
        data[i] = T();
}

template<class T>
DynamicArray<T>::DynamicArray(T* items, int count): data(new T[(count > 0 ? count : 1)]), cnt(count), capacity(count){
    for (int i = 0; i < count; ++i)
        data[i] = items[i];
}

template<class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& dynamicArray): data(new T[dynamicArray.capacity]), cnt(dynamicArray.cnt), capacity(dynamicArray.capacity){
    for (int i = 0; i < cnt; ++i)
        data[i] = dynamicArray.data[i];
}

template<class T>
DynamicArray<T>::~DynamicArray() {
    delete[] data;
}

template<class T>
T DynamicArray<T>::Get(int index) const{
    if (index < 0 || index >= cnt)
        throw std::out_of_range("INDEX OUT RANGE");
    return data[index];
}

template<class T>
void DynamicArray<T>::Set(int index, const T& value) {
    if (index < 0 || index >= capacity)
        throw std::out_of_range("INDEX OUT RANGE");
    data[index] = value;
}

template<class T>
int DynamicArray<T>::GetSize() const{
    return cnt;
}

template<class T>
void DynamicArray<T>::Resize(int newSize) {
    if (newSize < 0)
        throw std::out_of_range("WRONG SIZE");
    T* copyArr = new T[newSize];
    int oldCount = cnt;
    if (newSize < cnt)
        cnt = newSize;
    for (int i = 0; i < oldCount && i < newSize; i++)
        copyArr[i] = data[i];
    for (int i = oldCount; i < newSize; i++)
        copyArr[i] = T();
    delete[] data;
    data = copyArr;
    capacity = newSize;
    if(newSize > oldCount)
        cnt = newSize;
}

template class DynamicArray<int>;