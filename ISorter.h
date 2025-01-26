#ifndef ISORTER_H
#define ISORTER_H
#include "ISequence.h"
#include "SortBy.h"

template <typename T>
class ISorter {
public:
   virtual ISequence<T>* Sort(ISequence<T>* seq, SortBy sortBy) = 0;
   virtual ~ISorter() = default;
};

#endif // ISORTER_H