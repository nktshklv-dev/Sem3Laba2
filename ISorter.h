#ifndef ISORTER_H
#define ISORTER_H
#include "ISequence.h"

template <typename T>
class ISorter {
public:
   virtual ISequence<T>* Sort(ISequence<T>* seq) = 0;
   virtual ~ISorter() = default;  // Деструктор должен быть public
};

#endif // ISORTER_H