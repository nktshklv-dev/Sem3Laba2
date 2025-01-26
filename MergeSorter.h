#ifndef MERGESORTER_H
#define MERGESORTER_H
#include "ISorter.h"

template <typename T>
class MergeSorter : public ISorter<T> {
public:
    ISequence<T>* Sort(ISequence<T>* seq, SortBy sortBy) override {
        MergeSort(seq, 0, seq->GetLength() - 1, sortBy);
        return seq;
    }

private:
    void MergeSort(ISequence<T>* seq, int left, int right, SortBy sortBy) {
        if (left < right) {
            int mid = left + (right - left) / 2;

            MergeSort(seq, left, mid, sortBy);
            MergeSort(seq, mid + 1, right, sortBy);

            Merge(seq, left, mid, right, sortBy);
        }
    }

    void Merge(ISequence<T>* seq, int left, int mid, int right, SortBy sortBy) {
        int leftSize = mid - left + 1;
        int rightSize = right - mid;

        T* leftArray = new T[leftSize];
        T* rightArray = new T[rightSize];

        for (int i = 0; i < leftSize; ++i) {
            leftArray[i] = seq->GetElement(left + i);
        }
        for (int j = 0; j < rightSize; ++j) {
            rightArray[j] = seq->GetElement(mid + 1 + j);
        }

        int i = 0, j = 0, k = left;

        while (i < leftSize && j < rightSize) {
            bool shouldSwap = false;
            switch (sortBy) {
                case SortBy::SSN:
                    shouldSwap = leftArray[i].getSSN() <= rightArray[j].getSSN();
                    break;
                case SortBy::FirstName:
                    shouldSwap = leftArray[i].compareByFirstName(rightArray[j]);
                    break;
                case SortBy::LastName:
                    shouldSwap = leftArray[i].compareByLastName(rightArray[j]);
                    break;
                case SortBy::YearOfBirth:
                    shouldSwap = leftArray[i].compareByYearOfBirth(rightArray[j]);
                    break;
                case SortBy::Height:
                    shouldSwap = leftArray[i].compareByHeight(rightArray[j]);
                    break;
            }

            if (shouldSwap) {
                seq->Set(k, leftArray[i]);
                ++i;
            } else {
                seq->Set(k, rightArray[j]);
                ++j;
            }
            ++k;
        }

        while (i < leftSize) {
            seq->Set(k, leftArray[i]);
            ++i;
            ++k;
        }

        while (j < rightSize) {
            seq->Set(k, rightArray[j]);
            ++j;
            ++k;
        }

        delete[] leftArray;
        delete[] rightArray;
    }
};
#endif //MERGESORTER_H
