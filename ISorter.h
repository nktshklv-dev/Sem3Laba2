#ifndef ISORTER_H
#define ISORTER_H
#include "ISequence.h"

template <typename T>
class ISorter {
   virtual ISequence<T>* Sort(ISequence<T>* seq) = 0;
   virtual ~ISorter() = default;
};
#endif //ISORTER_H
