#pragma once
#include"Sequence.h"
#include"DynamicArray.h"

template<class T>
class ArraySequence : public Sequence<T> {
    private:
        DynamicArray<T> baseArray;
        size_t size;
        size_t capacity;
    public:
        ArraySequence<T>* copiedList () {
            ArraySequence<T> * newList = new ArraySequence<T>(*this);
            return newList;
        }
        ArraySequence(const ArraySequence<T>& array) {
            this->baseArray = array.baseArray;
            this->capacity = array.GetLength();
        }
        ArraySequence(T* items, size_t count) {
            DynamicArray<T> tmpArr(items, count);
            this->baseArray = tmpArr;
        }
        ArraySequence(size_t size) {
            this->baseArray = DynamicArray<T>(size);
        }
        ArraySequence() {
            capacity = 1;
            size = 0;
            baseArray = DynamicArray<T>(capacity);
        }
        T GetFirst() {
            return baseArray.Get(0);
        }
        T GetLast() {
            return baseArray.Get(baseArray.GetSize() - 1);
        }
        T Get(size_t index) {
            return baseArray.Get(index);
        }
        ArraySequence<T>* DeleteByIndex(size_t index) {
            if (index < 0 || index >= size) 
                throw std::length_error("Index is wrong!");
            baseArray.deleteByIndex(index);
            size -= 1;
            return this;
        }
        ArraySequence<T>* GetSubsequence(int startIndex, int endIndex) {
            ArraySequence<T>* newSeq = new ArraySequence<T>(endIndex - startIndex);
            newSeq->baseArray = *(this->baseArray.GetSubArray(startIndex, endIndex));
            return newSeq;
        }
        size_t GetLength() {
            return size;
        }

        Sequence<T>*Set(size_t index, T item) {
            baseArray.Set(index,item);
            return this;
        }

        Sequence<T>*Append(T item) {
            if (size + 1 == capacity) {
                capacity *= 2;
                baseArray.Resize(capacity);
            }
            size += 1;
            baseArray.Set(size - 1, item);
            return this;
        }
        Sequence<T>*Prepend(T item) {
            this->InsertAt(item, 0);
            return this;
        }

        Sequence<T>*InsertAt(T item, int index) {
            for (size_t i = baseArray.GetSize() - 1; i > index; --i)
                baseArray.Set(i, baseArray.Get(i - 1));
            baseArray.Set(index, item);
            if (baseArray.GetSize() + 1 == capacity)
                baseArray.Resize(baseArray.GetSize() * 2);
            return this;
        }

        ArraySequence <T>*Concat(Sequence<T>* array) {
            ArraySequence<T> *tmpArray = static_cast<ArraySequence<T>*>(array);
            for (size_t i = 0; i < tmpArray->GetLength(); ++i)
                this->Append(tmpArray->Get(i));
            return this;
        }

        T operator [] (size_t index) {
            return this->baseArray.Get(index);
        }
};