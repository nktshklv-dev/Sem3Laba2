#ifndef INSERTIONSORTER_H
#define INSERTIONSORTER_H
#include "ISorter.h"

template <typename T>
class InsertionSorter: public ISorter<T> {
public:
    ISequence<T>* Sort(ISequence<T>* seq) override {
        InsertionSort(seq);
        return seq;
    }
private:
    void InsertionSort(ISequence<T>* seq) {
        int length = seq->GetLength();
        for(int j = 1; j < length; ++j) {
            T key = seq->GetElement(j);
            int i = j - 1;
            while (i >= 0 && seq->GetElement(i) > key) {
                seq->Set(i + 1, seq->GetElement(i));
                i = i - 1;
            }
            seq->Set(i + 1, key);
        }
    }
};
#endif //INSERTIONSORTER_H
