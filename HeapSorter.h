#ifndef HEAPSORTER_H
#define HEAPSORTER_H
#include "ISorter.h"

template <typename T>
class HeapSorter : public ISorter<T> {
public:
    ISequence<T>* Sort(ISequence<T>* seq) override {
        HeapSort(seq);
        return seq;
    }

private:
    void Heapify(ISequence<T>* seq, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && seq->GetElement(left) > seq->GetElement(largest)) {
            largest = left;
        }

        if (right < n && seq->GetElement(right) > seq->GetElement(largest)) {
            largest = right;
        }

        if (largest != i) {
            T temp = seq->GetElement(i);
            seq->Set(i, seq->GetElement(largest));
            seq->Set(largest, temp);
            Heapify(seq, n, largest);
        }
    }

    void HeapSort(ISequence<T>* seq) {
        int n = seq->GetLength();

        for (int i = n / 2 - 1; i >= 0; --i) {
            Heapify(seq, n, i);
        }

        for (int i = n - 1; i > 0; --i) {
            T temp = seq->GetElement(0);
            seq->Set(0, seq->GetElement(i));
            seq->Set(i, temp);
            Heapify(seq, i, 0);
        }
    }
};

#endif // HEAPSORTER_H
