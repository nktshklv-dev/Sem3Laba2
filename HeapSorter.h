#ifndef HEAPSORTER_H
#define HEAPSORTER_H
#include "ISorter.h"

template <typename T>
class HeapSorter : public ISorter<T> {
public:
    ISequence<T>* Sort(ISequence<T>* seq, SortBy sortBy) override {
        HeapSort(seq, sortBy);
        return seq;
    }

private:
    void Heapify(ISequence<T>* seq, int n, int i, SortBy sortBy) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        bool shouldSwap = false;
        switch (sortBy) {
            case SortBy::SSN:
                shouldSwap = (left < n && seq->GetElement(left) > seq->GetElement(largest));
                break;
            case SortBy::FirstName:
                shouldSwap = (left < n && seq->GetElement(left).compareByFirstName(seq->GetElement(largest)));
                break;
            case SortBy::LastName:
                shouldSwap = (left < n && seq->GetElement(left).compareByLastName(seq->GetElement(largest)));
                break;
            case SortBy::YearOfBirth:
                shouldSwap = (left < n && seq->GetElement(left).compareByYearOfBirth(seq->GetElement(largest)));
                break;
            case SortBy::Height:
                shouldSwap = (left < n && seq->GetElement(left).compareByHeight(seq->GetElement(largest)));
                break;
        }

        if (shouldSwap) {
            largest = left;
        }

        shouldSwap = false;
        switch (sortBy) {
            case SortBy::SSN:
                shouldSwap = (right < n && seq->GetElement(right) > seq->GetElement(largest));
                break;
            case SortBy::FirstName:
                shouldSwap = (right < n && seq->GetElement(right).compareByFirstName(seq->GetElement(largest)));
                break;
            case SortBy::LastName:
                shouldSwap = (right < n && seq->GetElement(right).compareByLastName(seq->GetElement(largest)));
                break;
            case SortBy::YearOfBirth:
                shouldSwap = (right < n && seq->GetElement(right).compareByYearOfBirth(seq->GetElement(largest)));
                break;
            case SortBy::Height:
                shouldSwap = (right < n && seq->GetElement(right).compareByHeight(seq->GetElement(largest)));
                break;
        }

        if (shouldSwap) {
            largest = right;
        }

        if (largest != i) {
            T temp = seq->GetElement(i);
            seq->Set(i, seq->GetElement(largest));
            seq->Set(largest, temp);
            Heapify(seq, n, largest, sortBy);
        }
    }

    void HeapSort(ISequence<T>* seq, SortBy sortBy) {
        int n = seq->GetLength();

        for (int i = n / 2 - 1; i >= 0; --i) {
            Heapify(seq, n, i, sortBy);
        }

        for (int i = n - 1; i > 0; --i) {
            T temp = seq->GetElement(0);
            seq->Set(0, seq->GetElement(i));
            seq->Set(i, temp);
            Heapify(seq, i, 0, sortBy);
        }
    }
};

#endif // HEAPSORTER_H
