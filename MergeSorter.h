#ifndef MERGESORTER_H
#define MERGESORTER_H
#include "ISorter.h"

template <typename T>
class MergeSorter: public ISorter<T> {
public:
    ISequence<T>* Sort(ISequence<T>* seq) override {
        MergeSort(seq, 0, seq->GetLength() - 1);
        return seq;
    }
private:
    void MergeSort(ISequence<T>* seq, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;

            MergeSort(seq, left, mid);
            MergeSort(seq, mid, right);

            Merge(seq, left, mid, right);
        }
    }

    void Merge(ISequence<T>* seq, int left, int mid, int right) {
        int leftSize = mid - left + 1;
        int rightSize = right - mid;

        T* leftArray = new T[leftSize];
        T* rightArray = new T[rightSize];

        for (int i = 0; i < leftSize; ++i) {
            leftArray[i] = seq->GetElement(left + i);
        }
        for(int j = 0; j < rightSize; ++j) {
            rightArray[j] = seq->GetElement(mid + j + 1);
        }

        int i = 0, j = 0, k = left;

        while (i < leftSize && j < rightSize) {
            if (leftArray[i] <= rightArray[j]) {
                seq -> Set(k, leftArray[i]);
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
