#include "ArraySequence.h"
#include <stdexcept>

template <class T>
MutableArraySequence<T>::MutableArraySequence(): items(50){}

template <class T>
MutableArraySequence<T>::MutableArraySequence(T* input, int count): items(input, count){}

template <class T>
MutableArraySequence<T>::MutableArraySequence(DynamicArray<T>& arr): items(arr) {}

template <class T>
MutableArraySequence<T>::MutableArraySequence(MutableArraySequence<T>& arr): items(arr.items){}

template <class T>
T MutableArraySequence<T>::GetFirst() const {
    if (const_cast<DynamicArray<T>&>(items).GetSize() == 0)
        throw std::out_of_range("EMPTY SEQUENCE");
    return const_cast<DynamicArray<T>&>(items).Get(0);
}

template <class T>
T MutableArraySequence<T>::GetLast() const {
    int s = const_cast<DynamicArray<T>&>(items).GetSize();
    if (s == 0)
        throw std::out_of_range("EMPTY SEQUENCE");
    return const_cast<DynamicArray<T>&>(items).Get(s - 1);
}

template <class T>
T MutableArraySequence<T>::Get(int index) const {
    if (index < 0 || index >= const_cast<DynamicArray<T>&>(items).GetSize())
        throw std::out_of_range("INDEX OUT RANGE");
    return const_cast<DynamicArray<T>&>(items).Get(index);
}

template <class T>
int MutableArraySequence<T>::GetLength() const {
    return const_cast<DynamicArray<T>&>(items).GetSize();
}

template <class T>
Sequence<T>* MutableArraySequence<T>::GetSubsequence(int startIndex, int endIndex) const {
    if (startIndex < 0 || endIndex >= const_cast<DynamicArray<T>&>(items).GetSize() || startIndex > endIndex)
        throw std::out_of_range("INDEX OUT RANGE");
    int count = endIndex - startIndex + 1;
    T* subArr = new T[count];
    for (int i = 0; i < count; i++)
        subArr[i] = const_cast<DynamicArray<T>&>(items).Get(startIndex + i);
    Sequence<T>* subSeq = new MutableArraySequence<T>(subArr, count);
    delete[] subArr;
    return subSeq;
}

template <class T>
Sequence<T>* MutableArraySequence<T>::Append(T item) {
    int length = items.GetSize();
    items.Resize(length + 1);
    items.Set(length, item);
    return this;
}

template <class T>
Sequence<T>* MutableArraySequence<T>::Prepend(T item) {
    int length = items.GetSize();
    items.Resize(length + 1);
    for (int i = length; i > 0; i--) {
        items.Set(i, items.Get(i - 1));
    }
    items.Set(0, item);
    return this;
}

template <class T>
Sequence<T>* MutableArraySequence<T>::InsertAt(T item, int index) {
    int length = items.GetSize();
    if (index < 0 || index > length)
        throw std::out_of_range("INDEX OUT RANGE");
    items.Resize(length + 1);
    for (int i = length; i > index; i--) {
        items.Set(i, items.Get(i - 1));
    }
    items.Set(index, item);
    return this;
}

template <class T>
Sequence<T>* MutableArraySequence<T>::Concat(const Sequence<T>* seq) const {
    int length1 = const_cast<DynamicArray<T>&>(items).GetSize();
    int length2 = seq->GetLength();
    T* newArr = new T[length1 + length2];
    for (int i = 0; i < length1; i++)
        newArr[i] = const_cast<DynamicArray<T>&>(items).Get(i);
    for (int i = 0; i < length2; i++)
        newArr[length1 + i] = seq->Get(i);
    Sequence<T>* sum = new MutableArraySequence<T>(newArr, length1 + length2);
    delete[] newArr;
    return sum;
}

template <class T>
ImmutableArraySequence<T>::ImmutableArraySequence(): items(50){}

template <class T>
ImmutableArraySequence<T>::ImmutableArraySequence(T* input, int count): items(input, count){}

template <class T>
ImmutableArraySequence<T>::ImmutableArraySequence(const DynamicArray<T>& arr): items((DynamicArray<T>&)arr) {}

template <class T>
ImmutableArraySequence<T>::ImmutableArraySequence(const ImmutableArraySequence<T>& arr): items(arr.items){}

template <class T>
T ImmutableArraySequence<T>::GetFirst() const {
    if (const_cast<DynamicArray<T>&>(items).GetSize() == 0)
        throw std::out_of_range("EMPTY SEQUENCE");
    return const_cast<DynamicArray<T>&>(items).Get(0);
}

template <class T>
T ImmutableArraySequence<T>::GetLast() const {
    int s = const_cast<DynamicArray<T>&>(items).GetSize();
    if (s == 0)
        throw std::out_of_range("EMPTY SEQUENCE");
    return const_cast<DynamicArray<T>&>(items).Get(s - 1);
}

template <class T>
T ImmutableArraySequence<T>::Get(int index) const {
    if (index < 0 || index >= const_cast<DynamicArray<T>&>(items).GetSize())
        throw std::out_of_range("INDEX OUT RANGE");
    return const_cast<DynamicArray<T>&>(items).Get(index);
}

template <class T>
int ImmutableArraySequence<T>::GetLength() const {
    return const_cast<DynamicArray<T>&>(items).GetSize();
}

template <class T>
Sequence<T>* ImmutableArraySequence<T>::GetSubsequence(int startIndex, int endIndex) const {
    if (startIndex < 0 || endIndex >= const_cast<DynamicArray<T>&>(items).GetSize() || startIndex > endIndex)
        throw std::out_of_range("INDEX OUT RANGE");
    int count = endIndex - startIndex + 1;
    T* subArr = new T[count];
    for (int i = 0; i < count; i++)
        subArr[i] = const_cast<DynamicArray<T>&>(items).Get(startIndex + i);
    Sequence<T>* subSeq = new ImmutableArraySequence<T>(subArr, count);
    delete[] subArr;
    return subSeq;
}

template <class T>
Sequence<T>* ImmutableArraySequence<T>::Append(T item) {
    int length = items.GetSize();
    T* newArr = new T[length + 1];
    for (int i = 0; i < length; i++)
        newArr[i] = items.Get(i);
    newArr[length] = item;
    Sequence<T>* app = new ImmutableArraySequence<T>(newArr, length + 1);
    delete[] newArr;
    return app;
}

template <class T>
Sequence<T>* ImmutableArraySequence<T>::Prepend(T item) {
    int length = items.GetSize();
    T* newArr = new T[length + 1];
    newArr[0] = item;
    for (int i = 0; i < length; i++)
        newArr[i + 1] = items.Get(i);
    Sequence<T>* prep = new ImmutableArraySequence<T>(newArr, length + 1);
    delete[] newArr;
    return prep;
}

template <class T>
Sequence<T>* ImmutableArraySequence<T>::InsertAt(T item, int index) {
    int length = items.GetSize();
    if (index < 0 || index > length)
        throw std::out_of_range("INDEX OUT RANGE");
    T* newArr = new T[length + 1];
    for (int i = length; i > index; i--)
        newArr[i] = items.Get(i-1);
    newArr[index] = item;
    for (int i = index-1; i >=0; i--)
        newArr[i] = items.Get(i);
    Sequence<T>* ins = new ImmutableArraySequence<T>(newArr, length + 1);
    delete[] newArr;
    return ins;
}

template <class T>
Sequence<T>* ImmutableArraySequence<T>::Concat(const Sequence<T>* seq) const {
    int length1 = const_cast<DynamicArray<T>&>(items).GetSize();
    int length2 = seq->GetLength();
    T* newArr = new T[length1 + length2];
    for (int i = 0; i < length1; i++)
        newArr[i] = const_cast<DynamicArray<T>&>(items).Get(i);
    for (int i = 0; i < length2; i++)
        newArr[length1 + i] = seq->Get(i);
    Sequence<T>* sum = new ImmutableArraySequence<T>(newArr, length1 + length2);
    delete[] newArr;
    return sum;
}

template class MutableArraySequence<int>;
template class ImmutableArraySequence<int>;
