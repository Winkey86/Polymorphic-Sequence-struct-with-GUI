#include "ListSequence.h"
#include <stdexcept>


template <class T>
MutableListSequence<T>::MutableListSequence(): list(){}

template <class T>
MutableListSequence<T>::MutableListSequence(T* items, int count): list(items, count){}

template <class T>
MutableListSequence<T>::MutableListSequence(LinkedList<T>& lst): list(lst){}

template <class T>
MutableListSequence<T>::MutableListSequence(MutableListSequence<T>& lst): list(lst.list){}

template <class T>
T MutableListSequence<T>::GetFirst() const {
    return const_cast<LinkedList<T>&>(list).GetFirst();
}

template <class T>
T MutableListSequence<T>::GetLast() const {
    return const_cast<LinkedList<T>&>(list).GetLast();
}

template <class T>
T MutableListSequence<T>::Get(int index) const {
    return const_cast<LinkedList<T>&>(list).Get(index);
}

template <class T>
int MutableListSequence<T>::GetLength() const {
    return const_cast<LinkedList<T>&>(list).GetLength();
}

template <class T>
Sequence<T>* MutableListSequence<T>::GetSubsequence(int startIndex, int endIndex) const {
    if(startIndex < 0 || endIndex >= const_cast<LinkedList<T>&>(list).GetLength() || startIndex > endIndex)
         throw std::out_of_range("INDEX OUT RANGE");
    int count = endIndex - startIndex + 1;
    T* newArr = new T[count];
    for (int i = 0; i < count; i++)
         newArr[i] = const_cast<LinkedList<T>&>(list).Get(startIndex + i);
    Sequence<T>* subSeq = new MutableListSequence<T>(newArr, count);
    delete[] newArr;
    return subSeq;
}

template <class T>
Sequence<T>* MutableListSequence<T>::Append(T item) {
    list.Append(item);
    return this;
}

template <class T>
Sequence<T>* MutableListSequence<T>::Prepend(T item) {
    list.Prepend(item);
    return this;
}

template <class T>
Sequence<T>* MutableListSequence<T>::InsertAt(T item, int index) {
    if(index < 0 || index > list.GetLength())
         throw std::out_of_range("INDEX OUT RANGE");
    list.InsertAt(item, index);
    return this;
}

template <class T>
Sequence<T>* MutableListSequence<T>::Concat(const Sequence<T>* seq) const {
    MutableListSequence<T>* sum = new MutableListSequence<T>(const_cast<MutableListSequence<T>&>(*this));
    for (int i = 0; i < seq->GetLength(); i++){
         sum->Append(seq->Get(i));
    }
    return sum;
}

template <class T>
ImmutableListSequence<T>::ImmutableListSequence(): list(){}

template <class T>
ImmutableListSequence<T>::ImmutableListSequence(T* items, int count): list(items, count){}

template <class T>
ImmutableListSequence<T>::ImmutableListSequence(const LinkedList<T>& lst): list(const_cast<LinkedList<T>&>(lst)){}

template <class T>
ImmutableListSequence<T>::ImmutableListSequence(const ImmutableListSequence<T>& lst): list(lst.list){}

template <class T>
T ImmutableListSequence<T>::GetFirst() const {
    return const_cast<LinkedList<T>&>(list).GetFirst();
}

template <class T>
T ImmutableListSequence<T>::GetLast() const {
    return const_cast<LinkedList<T>&>(list).GetLast();
}

template <class T>
T ImmutableListSequence<T>::Get(int index) const {
    return const_cast<LinkedList<T>&>(list).Get(index);
}

template <class T>
int ImmutableListSequence<T>::GetLength() const {
    return const_cast<LinkedList<T>&>(list).GetLength();
}

template <class T>
Sequence<T>* ImmutableListSequence<T>::GetSubsequence(int startIndex, int endIndex) const {
    if(startIndex < 0 || endIndex >= const_cast<LinkedList<T>&>(list).GetLength() || startIndex > endIndex)
         throw std::out_of_range("INDEX OUT RANGE");
    int count = endIndex - startIndex + 1;
    T* newArr = new T[count];
    for (int i = 0; i < count; i++)
         newArr[i] = const_cast<LinkedList<T>&>(list).Get(startIndex + i);
    Sequence<T>* subSeq = new ImmutableListSequence<T>(newArr, count);
    delete[] newArr;
    return subSeq;
}

template <class T>
Sequence<T>* ImmutableListSequence<T>::Append(T item) {
    int length = list.GetLength();
    T* newArr = new T[length + 1];
    for (int i = 0; i < length; i++)
         newArr[i] = list.Get(i);
    newArr[length] = item;
    Sequence<T>* app = new ImmutableListSequence<T>(newArr, length + 1);
    delete[] newArr;
    return app;
}

template <class T>
Sequence<T>* ImmutableListSequence<T>::Prepend(T item) {
    int length = list.GetLength();
    T* newArr = new T[length + 1];
    newArr[0] = item;
    for (int i = 0; i < length; i++)
         newArr[i + 1] = list.Get(i);
    Sequence<T>* prep = new ImmutableListSequence<T>(newArr, length + 1);
    delete[] newArr;
    return prep;
}

template <class T>
Sequence<T>* ImmutableListSequence<T>::InsertAt(T item, int index) {
    int length = list.GetLength();
    if(index < 0 || index > length)
         throw std::out_of_range("INDEX OUT RANGE");
    T* newArr = new T[length + 1];
    for (int i = 0; i < index; i++)
         newArr[i] = list.Get(i);
    newArr[index] = item;
    for (int i = index; i < length; i++)
         newArr[i + 1] = list.Get(i);
    Sequence<T>* ins = new ImmutableListSequence<T>(newArr, length + 1);
    delete[] newArr;
    return ins;
}

template <class T>
Sequence<T>* ImmutableListSequence<T>::Concat(const Sequence<T>* seq) const {
    int length1 = const_cast<LinkedList<T>&>(list).GetLength();
    int length2 = seq->GetLength();
    T* newArr = new T[length1 + length2];
    for (int i = 0; i < length1; i++)
         newArr[i] = const_cast<LinkedList<T>&>(list).Get(i);
    for (int i = 0; i < length2; i++)
         newArr[length1 + i] = seq->Get(i);
    Sequence<T>* sum = new ImmutableListSequence<T>(newArr, length1 + length2);
    delete[] newArr;
    return sum;
}

template class MutableListSequence<int>;
template class ImmutableListSequence<int>;
