#pragma once
#include"Sequence.h"
#include"LinkedList.h"

template<class T>
class ListSequence : public Sequence<T> {
    private:
        LinkedList<T> listBase;
    public:
        ListSequence<T> * copiedList () {
            ListSequence<T> * newList = new ListSequence<T>(*this);
            return newList;
        }
        ListSequence(const ListSequence<T> & list) {
            this->listBase = list.listBase;
        }
        ListSequence (T* items, size_t count) {
            if (count <= 0) throw out_of_range("Size is wrong!");
            listBase = LinkedList<T>(items, count);
        }
        ListSequence() {
            this->listBase = LinkedList<T>();
        }
        ListSequence(size_t count) {
            this->listBase = LinkedList<T>(count);
        }
        T GetFirst() {
            return listBase.GetFirst();
        }

        T GetLast() {
            return listBase.GetLast();
        }

        T Get(size_t index) {
            if (index < 0 || index >= this->GetLength()) throw out_of_range("Uncorrect index!");
            return listBase.Get(index);
        }

        ListSequence<T> *GetSubsequence(int startIndex, int endIndex) {
            if (startIndex < 0 || endIndex >= this->GetLength() || \
            endIndex <= 0 || startIndex >= this->GetLength()) throw out_of_range("Uncorrect indexes!");
            LinkedList<T> *newList = this->listBase.GetSubList(startIndex, endIndex);
            ListSequence<T> *newSeq = new ListSequence<T>;
            newSeq->listBase = *newList;
            return newSeq;
        }

        size_t GetLength() {
            return listBase.GetLength();
        }

        Sequence<T>*Append(T item) {
            listBase.Append(item);
            return this;
        }
        Sequence<T>*Set(size_t index, T item) {
            listBase.Set(item, index);
            return this;
        }
        Sequence<T>*Prepend(T item) {
            listBase.Prepend(item);
            return this;
        }

        Sequence<T>*InsertAt(T item, int index) {
            if (index <= 0 || index >= this->GetLength()) throw out_of_range("Uncorrect index!");
            listBase.InsertAt(item, index);
            return this;
        }

        ListSequence <T> *Concat(Sequence<T>* list) {
            ListSequence<T> *tmpList = static_cast<ListSequence<T>*>(list);
            this->listBase.Concat(tmpList->listBase);
            return this;
        }
};
