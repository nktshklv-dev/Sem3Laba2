#ifndef INSERTIONSORTER_H
#define INSERTIONSORTER_H
#include "ISorter.h"
template <typename T>
class InsertionSorter : public ISorter<T> {
public:
    ISequence<T>* Sort(ISequence<T>* seq, SortBy sortBy) override {
        InsertionSort(seq, sortBy);
        return seq;
    }

private:
    void InsertionSort(ISequence<T>* seq, SortBy sortBy) {
        int length = seq->GetLength();
        for (int j = 1; j < length; ++j) {
            T key = seq->GetElement(j);
            int i = j - 1;

            bool shouldSwap = false;
            switch (sortBy) {
                case SortBy::SSN:
                    shouldSwap = seq->GetElement(i) > key;
                break;
                case SortBy::FirstName:
                    shouldSwap = seq->GetElement(i).compareByFirstName(key);
                break;
                case SortBy::LastName:
                    shouldSwap = seq->GetElement(i).compareByLastName(key);
                break;
                case SortBy::YearOfBirth:
                    shouldSwap = seq->GetElement(i).compareByYearOfBirth(key);
                break;
                case SortBy::Height:
                    shouldSwap = seq->GetElement(i).compareByHeight(key);
                break;
            }

            while (i >= 0 && shouldSwap) {
                seq->Set(i + 1, seq->GetElement(i));
                i = i - 1;
            }
            seq->Set(i + 1, key);
        }
    }
};
#endif // INSERTIONSORTER_H