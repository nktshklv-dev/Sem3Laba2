#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include "ISequence.h"

template <class T>
class DynamicArray : public ISequence<T> {
private:
    T* data;
    int size;

    void Resize(int newSize) {
        T* newData = new T[newSize];

        int minSize = (newSize < size) ? newSize : size;

        for (int i = 0; i < minSize; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        size = newSize;
    }

public:
    class DynamicArrayIterator : public ISequence<T>::Iterator {
    private:
        T* current;
    public:
        DynamicArrayIterator(T* current) : current(current) { }

        bool operator==(const typename ISequence<T>::Iterator& other) const override {
            const DynamicArrayIterator* otherIterator = static_cast<const DynamicArrayIterator*>(&other);
            return otherIterator && current == otherIterator->current;
        }

        bool operator!=(const typename ISequence<T>::Iterator& other) const override {
            return !(*this == other);
        }

        T& operator*() override {
            return *current;
        }

        typename ISequence<T>::Iterator& operator++() override {
            ++current;
            return *this;
        }
    };

    typename ISequence<T>::Iterator* ToBegin() override {
        return new DynamicArrayIterator(data);
    }

    typename ISequence<T>::Iterator* ToEnd() override {
        return new DynamicArrayIterator(data + size);
    }

    DynamicArray(T* items, int size) {
        this->size = size;
        data = new T[size];

        for (int i = 0; i < size; ++i) {
            Set(i, items[i]);
        }
    }

    DynamicArray(int size = 0) {
        this->size = size;
        data = new T[size];
    }

    DynamicArray(const DynamicArray<T>& dynamicArray) {
        size = dynamicArray.size;
        data = new T[size];

        for (int i = 0; i < size; ++i) {
            Set(i, dynamicArray.data[i]);
        }
    }

    ~DynamicArray() override {
        delete[] data;
    }

    T& operator[](int index) {
        return data[index];
    }

    T& GetFirstElement() override {
        return GetElement(0);
    }

    T& GetLastElement() override {
        return GetElement(size - 1);
    }

    T& GetElement(int index) override {
        return data[index];
    }

    void Swap(T& a, T& b) override {
        T temp = a;
        a = b;
        b = temp;
    }

    void Set(int index, T value) override {
        data[index] = value;
    }

    ISequence<T>* GetSubSequence(int startIndex, int endIndex) override {
        int length;

        if (endIndex > size) {
            length = size - startIndex;
        } else {
            length = endIndex - startIndex + 1;

            if (startIndex == 0) {
                length -= 1;
            }
        }

        T* items = new T[length];

        for (int i = 0; i < length; ++i) {
            items[i] = GetElement(startIndex + i);
        }

        return new DynamicArray<T>(items, length);
    }

    int GetLength() override {
        return size;
    }

    void Append(T item) override {
        InsertAt(item, size);
    }

    void Append(T* items, int dataSize) override {
        int oldSize = size;

        Resize(size + dataSize);

        for (int i = oldSize; i < oldSize + dataSize; i++) {
            Set(i, items[i - oldSize]);
        }
    }

    void Prepend(T item) override {
        InsertAt(item, 0);
    }

    void InsertAt(T item, int index) override {
        Resize(size + 1);

        for (int i = size - 1; i > index; --i) {
            Set(i, GetElement(i - 1));
        }

        Set(index, item);
    }

    void Union(ISequence<T>* dynamicArray) override {
        for (int i = 0; i < dynamicArray->GetLength(); ++i) {
            Append(dynamicArray->GetElement(i));
        }
    }
};

#endif // DYNAMICARRAY_H